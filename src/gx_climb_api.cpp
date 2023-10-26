#include "gx_climb_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_climb_api::gx_climb_api() : impl_{std::make_unique<impl>()} {}
    gx_climb_api::gx_climb_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_climb_api::~gx_climb_api() {}
    gx_climb_api::gx_climb_api(gx_climb_api&&) noexcept            = default;
    gx_climb_api& gx_climb_api::operator=(gx_climb_api&&) noexcept = default;
    class gx_climb_api::impl {
    public:
        void init() {
            empower_key = get_empower_key(_config->_configure_directory.license_directory);
            empower.set_serial_number(_config->_configure_directory.empower_serial_number);
            empower.set_algorithm_id(empower_algorithm_id);
            empower.set_license(empower_key.c_str());
            empower.evaluate_license(empower_Callback, nullptr);
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
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_CLIMB_V1.0.0";
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
    };

    //  安全生产 攀爬检测
    climb_info gx_climb_api::safe_production_climb(const gx_img_api& mat, const climb_line& line) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                climb_info ans;
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<climb::detect>(ptr->climb_handle,
                    climb_detect_param{.instance_guid = "",
                        .format                       = _config->_climb_config.format,
                        .height                       = mat.get_rows(),
                        .width                        = mat.get_cols(),
                        .roi_x                        = 0,
                        .roi_y                        = 0,
                        .roi_width                    = mat.get_cols(),
                        .roi_height                   = mat.get_rows(),
                        .params = climb_detect_param::confidence_params{.conf_thres = _config->_climb_config.conf_thres,
                            .nms_thres                                              = _config->_climb_config.nms_thres,
                            .x1                                                     = line.x1,
                            .y1                                                     = line.y1,
                            .x2                                                     = line.x2,
                            .y2                                                     = line.y2}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            const auto timestamp       = date_time::now();
            const std::string time_str = timestamp.to_string("yyyyMMddhhmmsszzz");
            bool flag = mat.write(_config->_configure_directory.dump_img_directory + "/" + time_str + "_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix