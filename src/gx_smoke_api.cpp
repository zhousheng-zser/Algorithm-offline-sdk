#include "gx_smoke_api.hpp"
#include "sdk_share.hpp"

namespace glasssix {

    gx_smoke_api::gx_smoke_api() : impl_{std::make_unique<impl>()} {}
    gx_smoke_api::gx_smoke_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_smoke_api::~gx_smoke_api() {}
    gx_smoke_api::gx_smoke_api(gx_smoke_api&&) noexcept      = default;
    gx_smoke_api& gx_smoke_api::operator=(gx_smoke_api&&) noexcept = default;
    class gx_smoke_api::impl {
    public:
        void init() {
            empower_key = get_empower_key(_config->_configure_directory.license_directory);
            empower.set_license(empower_key.c_str());
            empower.set_algorithm_id(empower_algorithm_id);
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
        std::string empower_algorithm_id = "RK3588_C++_SMOKE_V1.0.0";
        std::string get_empower_key(std::string& path) {
            std::ifstream key(path, std::ios::in);
            if (!key.is_open()) {
                key.close();
                throw source_code_aware_runtime_error(U8("Error: license_directory :Failed to open file"));
            }
            std::string ans;
            key >> ans;
            return ans;
        }
    };

    //  抽烟检测
    smoke_info gx_smoke_api::safe_production_smoke(const gx_img_api& mat) {
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            smoke_info ans;
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result = ptr->protocol_ptr.invoke<smoke::detect>(ptr->smoke_handle,
                smoke_detect_param{.instance_guid = "",
                    .format                       = _config->_smoke_config.format,
                    .height                       = mat.get_rows(),
                    .width                        = mat.get_cols(),
                    .roi_x                        = 0,
                    .roi_y                        = 0,
                    .roi_width                    = mat.get_cols(),
                    .roi_height                   = mat.get_rows(),
                    .params = smoke_detect_param::confidence_params{.conf_thres = _config->_smoke_config.conf_thres,
                        .nms_thres                                              = _config->_smoke_config.nms_thres}},
                str);

            ans = std::move(result.detect_info);
            return ans;
        });
        return result_pool.get();
    }

} // namespace glasssix