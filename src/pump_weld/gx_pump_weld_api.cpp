#include "gx_pump_weld_api.hpp"
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

                nlohmann::json new_json(pump_weld_new_param{.device = _config->_pump_weld_config.device,
                    .models_directory            = _config->_configure_directory.models_directory});
                char* new_result_c = parser_create_instance("g6.pump_weld.detect_code", new_json.dump().c_str());
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
    gx_pump_weld_api::gx_pump_weld_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_weld_api::gx_pump_weld_api(const std::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_weld_api::~gx_pump_weld_api() {}
    gx_pump_weld_api::gx_pump_weld_api(gx_pump_weld_api&&) noexcept            = default;
    gx_pump_weld_api& gx_pump_weld_api::operator=(gx_pump_weld_api&&) noexcept = default;
    class gx_pump_weld_api::impl {
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
            init();
        }
        impl(const std::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                pool    = new thread_pool(_config->thread_pool_val);
            }
            init();
        }
        ~impl() {}
        pump_weld_info safe_production_pump_weld(const std::vector<gx_img_api>& mat_list, float wlight_conf_thres,
            float candidate_box_width, float candidate_box_height) {
            try {
                auto result_pool = pool->enqueue([&] {
                    std::thread::id id_ = std::this_thread::get_id();
                    if (thread_algo_ptr[id_] == nullptr) {
                        thread_algo_ptr[id_] = new algo_ptr();
                    }
                    auto ptr = thread_algo_ptr[id_];
                    if (_config->_pump_weld_config.batch != mat_list.size())
                        throw std::runtime_error{"Error: The config/pump_weld.json : batch != mat_list.size()"};
                    pump_weld_info ans;
                    std::vector<char> imgBatchDataArr(
                        _config->_pump_weld_config.batch * mat_list[0].get_data_len()); // push batch img to array
                    for (int j = 0; j < _config->_pump_weld_config.batch; ++j) {
                        //   构造图片数组
#if (GX_PLATFORM_NAME != 8)
                        std::memcpy(imgBatchDataArr.data() + j * mat_list[j].get_data_len(), mat_list[j].get_data(),
                            mat_list[j].get_data_len());
#else
                        // std::vector<uchar> img_data(mat_list[j].get_cols() * get_rows() * 3);
                        for (size_t i = 0; i < mat_list[j].get_rows(); i++) {
                            auto row_ptr = mat_list[j].get_row_ptr(i);
                            std::copy(row_ptr, row_ptr + mat_list[j].get_cols() * 3,
                                imgBatchDataArr.data() + j * mat_list[0].get_data_len()
                                    + i * mat_list[j].get_cols() * 3);
                        }
#endif
                    }
                    std::span<char> str{imgBatchDataArr.data(), imgBatchDataArr.size()};
                    nlohmann::json execute_json(pump_weld_detect_param{
                        .algo_params =
                            pump_weld_detect_param::optional_params{
                                .dyparams =
                                    pump_weld_detect_param::optional_params::dyparams_params{
                                        .wmachine_conf_thres  = _config->_pump_weld_config.wmachine_conf_thres,
                                        .wlight_conf_thres    = _config->_pump_weld_config.wlight_conf_thres,
                                        .nms_thres            = _config->_pump_weld_config.nms_thres,
                                        .candidate_box_width  = candidate_box_width,
                                        .candidate_box_height = candidate_box_height,
                                        .batch                = _config->_pump_weld_config.batch}},
                        .data_params = pump_weld_detect_param::basic_params{.height = mat_list[0].get_rows(),
                            .width                                                  = mat_list[0].get_cols(),
                            .num                                                    = _config->_pump_weld_config.batch}
                    });
                    char* execute_result_c = parser_execute(ptr->instance_guid.c_str(), execute_json.dump().c_str(),
                        str.data(), imgBatchDataArr.size(), nullptr, 0);
                    parser_execute_result execute_result = json::parse(execute_result_c).get<parser_execute_result>();
                    if (execute_result.status.code != 0)
                        throw std::runtime_error{execute_result_c};

                    ans = std::move(json::parse(execute_result.result).get<pump_weld_detect_info_result>().detect_info);
                    return ans;
                });
                return result_pool.get();
            } catch (const std::exception& ex) {
                bool flag = 1;
                if (_config->_pump_weld_config.batch != mat_list.size())
                    flag = false;
                for (int i = 0; i < _config->_pump_weld_config.batch && flag; i++)
                    flag = write_dump_img(mat_list[i], "_pump_weld_dump_" + std::to_string(i) + ".jpg",
                        _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }
    private:


#if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key               = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_SMOG_V3.0.0";
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


    //  安全生产 打架检测
    pump_weld_info gx_pump_weld_api::safe_production_pump_weld(const std::vector<gx_img_api>& mat_list,
        float wlight_conf_thres , float candidate_box_width , float candidate_box_height) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_pump_weld( mat_list, wlight_conf_thres ,
             candidate_box_width, candidate_box_height);
    }

} // namespace glasssix