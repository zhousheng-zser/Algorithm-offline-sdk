#include "gx_head_api.hpp"
#include "sdk_share.hpp"

namespace glasssix {

    gx_head_api::gx_head_api() : impl_{std::make_unique<impl>()} {}
    gx_head_api::gx_head_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_head_api::~gx_head_api() {}
    gx_head_api::gx_head_api(gx_head_api&&) noexcept            = default;
    gx_head_api& gx_head_api::operator=(gx_head_api&&) noexcept = default;
    class gx_head_api::impl {
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
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_HEAD_V1.1.4";
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


    //  安全生产 人头检测
    abi::vector<head_info> gx_head_api::safe_production_head(const gx_img_api& mat) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                abi::vector<head_info> ans;
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<head::detect>(ptr->head_handle,
                    head_detect_param{.instance_guid = "",
                        .format                      = 1,
                        .height                      = mat.get_rows(),
                        .width                       = mat.get_cols(),
                        .roi_x                       = 0,
                        .roi_y                       = 0,
                        .roi_width                   = mat.get_cols(),
                        .roi_height                  = mat.get_rows()},
                    str);
                ans         = std::move(result.info_list);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_head_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix