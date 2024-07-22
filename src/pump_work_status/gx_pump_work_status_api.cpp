#include "gx_pump_work_status_api.hpp"

#include "../sdk_share.hpp"
#include "config.hpp"
#include "thread_pool.hpp"

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

                nlohmann::json new_json(pump_work_status_new_param{.device = _config->_pump_work_status_config.device,
                    .models_directory = _config->_configure_directory.models_directory});
                char* new_result_c = parser_create_instance("g6.pump_work_status.detect_code", new_json.dump().c_str());
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
    gx_pump_work_status_api::gx_pump_work_status_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_work_status_api::gx_pump_work_status_api(const std::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_work_status_api::~gx_pump_work_status_api() {}
    gx_pump_work_status_api::gx_pump_work_status_api(gx_pump_work_status_api&&) noexcept            = default;
    gx_pump_work_status_api& gx_pump_work_status_api::operator=(gx_pump_work_status_api&&) noexcept = default;
    class gx_pump_work_status_api::impl {
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
        pump_work_status_info safe_production_pump_work_status(
            const gx_img_api& mat, int big_paint_room, const std::vector<pump_work_status_point>& polygon) {
            if (polygon.size() < 3)
                throw std::runtime_error("Error: Invalid polygon: polygon.size < 3.");
            if (big_paint_room != 1 && big_paint_room != 0)
                throw std::runtime_error("Error: Invalid big_paint_room: big_paint_room != 1 && big_paint_room !=0.");
            try {
                auto result_pool = pool->enqueue([&] {
                    std::thread::id id_ = std::this_thread::get_id();
                    if (thread_algo_ptr[id_] == nullptr) {
                        thread_algo_ptr[id_] = new algo_ptr();
                    }
                    auto ptr = thread_algo_ptr[id_];
                    pump_work_status_info ans;
                    std::vector<int> mask_list;
                    for (int i = 0; i < polygon.size(); i++) {
                        mask_list.emplace_back(polygon[i].x);
                        mask_list.emplace_back(polygon[i].y);
                    }
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

                    nlohmann::json execute_json(pump_work_status_detect_param{
                        .algo_params =
                            pump_work_status_detect_param::optional_params{
                                .dyparams =
                                    pump_work_status_detect_param::optional_params::dyparams_params{
                                        .big_paint_room = big_paint_room, .mask_roi = mask_list}},
                        .data_params = pump_work_status_detect_param::basic_params{
                            .height = mat.get_rows(), .width = mat.get_cols()}});
                    char* execute_result_c = parser_execute(ptr->instance_guid.c_str(), execute_json.dump().c_str(),
                        str.data(), 3ll * mat.get_rows() * mat.get_cols(), nullptr, 0);
                    parser_execute_result execute_result = json::parse(execute_result_c).get<parser_execute_result>();
                    if (execute_result.status.code != 0)
                        throw std::runtime_error{execute_result_c};

                    ans = std::move(
                        json::parse(execute_result.result).get<pump_work_status_detect_info_result>().detect_info);
                    return ans;
                });
                return result_pool.get();
            } catch (const std::exception& ex) {
                bool flag =
                    write_dump_img(mat, "_pump_work_status_dump.jpg", _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }

    private:
#if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_pump_work_status_V3.0.0";
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


    //  泵业 工作状态检测
    pump_work_status_info gx_pump_work_status_api::safe_production_pump_work_status(
        const gx_img_api& mat, int big_paint_room, const std::vector<pump_work_status_point>& polygon) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_pump_work_status(mat, big_paint_room, polygon);
    }

} // namespace glasssix