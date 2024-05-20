#include "gx_posture_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_posture_api::gx_posture_api() : impl_{std::make_unique<impl>()} {}
    gx_posture_api::gx_posture_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_posture_api::~gx_posture_api() {}
    gx_posture_api::gx_posture_api(gx_posture_api&&) noexcept            = default;
    gx_posture_api& gx_posture_api::operator=(gx_posture_api&&) noexcept = default;
    class gx_posture_api::impl {
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
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_POSTURE_V4.0.0";
        std::vector<std::string> empower_algorithm_id_list = {"-12"};
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

    //  姿态检测
    abi::vector<posture_info> gx_posture_api::safe_production_posture(const gx_img_api& mat) {
        try {
            auto result_pool = pool->enqueue(0,[&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                abi::vector<posture_info> ans;
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
                auto result = ptr->protocol_ptr.invoke<posture::detect>(ptr->posture_handle,
                    posture_detect_param{.instance_guid = "",
                        .format                         = 1,
                        .height                         = mat.get_rows(),
                        .width                          = mat.get_cols(),
                        .roi_x                          = 0,
                        .roi_y                          = 0,
                        .roi_width                      = mat.get_cols(),
                        .roi_height                     = mat.get_rows()},
                    str);

                ans = std::move(result.info_list);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_posture_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix