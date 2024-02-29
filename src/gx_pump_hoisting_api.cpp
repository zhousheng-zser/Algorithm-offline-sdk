#include "gx_pump_hoisting_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_pump_hoisting_api::gx_pump_hoisting_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_hoisting_api::gx_pump_hoisting_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_hoisting_api::~gx_pump_hoisting_api() {}
    gx_pump_hoisting_api::gx_pump_hoisting_api(gx_pump_hoisting_api&&) noexcept            = default;
    gx_pump_hoisting_api& gx_pump_hoisting_api::operator=(gx_pump_hoisting_api&&) noexcept = default;
    class gx_pump_hoisting_api::impl {
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

        int camera_id = 0; // 摄像头ID
    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_PUMP_HOISTING_V1.0.5";
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

    //  安全生产 泵业吊装狭小区域检测
    pump_hoisting_info gx_pump_hoisting_api::safe_production_pump_hoisting(const gx_img_api& mat, int device_id) {
        if (!impl_->camera_id) {
            impl_->camera_id = device_id;
        } else if (impl_->camera_id != device_id)
            throw source_code_aware_runtime_error{"(device_id:" + std::to_string(device_id)
                                                  + ") != (camera_id:" + std::to_string(impl_->camera_id) + ")\n"};
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                pump_hoisting_info ans;
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<pump_hoisting::detect>(ptr->pump_hoisting_handle,
                    pump_hoisting_detect_param{.instance_guid = "",
                        .format                       = _config->_pump_hoisting_config.format,
                        .height                       = mat.get_rows(),
                        .width                                = mat.get_cols(),
                        .roi_x                                = 0,
                        .roi_y                                = 0,
                        .roi_width                            = mat.get_cols(),
                        .roi_height                           = mat.get_rows(),
                        .params =
                            pump_hoisting_detect_param::confidence_params{
                                .conf_thres = _config->_pump_hoisting_config.conf_thres,
                                .nms_thres  = _config->_pump_hoisting_config.nms_thres,
                                .move_threshold = _config->_pump_hoisting_config.move_threshold,
                                .device_id      = device_id}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pump_hoisting_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix