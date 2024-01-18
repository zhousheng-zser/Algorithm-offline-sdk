#include "gx_onphone_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_onphone_api::gx_onphone_api() : impl_{std::make_unique<impl>()} {}
    gx_onphone_api::gx_onphone_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_onphone_api::~gx_onphone_api() {}
    gx_onphone_api::gx_onphone_api(gx_onphone_api&&) noexcept            = default;
    gx_onphone_api& gx_onphone_api::operator=(gx_onphone_api&&) noexcept = default;
    class gx_onphone_api::impl {
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
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_ONPHONE_V3.2.0";
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

    //  打电话检测
    onphone_info gx_onphone_api::safe_production_onphone(
        const gx_img_api& mat, const abi::vector<head_info>& head_info_list) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                onphone_info ans;

                // 过滤掉人头置信度小于head_conf_thres的
                abi::vector<head_info> head_list_temp;
                for (int i = 0; i < head_info_list.size(); i++) {
                    if (head_info_list[i].score >= _config->_onphone_config.head_conf_thres)
                        head_list_temp.emplace_back(head_info_list[i]);
                }

                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<onphone::detect>(ptr->onphone_handle,
                    onphone_detect_param{.instance_guid = "",
                        .format                         = _config->_onphone_config.format,
                        .height                         = mat.get_rows(),
                        .width                          = mat.get_cols(),
                        .roi_x                          = 0,
                        .roi_y                          = 0,
                        .roi_width                      = mat.get_cols(),
                        .roi_height                     = mat.get_rows(),
                        .head_info_list                 = head_list_temp,
                        .params =
                            onphone_detect_param::confidence_params{.conf_thres = _config->_onphone_config.conf_thres,
                                .nms_thres                                      = _config->_onphone_config.nms_thres,
                                .phone_distance_thres = _config->_onphone_config.phone_distance_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_onphone_head_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

    //  打电话检测
    onphone_info gx_onphone_api::safe_production_onphone(
        const gx_img_api& mat, const abi::vector<posture_info>& posture_info_list) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                onphone_info ans;
                // 过滤掉姿态置信度小于0.6的
                abi::vector<posture_info> posture_list_temp;
                for (int i = 0; i < posture_info_list.size(); i++) {
                    if (posture_info_list[i].score >= 0.6)
                        posture_list_temp.emplace_back(posture_info_list[i]);
                }
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<onphone::detect2>(ptr->onphone_handle,
                    onphone_detect2_param{.instance_guid = "",
                        .format                          = _config->_onphone_config.format,
                        .height                          = mat.get_rows(),
                        .width                           = mat.get_cols(),
                        .roi_x                           = 0,
                        .roi_y                           = 0,
                        .roi_width                       = mat.get_cols(),
                        .roi_height                      = mat.get_rows(),
                        .posture_info_list               = posture_list_temp,
                        .params =
                            onphone_detect2_param::confidence_params{.conf_thres = _config->_onphone_config.conf_thres,
                                .nms_thres                                       = _config->_onphone_config.nms_thres,
                                .phone_distance_thres = _config->_onphone_config.phone_distance_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_onphone_posture_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix