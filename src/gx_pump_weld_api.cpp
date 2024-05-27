#include "gx_pump_weld_api.hpp"

#include "sdk_share.hpp"

#include <queue>

namespace glasssix {

    gx_pump_weld_api::gx_pump_weld_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_weld_api::gx_pump_weld_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_weld_api::~gx_pump_weld_api() {}
    gx_pump_weld_api::gx_pump_weld_api(gx_pump_weld_api&&) noexcept            = default;
    gx_pump_weld_api& gx_pump_weld_api::operator=(gx_pump_weld_api&&) noexcept = default;
    class gx_pump_weld_api::impl {
    public:
        void init() {
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

    private:
#if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_PUMP_WELD_V2.0.0";
        std::vector<std::string> empower_algorithm_id_list = {"31"};
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

    //  泵业定制化焊接检测
    pump_weld_info gx_pump_weld_api::safe_production_pump_weld(const abi::vector<gx_img_api>& mat_list,
        float light_conf_thres, float candidate_box_width, float candidate_box_height) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                if (_config->_pump_weld_config.batch != mat_list.size())
                    throw source_code_aware_runtime_error(
                        U8("Error: The config/pump_weld.json : batch != mat_list.size()"));
                pump_weld_info ans;
                std::vector<char> imgBatchDataArr(
                    _config->_pump_weld_config.batch * mat_list[0].get_data_len()); // push batch img to array
                for (int j = 0; j < _config->_pump_weld_config.batch; ++j) {
                    //   构造图片数组
#if (GX_PLATFORM_NAME != 8)
                    std::memcpy(imgBatchDataArr.data() + j * mat_list[j].get_data_len(), mat_list[j].get_data(),
                        mat_list[j].get_data_len());
#else
                    for (size_t i = 0; i < mat_list[j].get_rows(); i++) {
                        auto row_ptr = mat_list[j].get_row_ptr(i);
                        std::copy(row_ptr, row_ptr + mat_list[j].get_cols() * 3,
                            imgBatchDataArr.data() + j * mat_list[0].get_data_len() + i * mat_list[j].get_cols() * 3);
                    }
#endif
                }
                std::span<char> str{imgBatchDataArr.data(), imgBatchDataArr.size()};
                auto result = ptr->protocol_ptr.invoke<pump_weld::detect>(ptr->pump_weld_handle,
                    pump_weld_detect_param{.instance_guid = "",
                        .format                           = _config->_pump_weld_config.format,
                        .height                           = mat_list[0].get_rows(),
                        .width                            = mat_list[0].get_cols(),
                        .batch                            = _config->_pump_weld_config.batch,
                        .params                           = pump_weld_detect_param::confidence_params{.conf_thres =
                                                                                _config->_pump_weld_config.conf_thres,
                                                      .nms_thres            = _config->_pump_weld_config.nms_thres,
                                                      .wmachine_conf_thres            = _config->_pump_weld_config.wmachine_conf_thres,
                                                      .wlight_conf_thres            = light_conf_thres,
                                                      .candidate_box_width  = candidate_box_width,
                                                      .candidate_box_height = candidate_box_height}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = 1;
            for (int i = 0; i < _config->_pump_weld_config.batch && flag; i++)
                flag = write_dump_img(mat_list[i], "_pump_weld_dump_" + std::to_string(i) + ".jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix