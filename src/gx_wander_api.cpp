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
            if (api_temp == nullptr) {
                api_temp = new gx_pedestrian_api();//前面已经加载过路径 不用在加
            }
            time = 0;
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

        int camera_id = 0; // 摄像头ID
        int category  = 0; // 0:未分类 1:徘徊 2:越界
        std::chrono::steady_clock::time_point temp_time; // 上一次检测的时间点
        int time      = 0;
        struct person_cache {
            std::int64_t sum_time  = 0;
            std::int64_t last_time = 0;
            int x, y;
        };
        std::unordered_map<std::int32_t, person_cache> wander_map;
        gx_pedestrian_api* api_temp = nullptr;

    private:
#if (GX_EMPOWER_FLAG) 
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_WANDER_V2.1.0";
        std::vector<std::string> empower_algorithm_id_list = {"18", "22"};
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

    //  徘徊检测
    wander_info gx_wander_api::safe_production_wander(const gx_img_api& mat, std::int64_t current_time, int device_id,
        int interval, const abi::vector<pedestrian_info::boxes>& person_list) {
        current_time %= 86400; //   一天86400秒
        if (!impl_->camera_id) {
            impl_->camera_id = device_id;
            impl_->category  = 1;
            impl_->temp_time = std::chrono::steady_clock::now() - std::chrono::seconds(10);
        } else if (impl_->camera_id != device_id)
            throw source_code_aware_runtime_error{"(device_id:" + std::to_string(device_id)
                                                  + ") != (camera_id:" + std::to_string(impl_->camera_id) + ")\n"};
        else if (impl_->category == 2)
            throw source_code_aware_runtime_error{
                "device_id:" + std::to_string(device_id)
                + " \"wander\" and \"wander_limit\" cannot be used at the same time\n"};
        
        std::chrono::steady_clock::time_point now_time = std::chrono::steady_clock::now();
        auto duration         = std::chrono::duration_cast<std::chrono::microseconds>(now_time - impl_->temp_time);
        double detection_fps_ = double{1000000.0}/ duration.count();
        impl_->temp_time      = now_time;

        ///  超过interval秒没出现的人自动删
        std::vector<std::int32_t> v;
        for (auto& it : impl_->wander_map) {
            if ((current_time - it.second.last_time+86400)%86400 >interval)
                v.emplace_back(it.first);
        }
        for (int x : v) {
            impl_->wander_map.erase(x);
            wander_remove_id(x);
        }
        wander_info ans;
        // 过滤掉行人置信度小于person_conf的
        abi::vector<pedestrian_info::boxes> pedestrian_list_temp;
        for (int i = 0; i < person_list.size(); i++) {
            if (person_list[i].score >= _config->_wander_config.person_conf)
                pedestrian_list_temp.emplace_back(person_list[i]);
        }
        //pedestrian_list_temp.emplace_back(
        //    pedestrian_info::boxes{.score = 0.9, .x1 = 0, .y1 = 0, .x2 = mat.get_cols(), .y2 = mat.get_rows()});
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
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
                auto result = ptr->protocol_ptr.invoke<wander::detect>(ptr->wander_handle,
                    wander_detect_param{.instance_guid = "",
                        .format                        = _config->_wander_config.format,
                        .height                        = mat.get_rows(),
                        .width                         = mat.get_cols(),
                        .roi_x                         = 0,
                        .roi_y                         = 0,
                        .roi_width                     = mat.get_cols(),
                        .roi_height                    = mat.get_rows(),
                        .person_list                   = pedestrian_list_temp,
                        .params =
                            wander_detect_param::confidence_params{
                                .current_time            = current_time,
                                .feature_table_size      = _config->_wander_config.feature_table_size,
                                .feature_match_threshold = _config->_wander_config.feature_match_threshold,
                                .device_id               = device_id,
                            }},
                    str);
                return std::move(result.detect_info);
            });
            ans              = result_pool.get();
            for (int i = 0; i < ans.person_info.size(); i++) {
                int id_temp = ans.person_info[i].id;
                if (impl_->wander_map.find(id_temp) == impl_->wander_map.end()) // 库里没有
                    impl_->wander_map[id_temp] = impl::person_cache{.sum_time = 0, .last_time = current_time};
                else {
                    impl_->wander_map[id_temp].sum_time += (current_time - impl_->wander_map[id_temp].last_time+86400)%86400;
                    impl_->wander_map[id_temp].last_time = current_time;
                }
                ans.person_info[i].detection_fps = detection_fps_;
                ans.person_info[i].sum_time = impl_->wander_map[id_temp].sum_time;
            }

            return ans;
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_wander_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

    //  徘徊检测
    wander_info gx_wander_api::safe_production_wander(
        const gx_img_api& mat, std::int64_t current_time, int device_id, int interval) {
        auto person_list = impl_->api_temp->safe_production_pedestrian(mat);
        return safe_production_wander(mat, current_time, device_id, interval, person_list.person_list);
    }

    //  安全生产 越界检测
    wander_limit_info gx_wander_api::safe_production_wander_limit(const gx_img_api& mat, std::int64_t current_time,
        int device_id, const abi::vector<pedestrian_info::boxes>& person_list) {
        if (!impl_->camera_id) {
            impl_->camera_id = device_id;
            impl_->category  = 2;
        } else if (impl_->camera_id != device_id)
            throw source_code_aware_runtime_error{"(device_id:" + std::to_string(device_id)
                                                  + ") != (camera_id:" + std::to_string(impl_->camera_id) + ")\n"};
        else if (impl_->category == 1)
            throw source_code_aware_runtime_error{
                "device_id:" + std::to_string(device_id)
                + " \"wander\" and \"wander_limit\" cannot be used at the same time\n"};

        ///  超过interval秒全部删库
        if (current_time - impl_->time > _config->_wander_limit_config.interval) {
            wander_remove_library();
            impl_->time = current_time;
            //    ///  超过interval秒没出现的人自动删
            //    std::vector<std::int32_t> v;
            //    for (auto& it : impl_->wander_map) {
            //        if (current_time - it.second.last_time > _config->_wander_config.interval)
            //            v.emplace_back(it.first);
            //    }
            //    for (int x : v) {
            //        impl_->wander_map.erase(x);
            //        wander_remove_id(x);
        }
        wander_info temp_ans;
        // 过滤掉行人置信度小于person_conf的
        abi::vector<pedestrian_info::boxes> pedestrian_list_temp;
        for (int i = 0; i < person_list.size(); i++) {
            if (person_list[i].score >= _config->_wander_limit_config.person_conf)
                pedestrian_list_temp.emplace_back(person_list[i]);
        }
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
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
                auto result = ptr->protocol_ptr.invoke<wander::detect>(ptr->wander_handle,
                    wander_detect_param{.instance_guid = "",
                        .format                        = _config->_wander_limit_config.format,
                        .height                        = mat.get_rows(),
                        .width                         = mat.get_cols(),
                        .roi_x                         = 0,
                        .roi_y                         = 0,
                        .roi_width                     = mat.get_cols(),
                        .roi_height                    = mat.get_rows(),
                        .person_list                   = pedestrian_list_temp,
                        .params =
                            wander_detect_param::confidence_params{
                                .current_time            = current_time,
                                .feature_table_size      = _config->_wander_limit_config.feature_table_size,
                                .feature_match_threshold = _config->_wander_limit_config.feature_match_threshold,
                                .device_id               = device_id,
                            }},
                    str);
                return std::move(result.detect_info);
            });
            temp_ans         = result_pool.get();
            wander_limit_info ans(temp_ans);
            for (int i = 0; i < ans.person_info.size(); i++) {
                int id_temp = ans.person_info[i].id;
                int xx      = ans.person_info[i].x1 + ans.person_info[i].x2 >> 1;
                int yy      = ans.person_info[i].y2;
                if (impl_->wander_map.find(id_temp) == impl_->wander_map.end()) // 库里没有
                {
                    impl_->wander_map[id_temp] =
                        impl::person_cache{.sum_time = 0, .last_time = current_time, .x = xx, .y = yy};
                    ans.segment_info.emplace_back(wander_limit_info::segment{.x1 = xx, .y1 = yy, .x2 = xx, .y2 = yy});
                } else {
                    ans.segment_info.emplace_back(wander_limit_info::segment{
                        .x1 = impl_->wander_map[id_temp].x, .y1 = impl_->wander_map[id_temp].y, .x2 = xx, .y2 = yy});
                    impl_->wander_map[id_temp].x = xx;
                    impl_->wander_map[id_temp].y = yy;
                    impl_->wander_map[id_temp].sum_time += (current_time - impl_->wander_map[id_temp].last_time);
                    impl_->wander_map[id_temp].last_time = current_time;
                }
            }

            return ans;
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_wander_limit_dump.jpg");
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
            impl_->wander_map.erase(id);
            if (result.delete_info == "OK")
                return true;
            return false;
        });

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
            impl_->wander_map.clear();
            impl_->camera_id = 0;
            if (result.delete_info == "ok")
                return true;
            return false;
        });

        return result_pool.get();
    }

} // namespace glasssix