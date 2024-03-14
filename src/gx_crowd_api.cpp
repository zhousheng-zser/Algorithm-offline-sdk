#include "gx_crowd_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    thread_pool pool_crowd(1);
    gx_crowd_api::gx_crowd_api() : impl_{std::make_unique<impl>()} {}
    gx_crowd_api::gx_crowd_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_crowd_api::~gx_crowd_api() {}
    gx_crowd_api::gx_crowd_api(gx_crowd_api&&) noexcept            = default;
    gx_crowd_api& gx_crowd_api::operator=(gx_crowd_api&&) noexcept = default;
    class gx_crowd_api::impl {
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
            }
            init();
        }
        impl(const abi::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
            }
            init();
        }
        ~impl() {}

    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_CROWD_V2.1.4";
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

    //  安全生产 聚众检测
    crowd_info gx_crowd_api::safe_production_crowd(const gx_img_api& mat, int min_cluster_size) {
        try {
            if (min_cluster_size < 4)
                throw source_code_aware_runtime_error(U8("Error: The min_cluster_size < 4!!"));

            auto result_pool = pool_crowd.enqueue([&] {
                if (thread_algo_crowd_ptr == nullptr) {
                    thread_algo_crowd_ptr = new algo_crowd_ptr();
                }
                auto ptr = thread_algo_crowd_ptr;
                crowd_info ans;
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<crowd::detect>(ptr->crowd_handle,
                    crowd_detect_param{
                        .instance_guid    = "",
                        .format           = _config->_crowd_config.format,
                        .height           = mat.get_rows(),
                        .width            = mat.get_cols(),
                        .roi_x            = 0,
                        .roi_y            = 0,
                        .roi_width        = mat.get_cols(),
                        .roi_height       = mat.get_rows(),
                        .min_cluster_size = min_cluster_size,
                        .params           = crowd_detect_param::confidence_params{.area_threshold =
                                                                            _config->_crowd_config.area_threshold},
                    },
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_crowd_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix