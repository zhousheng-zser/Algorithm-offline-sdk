#include "gx_wander_api.hpp"
#include "gx_pedestrian_api.hpp"
#include "thread_pool.hpp"
#include "../sdk_share.hpp"
#include "config.hpp"
#include <unordered_map>
namespace glasssix {
    config* _config = nullptr;
    
    class algo_ptr {
    public:
        std::string instance_guid = ""; 
        algo_ptr() {
            try {
                char* init_result_c = parser_init_plugin(_config->_configure_directory.directory.c_str(), "license");
                parser_init_result init_result = json::parse(init_result_c).get<parser_init_result>();
                if (init_result.status.code != 0)
                    throw std::runtime_error{init_result_c};

                nlohmann::json new_json(wander_new_param{.device = _config->_wander_config.device,
                    .models_directory            = _config->_configure_directory.models_directory
                    });
                char* new_result_c = parser_create_instance("g6.wander.detect_code", new_json.dump().c_str());
                parser_create_instance_result new_result =
                    json::parse(new_result_c).get<parser_create_instance_result>();
                if (new_result.status.code != 0)
                    throw std::runtime_error{new_result_c};
                instance_guid = new_result.instance_id;
            } catch (const std::exception& ex) {
                throw std::runtime_error{ex.what()};
            }
        }
        ~algo_ptr() {
            // 释放模型
        }
    };

    std::unordered_map<std::thread::id, algo_ptr*> thread_algo_ptr;
    thread_pool* pool = nullptr;
    gx_wander_api::gx_wander_api() : impl_{std::make_unique<impl>()} {}
    gx_wander_api::gx_wander_api(const std::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_wander_api::~gx_wander_api() {}
    gx_wander_api::gx_wander_api(gx_wander_api&&) noexcept            = default;
    gx_wander_api& gx_wander_api::operator=(gx_wander_api&&) noexcept = default;
    class gx_wander_api::impl {
    public:
        void init() {
#if (GX_EMPOWER_FLAG)
            for (int i = 0; i < empower_algorithm_id_list.size(); ++i) {
                try {
                    auto license = std::from_std_string(_config->_configure_directory.license_directory);
                    empower_key  = get_empower_key(license);
                    auto number  = std::from_std_string(_config->_configure_directory.empower_serial_number);
                    empower.set_serial_number(number);
                    empower.set_algorithm_id(empower_algorithm_id_list[i]);
                    empower.set_license(empower_key.c_str());
                    empower.evaluate_license(empower_Callback, nullptr);
                    break; // 不崩就直接跳出去
                } catch (const std::exception& ex) {
                    if (i == empower_algorithm_id_list.size() - 1) // 最后一个都崩就抛异常
                        throw std::runtime_error{ex.what() + std::string{": empower_key install error"}};
                }
            }
#endif
        }
        impl() {
            if (_config == nullptr) {
                _config = new config();
                pool    = new thread_pool(_config->thread_pool_val);
            }
            if (api_temp == nullptr) {
                api_temp = new gx_pedestrian_api();
            }
            init();
        }
        impl(const std::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                pool    = new thread_pool(_config->thread_pool_val);
            }
            if (api_temp == nullptr) {
                api_temp = new gx_pedestrian_api(config_path);
            }
            init();
        }
        ~impl() {}

        int camera_id = 0; // 摄像头ID
        int category  = 0; // 0:未分类 1:徘徊 2:越界
        std::chrono::steady_clock::time_point temp_time; // 上一次检测的时间点
        int time = 0;
        struct person_cache {
            std::int64_t sum_time  = 0;
            std::int64_t last_time = 0;
            int x, y;
        };
        std::unordered_map<int, person_cache> wander_map;
        gx_pedestrian_api* api_temp = nullptr;
        wander_info safe_production_wander(const gx_img_api& mat, std::int64_t current_time, int device_id,
            int interval, const std::vector<pedestrian_info::boxes>& person_list) {
            current_time %= 86400; //   一天86400秒
            if (!camera_id) {
                camera_id = device_id;
                category  = 1;
                temp_time = std::chrono::steady_clock::now() - std::chrono::seconds(10);
            } else if (camera_id != device_id)
                throw std::runtime_error{
                    "(device_id:" + std::to_string(device_id) + ") != (camera_id:" + std::to_string(camera_id) + ")\n"};
            else if (category == 2)
                throw std::runtime_error{"device_id:" + std::to_string(device_id)
                                         + " \"wander\" and \"wander_limit\" cannot be used at the same time\n"};

            std::chrono::steady_clock::time_point now_time = std::chrono::steady_clock::now();
            auto duration         = std::chrono::duration_cast<std::chrono::microseconds>(now_time - temp_time);
            double detection_fps_ = double{1000000.0} / duration.count();
            temp_time      = now_time;

            ///  超过interval秒没出现的人自动删
            std::vector<std::int32_t> v;
            for (auto& it : wander_map) {
                if ((current_time - it.second.last_time + 86400) % 86400 > interval)
                    v.emplace_back(it.first);
            }
            for (int x : v) {
                wander_map.erase(x);
                wander_remove_id(x);
            }
            wander_info ans;
            // 过滤掉行人置信度小于person_conf的
            std::vector<pedestrian_info::boxes> pedestrian_list_temp;
            for (int i = 0; i < person_list.size(); i++) {
                if (person_list[i].score >= _config->_wander_config.person_conf)
                    pedestrian_list_temp.emplace_back(person_list[i]);
            }
            // pedestrian_list_temp.emplace_back(
            //     pedestrian_info::boxes{.score = 0.9, .x1 = 0, .y1 = 0, .x2 = mat.get_cols(), .y2 = mat.get_rows()});


            try {
                auto result_pool = pool->enqueue([&] {
                    std::thread::id id_ = std::this_thread::get_id();
                    if (thread_algo_ptr[id_] == nullptr) {
                        thread_algo_ptr[id_] = new algo_ptr();
                    }
                    auto ptr = thread_algo_ptr[id_];
                    wander_info ans;
#if (GX_PLATFORM_NAME != 8)
                    std::span<char> str{
                        reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
#else
                    std::vector<uchar> img_data(mat.get_cols() * mat.get_rows() * 3);
                    for (int i = 0; i < mat.get_rows(); i++) {
                        auto row_ptr = mat.get_row_ptr(i);
                        std::copy(row_ptr, row_ptr + mat.get_cols() * 3, img_data.data() + i * mat.get_cols() * 3);
                    }
                    std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(img_data.data())),
                        mat.get_cols() * mat.get_rows() * 3};
#endif

                    nlohmann::json execute_json(wander_detect_param{
                        .algo_params =
                            wander_detect_param::optional_params{
                                .dyparams =
                                    wander_detect_param::optional_params::dyparams_params{
                                        .pedestrian_info_list = pedestrian_list_temp,
                                        .current_time            = current_time,
                                        .feature_table_size      = _config->_wander_config.feature_table_size,
                                        .feature_match_threshold = _config->_wander_config.feature_match_threshold,
                                        .device_id               = device_id}},
                        .data_params =
                            wander_detect_param::basic_params{.height = mat.get_rows(), .width = mat.get_cols()}
                    });
                    char* execute_result_c = parser_execute(ptr->instance_guid.c_str(), execute_json.dump().c_str(),
                        str.data(), 3ll * mat.get_rows() * mat.get_cols(), nullptr, 0);
                    parser_execute_result execute_result = json::parse(execute_result_c).get<parser_execute_result>();
                    if (execute_result.status.code != 0)
                        throw std::runtime_error{execute_result_c};

                    ans = std::move(json::parse(execute_result.result).get<wander_detect_info_result>().detect_info);
                    return ans;
                });
                return result_pool.get();
            } catch (const std::exception& ex) {
                bool flag = write_dump_img(mat, "_wander_dump.jpg", _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }
        wander_limit_info safe_production_wander_limit(const gx_img_api& mat, std::int64_t current_time, int device_id,
            const std::vector<pedestrian_info::boxes>& person_list) {
            
            if (!camera_id) {
                camera_id = device_id;
                category  = 2;
            } else if (camera_id != device_id)
                throw std::runtime_error{
                    "(device_id:" + std::to_string(device_id) + ") != (camera_id:" + std::to_string(camera_id) + ")\n"};
            else if (category == 1)
                throw std::runtime_error{"device_id:" + std::to_string(device_id)
                                         + " \"wander\" and \"wander_limit\" cannot be used at the same time\n"};

            ///  超过interval秒全部删库
            if (current_time - time > _config->_wander_limit_config.interval) {
                wander_remove_library();
                time = current_time;
            }

            wander_info temp_ans;
            // 过滤掉行人置信度小于person_conf的
            std::vector<pedestrian_info::boxes> pedestrian_list_temp;
            for (int i = 0; i < person_list.size(); i++) {
                if (person_list[i].score >= _config->_wander_limit_config.person_conf)
                    pedestrian_list_temp.emplace_back(person_list[i]);
            }

            try {
                auto result_pool = pool->enqueue([&] {
                    std::thread::id id_ = std::this_thread::get_id();
                    if (thread_algo_ptr[id_] == nullptr) {
                        thread_algo_ptr[id_] = new algo_ptr();
                    }
                    auto ptr = thread_algo_ptr[id_];
#if (GX_PLATFORM_NAME != 8)
                    std::span<char> str{
                        reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
#else
                    std::vector<uchar> img_data(mat.get_cols() * mat.get_rows() * 3);
                    for (int i = 0; i < mat.get_rows(); i++) {
                        auto row_ptr = mat.get_row_ptr(i);
                        std::copy(row_ptr, row_ptr + mat.get_cols() * 3, img_data.data() + i * mat.get_cols() * 3);
                    }
                    std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(img_data.data())),
                        mat.get_cols() * mat.get_rows() * 3};
#endif
                    nlohmann::json execute_json(wander_detect_param{
                        .algo_params =
                            wander_detect_param::optional_params{
                                .dyparams =
                                    wander_detect_param::optional_params::dyparams_params{
                                        .pedestrian_info_list = pedestrian_list_temp,
                                        .current_time         = current_time,
                                        .feature_table_size   = _config->_wander_limit_config.feature_table_size,
                                        .feature_match_threshold =
                                            _config->_wander_limit_config.feature_match_threshold,
                                        .device_id = device_id}},
                        .data_params =
                            wander_detect_param::basic_params{.height = mat.get_rows(), .width = mat.get_cols()}});
                    char* execute_result_c = parser_execute(ptr->instance_guid.c_str(), execute_json.dump().c_str(),
                        str.data(), 3ll * mat.get_rows() * mat.get_cols(), nullptr, 0);
                    parser_execute_result execute_result = json::parse(execute_result_c).get<parser_execute_result>();
                    if (execute_result.status.code != 0)
                        throw std::runtime_error{execute_result_c};
                    return std::move(json::parse(execute_result.result).get<wander_detect_info_result>().detect_info);
                });
                temp_ans = result_pool.get();
                wander_limit_info ans(temp_ans);
                for (int i = 0; i < ans.person_info.size(); i++) {
                    int id_temp = ans.person_info[i].id;
                    int xx      = ans.person_info[i].x1 + ans.person_info[i].x2 >> 1;
                    int yy      = ans.person_info[i].y2;
                    if (wander_map.find(id_temp) == wander_map.end()) // 库里没有
                    {
                        wander_map[id_temp] =
                            impl::person_cache{.sum_time = 0, .last_time = current_time, .x = xx, .y = yy};
                        ans.segment_info.emplace_back(
                            wander_limit_info::segment{.x1 = xx, .y1 = yy, .x2 = xx, .y2 = yy});
                    } else {
                        ans.segment_info.emplace_back(wander_limit_info::segment{
                            .x1 = wander_map[id_temp].x, .y1 = wander_map[id_temp].y, .x2 = xx, .y2 = yy});
                        wander_map[id_temp].x = xx;
                        wander_map[id_temp].y = yy;
                        wander_map[id_temp].sum_time += (current_time - wander_map[id_temp].last_time);
                        wander_map[id_temp].last_time = current_time;
                    }
                }
                return ans;

            } catch (const std::exception& ex) {
                bool flag = write_dump_img(mat, "_wander_dump.jpg", _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }
        bool wander_remove_id(int id) {
            return true; 
            /// AlgorithmZoo没实现
        }
        bool wander_remove_library() {
            return true; 
            /// AlgorithmZoo没实现
        }

    private:


#if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key               = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_wander_V3.0.0";
        std::vector<std::string> empower_algorithm_id_list = {"15"};
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


    //  安全生产 徘徊检测
    wander_info gx_wander_api::safe_production_wander(
        const gx_img_api& mat, long long current_time, int device_id, int interval) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        auto person_list = impl_->api_temp->safe_production_pedestrian(mat);
        return impl_->safe_production_wander(mat, current_time, device_id, interval, person_list.person_list);
    }
    //  安全生产 徘徊检测
    wander_info gx_wander_api::safe_production_wander(const gx_img_api& mat, long long current_time, int device_id,
        int interval, const std::vector<pedestrian_info::boxes>& person_list) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_wander(mat,current_time,device_id, interval,person_list);
    }
    //  安全生产 越界检测
    wander_limit_info gx_wander_api::safe_production_wander_limit(const gx_img_api& mat, long long current_time,
        int device_id, const std::vector<pedestrian_info::boxes>& person_list) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_wander_limit(mat, current_time, device_id, person_list);
    }
    bool gx_wander_api::wander_remove_id(int id) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->wander_remove_id(id);
    }
    bool gx_wander_api::wander_remove_library() {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->wander_remove_library();
    }
} // namespace glasssix