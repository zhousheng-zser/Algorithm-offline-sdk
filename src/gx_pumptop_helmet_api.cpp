#include "gx_pumptop_helmet_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_pumptop_helmet_api::gx_pumptop_helmet_api() : impl_{std::make_unique<impl>()} {}
    gx_pumptop_helmet_api::gx_pumptop_helmet_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_pumptop_helmet_api::~gx_pumptop_helmet_api() {}
    gx_pumptop_helmet_api::gx_pumptop_helmet_api(gx_pumptop_helmet_api&&) noexcept            = default;
    gx_pumptop_helmet_api& gx_pumptop_helmet_api::operator=(gx_pumptop_helmet_api&&) noexcept = default;
    class gx_pumptop_helmet_api::impl {
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
        std::string empower_key = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_PUMPTOP_HELMET_V1.0.6";
        std::vector<std::string> empower_algorithm_id_list = {"26"};
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

    //  安全生产 泵顶安全帽检测
    pumptop_helmet_info gx_pumptop_helmet_api::safe_production_pumptop_helmet(const gx_img_api& mat) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                pumptop_helmet_info ans;
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
                auto result = ptr->protocol_ptr.invoke<pumptop_helmet::detect>(ptr->pumptop_helmet_handle,
                    pumptop_helmet_detect_param{.instance_guid = "",
                        .format                                = _config->_pumptop_helmet_config.format,
                        .height                                = mat.get_rows(),
                        .width                                 = mat.get_cols(),
                        .params =
                            pumptop_helmet_detect_param::confidence_params{
                                .head_conf_thres = _config->_pumptop_helmet_config.head_conf_thres,
                                .pump_conf_thres = _config->_pumptop_helmet_config.pump_conf_thres,
                                .people_conf_thres     = _config->_pumptop_helmet_config.people_conf_thres,
                                .head_score_conf_thres = _config->_pumptop_helmet_config.head_score_conf_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pumptop_helmet_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix