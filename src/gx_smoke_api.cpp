#include "gx_smoke_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_smoke_api::gx_smoke_api() : impl_{std::make_unique<impl>()} {}
    gx_smoke_api::gx_smoke_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_smoke_api::~gx_smoke_api() {}
    gx_smoke_api::gx_smoke_api(gx_smoke_api&&) noexcept            = default;
    gx_smoke_api& gx_smoke_api::operator=(gx_smoke_api&&) noexcept = default;
    class gx_smoke_api::impl {
    public:
        void init() {
            if (api_temp == nullptr) {
                api_temp = new gx_posture_api();
            }
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
        gx_posture_api* api_temp = nullptr;

    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_SMOKE_V3.0.6";
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

    //  抽烟检测
    smoke_info gx_smoke_api::safe_production_smoke(
        const gx_img_api& mat, const abi::vector<posture_info>& posture_info_list) {
        if (mat.get_infrared_status())
            return {};
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                smoke_info ans;
                // 过滤掉姿态置信度小于0.6的
                abi::vector<posture_info> posture_list_temp;
                for (int i = 0; i < posture_info_list.size(); i++) {
                    if (posture_info_list[i].score >= 0.6)
                        posture_list_temp.emplace_back(posture_info_list[i]);
                }
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
                        .posture_info_list            = posture_list_temp,
                        .params = smoke_detect_param::confidence_params{.conf_thres = _config->_smoke_config.conf_thres,
                            .nms_thres                                              = _config->_smoke_config.nms_thres,
                            .little_target_conf_thres = _config->_smoke_config.little_target_conf_thres,
                            .smoke_conf_thres         = _config->_smoke_config.smoke_conf_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_smoke_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }
    //  抽烟检测
    smoke_info gx_smoke_api::safe_production_smoke(const gx_img_api& mat) {
        if (mat.get_infrared_status())
            return {};
        auto posture_info_list = impl_->api_temp->safe_production_posture(mat);
        return safe_production_smoke(mat, posture_info_list);
    }

} // namespace glasssix