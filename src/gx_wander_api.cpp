#include "gx_wander_api.hpp"

#include "sdk_share.hpp"

#include <unordered_map>

namespace glasssix {

    gx_wander_api::gx_wander_api() : impl_{std::make_unique<impl>()} {}
    gx_wander_api::gx_wander_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_wander_api::~gx_wander_api() {}
    gx_wander_api::gx_wander_api(gx_wander_api&&) noexcept            = default;
    gx_wander_api& gx_wander_api::operator=(gx_wander_api&&) noexcept = default;
    class gx_wander_api::impl {
    public:
        void init() {
            wander_map.clear();
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
        struct person_cache {
            std::int64_t sum_time  = 0;
            std::int64_t last_time = 0;
        };
        std::unordered_map<std::int32_t, person_cache> wander_map;

    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_WANDER_V2.0.2";
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

    //  徘徊检测
    wander_info gx_wander_api::safe_production_wander(const gx_img_api& mat, std::int64_t current_time, int device_id) {
        if (!impl_->camera_id) {
            impl_->camera_id = device_id;
        } else if (impl_->camera_id != device_id)
            throw source_code_aware_runtime_error{"(device_id:" + std::to_string(device_id)
                                                  + ") != (camera_id:" + std::to_string(impl_->camera_id) + ")\n"};
        ///  超过interval秒没出现的人自动删
        std::vector<std::int32_t> v;
        for (auto& it : impl_->wander_map) {
            if (current_time - it.second.last_time > _config->_wander_config.interval)
                v.emplace_back(it.first);
        }
        for (int x : v) {
            impl_->wander_map.erase(x);
            wander_remove_id(x);
        }
        wander_info ans;
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<wander::detect>(ptr->wander_handle,
                    wander_detect_param{.instance_guid = "",
                        .format                        = _config->_wander_config.format,
                        .height                        = mat.get_rows(),
                        .width                         = mat.get_cols(),
                        .roi_x                         = 0,
                        .roi_y                         = 0,
                        .roi_width                     = mat.get_cols(),
                        .roi_height                    = mat.get_rows(),
                        .params =
                            wander_detect_param::confidence_params{
                                .current_time            = current_time,
                                .feature_table_size      = _config->_wander_config.feature_table_size,
                                .feature_match_threshold = _config->_wander_config.feature_match_threshold,
                                .person_conf             = _config->_wander_config.person_conf,
                                .device_id               = device_id,
                            }},
                    str);
                return std::move(result.detect_info);
            });
            ans              = result_pool.get();
            for (int i = 0; i < ans.person_info.size(); i++) {
                int id_temp = ans.person_info[i].id;
                if (impl_->wander_map.find(id_temp) == impl_->wander_map.end()) // 库里没有
                    impl_->wander_map[id_temp] = {.sum_time = 0, .last_time = current_time};
                else {
                    impl_->wander_map[id_temp].sum_time += (current_time - impl_->wander_map[id_temp].last_time);
                    impl_->wander_map[id_temp].last_time = current_time;
                }
                ans.person_info[i].sum_time = impl_->wander_map[id_temp].sum_time;
            }

            return ans;
        } catch (const std::exception& ex) {
            const auto timestamp       = date_time::now();
            const std::string time_str = timestamp.to_string("yyyyMMddhhmmsszzz");
            bool flag = mat.write(_config->_configure_directory.dump_img_directory + "/" + time_str + "_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

    bool gx_wander_api::wander_remove_id(int id) {

        if (impl_->camera_id == 0)
            return true;

        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::array<char, 0> arr{};
            auto result = ptr->protocol_ptr.invoke<wander::remove_person_by_index>(ptr->wander_handle,
                wander_remove_person_by_index_param{.id = id, .device_id = impl_->camera_id}, std::span<char>{arr});
            if (result.delete_info == "OK")
                return true;
            return false;
        });
        impl_->wander_map.erase(id);

        return result_pool.get();
    }

    bool gx_wander_api::wander_remove_library() {

        if (impl_->camera_id == 0)
            return true;

        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::array<char, 0> arr{};
            auto result = ptr->protocol_ptr.invoke<wander::remove_library>(
                ptr->wander_handle, wander_remove_library_param{.id = impl_->camera_id}, std::span<char>{arr});
            if (result.delete_info == "ok")
                return true;
            return false;
        });
        impl_->wander_map.clear();
        impl_->camera_id = 0;

        return result_pool.get();
    }

} // namespace glasssix