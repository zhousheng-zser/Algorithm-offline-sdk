#include "gx_batterypilferers_api.hpp"

#include "sdk_share.hpp"

#include <queue>

namespace glasssix {
    thread_pool* pool_batterypilferers = nullptr;
    std::unordered_map<std::thread::id, algo_batterypilferers_ptr*> batterypilferers_thread_algo_ptr;
    gx_batterypilferers_api::gx_batterypilferers_api() : impl_{std::make_unique<impl>()} {}
    gx_batterypilferers_api::gx_batterypilferers_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_batterypilferers_api::~gx_batterypilferers_api() {}
    gx_batterypilferers_api::gx_batterypilferers_api(gx_batterypilferers_api&&) noexcept            = default;
    gx_batterypilferers_api& gx_batterypilferers_api::operator=(gx_batterypilferers_api&&) noexcept = default;
    class gx_batterypilferers_api::impl {
    public:
        void init() {
            if (pool_batterypilferers == nullptr)
                pool_batterypilferers = new thread_pool(_config->_configure_directory.thread_pool_num_batterypilferers);

#if (GX_EMPOWER_FLAG) 
            for (int i = 0; i < empower_algorithm_id_list.size(); ++i) {
                try {
                    auto license = abi::from_abi_string(_config->_configure_directory.license_directory);
                    empower_key  = get_empower_key(license);
                    auto number = abi::from_abi_string(_config->_configure_directory.empower_serial_number);
                    empower.set_serial_number(number);
                    empower.set_algorithm_id(empower_algorithm_id_list[i]);
                    empower.set_license(empower_key.c_str());
                    empower.evaluate_license(empower_Callback, nullptr);
                    break;//不崩就直接跳出去
                } catch (const std::exception& ex) {
                    if (i == empower_algorithm_id_list.size()-1) //最后一个都崩就抛异常
                        throw source_code_aware_runtime_error{ex.what() + std::string{": empower_key install error"}};
                }
            }
#endif
        }
        impl() {
            if (_config == nullptr) {
                _config = new config();
                pool    = new thread_pool(_config->_configure_directory.thread_pool_num);
            }
            init();
        }
        impl(const abi::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                pool    = new thread_pool(_config->_configure_directory.thread_pool_num);
            }
            init();
        }
        ~impl() {}


    private:
        #if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_BATTERYPILFERERS_V1.0.1";
        std::vector<std::string> empower_algorithm_id_list = {"17"};
        std::string get_empower_key(std::string& path) {
            std::ifstream key(path, std::ios::in);
            if (!key.is_open()) {
                key.close();
                if (!empower_warning_flag) {
                    printf("Warning: license_directory :Failed to open file\n");
                    empower_warning_flag = true;
                }
                return "";
            }
            std::string ans;
            key >> ans;
            return ans;
        }
#endif
    };

    //  偷电瓶检测
    batterypilferers_info gx_batterypilferers_api::safe_production_batterypilferers(const abi::vector<gx_img_api>& mat_list) {
        try {
            auto result_pool = pool_batterypilferers->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (batterypilferers_thread_algo_ptr[id_] == nullptr) {
                    batterypilferers_thread_algo_ptr[id_] = new algo_batterypilferers_ptr();
                }
                auto ptr = batterypilferers_thread_algo_ptr[id_];
                if (_config->_batterypilferers_config.batch != mat_list.size())
                    throw source_code_aware_runtime_error(U8("Error: The config/batterypilferers.json : batch != mat_list.size()"));
                batterypilferers_info ans;
                std::vector<char> imgBatchDataArr(
                    _config->_batterypilferers_config.batch * mat_list[0].get_data_len()); // push batch img to array
                for (int j = 0; j < _config->_batterypilferers_config.batch; ++j) {
                    //   构造图片数组
#if (GX_PLATFORM_NAME != 8)
                    std::memcpy(imgBatchDataArr.data() + j * mat_list[j].get_data_len(),
                        mat_list[j].get_data(), mat_list[j].get_data_len());
#else
                    //std::vector<uchar> img_data(mat_list[j].get_cols() * get_rows() * 3);
                    for (size_t i = 0; i < mat_list[j].get_rows(); i++)
                    {
                        auto row_ptr = mat_list[j].get_row_ptr(i);
                        std::copy(row_ptr, row_ptr + mat_list[j].get_cols() * 3,
                            imgBatchDataArr.data() + j * mat_list[0].get_data_len() + i * mat_list[j].get_cols() * 3);
                    }
#endif
                }
                std::span<char> str{imgBatchDataArr.data(), imgBatchDataArr.size()};
                auto result = ptr->protocol_ptr.invoke<batterypilferers::detect>(ptr->batterypilferers_handle,
                    batterypilferers_detect_param{.instance_guid = "",
                        .format                                  = _config->_batterypilferers_config.format,
                        .height                                  = mat_list[0].get_rows(),
                        .width                                   = mat_list[0].get_cols(),
                        .roi_x                                   = 0,
                        .roi_y                                   = 0,
                        .roi_width                               = mat_list[0].get_cols(),
                        .roi_height                              = mat_list[0].get_rows(),
                        .params =
                            batterypilferers_detect_param::confidence_params{
                                .conf_thres = _config->_batterypilferers_config.conf_thres,
                                .nms_thres  = _config->_batterypilferers_config.nms_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = 1;
            for (int i = 0; i < mat_list.size() && flag; i++)
                flag = write_dump_img(mat_list[i], "_batterypilferers_dump_" + std::to_string(i) + ".jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }
} // namespace glasssix