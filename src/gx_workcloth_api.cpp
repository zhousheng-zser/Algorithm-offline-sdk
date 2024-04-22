#include "gx_workcloth_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_workcloth_api::gx_workcloth_api() : impl_{std::make_unique<impl>()} {}
    gx_workcloth_api::gx_workcloth_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_workcloth_api::~gx_workcloth_api() {}
    gx_workcloth_api::gx_workcloth_api(gx_workcloth_api&&) noexcept            = default;
    gx_workcloth_api& gx_workcloth_api::operator=(gx_workcloth_api&&) noexcept = default;
    class gx_workcloth_api::impl {
    public:
        void init() {
            if (api_temp == nullptr) {
                api_temp = new gx_posture_api();
            }
#if (GX_EMPOWER_FLAG)  
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
        gx_posture_api* api_temp = nullptr;

    private:
#if (GX_EMPOWER_FLAG) 
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_WORKCLOTH_V2.8.0";
        std::vector<std::string> empower_algorithm_id_list = {"4"};
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

    //  工服检测
    workcloth_info gx_workcloth_api::safe_production_workcloth(
        const gx_img_api& mat, int color_hsv_list_id, const abi::vector<posture_info>& posture_info_list) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                workcloth_info ans;
                // 过滤掉姿态置信度小于0.7的
                abi::vector<posture_info> posture_list_temp;
                for (int i = 0; i < posture_info_list.size(); i++) {
                    if (posture_info_list[i].score >= 0.7)
                        posture_list_temp.emplace_back(posture_info_list[i]);
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
                auto result = ptr->protocol_ptr.invoke<workcloth::detect>(ptr->workcloth_handle,
                    workcloth_detect_param{.instance_guid = "",
                        .format                           = _config->_workcloth_config.format,
                        .height                           = mat.get_rows(),
                        .width                            = mat.get_cols(),
                        .roi_x                            = 0,
                        .roi_y                            = 0,
                        .roi_width                        = mat.get_cols(),
                        .roi_height                       = mat.get_rows(),
                        .posture_info_list                = posture_list_temp,
                        .params                           = workcloth_detect_param::confidence_params{.conf_thres =
                                                                                _config->_workcloth_config.conf_thres,
                                                      .nms_thres = _config->_workcloth_config.nms_thres},
                        .color_hsv_cfg = _config->_workcloth_config.color_hsv_list[color_hsv_list_id]},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_workcloth_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

    //  工服检测
    workcloth_info gx_workcloth_api::safe_production_workcloth(const gx_img_api& mat, int color_hsv_list_id) {
        auto posture_info_list   = impl_->api_temp->safe_production_posture(mat);
        return safe_production_workcloth(mat, color_hsv_list_id, posture_info_list);
    }

} // namespace glasssix