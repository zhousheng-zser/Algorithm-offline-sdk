#include "gx_helmet_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_helmet_api::gx_helmet_api() : impl_{std::make_unique<impl>()} {}
    gx_helmet_api::gx_helmet_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_helmet_api::~gx_helmet_api() {}
    gx_helmet_api::gx_helmet_api(gx_helmet_api&&) noexcept            = default;
    gx_helmet_api& gx_helmet_api::operator=(gx_helmet_api&&) noexcept = default;
    class gx_helmet_api::impl {
    public:
        void init() {
            if (api_temp == nullptr) {
                api_temp = new gx_head_api();
            }
#if (GX_PLATFORM_NAME != 6)  
            for (int i = 0; i < empower_algorithm_id_list.size(); ++i) {
                try {
                    empower_key = get_empower_key(_config->_configure_directory.license_directory);
                    empower.set_serial_number(_config->_configure_directory.empower_serial_number);
                    empower.set_algorithm_id(empower_algorithm_id_list[i]);
                    empower.set_license(empower_key.c_str());
                    empower.evaluate_license(empower_Callback, nullptr);
                    break; // 不崩就直接跳出去
                } catch (const std::exception& ex) {
                    if (i == empower_algorithm_id_list.size() - 1) // 最后一个都崩就抛异常
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
        gx_head_api* api_temp = nullptr;

    private:
#if (GX_PLATFORM_NAME != 6) 
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_HELMET_V3.2.2";
        std::vector<std::string> empower_algorithm_id_list = {"2"};
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


    //  安全生产 安全帽检测
    helmet_info gx_helmet_api::safe_production_helmet(
        const gx_img_api& mat, const abi::vector<head_info>& head_info_list) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                helmet_info ans;
                // 过滤掉人头置信度小于conf_thres的
                abi::vector<head_info> head_list_temp;
                for (int i = 0; i < head_info_list.size(); i++) {
                    if (head_info_list[i].score >= _config->_helmet_config.conf_thres)
                        head_list_temp.emplace_back(head_info_list[i]);
                }
#if (GX_PLATFORM_NAME != 8)
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
#else
                std::vector<uchar> img_data(mat.get_cols() * mat.get_rows() * 3);
                for (int i = 0; i < mat.get_rows(); i++) {
                    auto row_ptr = mat.get_row_ptr(i);
                    std::copy(row_ptr, row_ptr + mat.get_cols() * 3, img_data.data() + i * mat.get_cols() * 3);
                }
                std::span<char> str{
                    reinterpret_cast<char*>(const_cast<uchar*>(img_data.data())), mat.get_cols() * mat.get_rows() * 3};
#endif
                auto result = ptr->protocol_ptr.invoke<helmet::detect>(ptr->helmet_handle,
                    helmet_detect_param{.instance_guid = "",
                        .format                        = _config->_helmet_config.format,
                        .height                        = mat.get_rows(),
                        .width                         = mat.get_cols(),
                        .roi_x                         = 0,
                        .roi_y                         = 0,
                        .roi_width                     = mat.get_cols(),
                        .roi_height                    = mat.get_rows(),
                        .head_info_list                = head_list_temp,
                        .params =
                            helmet_detect_param::confidence_params{.conf_thres = _config->_helmet_config.conf_thres,
                                .nms_thres                                     = _config->_helmet_config.nms_thres,
                                .min_size                                      = _config->_helmet_config.min_size}},
                    str);
                ans         = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_helmet_dump.jpg");
            throw source_code_aware_runtime_error{ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"} };
        }
    }

    helmet_info gx_helmet_api::safe_production_helmet(const gx_img_api& mat) {
        auto head_info_list = impl_->api_temp->safe_production_head(mat);
        return safe_production_helmet(mat, head_info_list);
    }
} // namespace glasssix