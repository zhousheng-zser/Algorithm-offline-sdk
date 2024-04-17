#include "gx_pump_light_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_pump_light_api::gx_pump_light_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_light_api::gx_pump_light_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_light_api::~gx_pump_light_api() {}
    gx_pump_light_api::gx_pump_light_api(gx_pump_light_api&&) noexcept            = default;
    gx_pump_light_api& gx_pump_light_api::operator=(gx_pump_light_api&&) noexcept = default;
    class gx_pump_light_api::impl {
    public:
        void init() {
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

    private:
#if (GX_PLATFORM_NAME != 6) 
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_PUMP_LIGHT_V2.0.0";
        std::vector<std::string> empower_algorithm_id_list = {"24"};
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

    //  安全生产 定制灯光检测
    pump_light_info gx_pump_light_api::safe_production_pump_light(
        const gx_img_api& mat, const abi::vector<pump_light_point>& quadrangle ) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                pump_light_info ans;
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
                auto result = ptr->protocol_ptr.invoke<pump_light::detect>(ptr->pump_light_handle,
                    pump_light_detect_param{.instance_guid = "",
                        .format                       = _config->_pump_light_config.format,
                        .height                       = mat.get_rows(),
                        .width                        = mat.get_cols(),
                        .params = pump_light_detect_param::confidence_params{
                            .x1                                                  = quadrangle[0].x,
                            .y1                                                  = quadrangle[0].y,
                            .x2                                                  = quadrangle[1].x,
                            .y2                                                  = quadrangle[1].y,
                            .x3                                                  = quadrangle[2].x,
                            .y3                                                  = quadrangle[2].y,
                            .x4                                                  = quadrangle[3].x,
                            .y4                                                  = quadrangle[3].y,
                            .conf_thres                                          = _config->_pump_light_config.conf_thres
                    }},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pump_light_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix