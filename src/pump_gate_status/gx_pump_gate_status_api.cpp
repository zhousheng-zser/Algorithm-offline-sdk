#include "gx_pump_gate_status_api.hpp"
#include "thread_pool.hpp"
#include "../sdk_share.hpp"
#include "config.hpp"
#include <unordered_map>


struct pump_gate_room_info {
    std::int32_t yellow_hsv_lower;
    std::int32_t yellow_hsv_upper;
    std::int32_t gray_hsv_lower;
    std::int32_t gray_hsv_upper;
    struct boxes_door {
        std::int32_t x1; // 检出框体左上坐标x
        std::int32_t y1; // 检出框体左上坐标y
        std::int32_t x2; // 检出框体右下坐标x
        std::int32_t y2; // 检出框体右下坐标y
    } door;
    struct boxes_floor {
        std::int32_t x1; // 检出框体左上坐标x
        std::int32_t y1; // 检出框体左上坐标y
        std::int32_t x2; // 检出框体右下坐标x
        std::int32_t y2; // 检出框体右下坐标y
    } floor;

    float door_close_ratio;
    float door_open_ratio;
    float floor_ratio;
};
std::vector<pump_gate_room_info> rooms_list = {
    pump_gate_room_info{20051102, 40230255, 15013051, 45038115, {720, 206, 777, 255}, {980, 915, 1260, 1010}, 0.16,0.04 ,0.10 },//10
    pump_gate_room_info{20051102, 40230255, 110038077, 130089140, {713, 218, 775, 269}, {890, 1003, 963, 1080},0.04 , 0.01,0.10 },//11
    pump_gate_room_info{20051102, 40230255, 105051102, 145128166, {750, 210, 811, 261}, {936, 1000, 1008, 1080},0.09 , 0.04, 0.08},//12
    pump_gate_room_info{20051102, 40230255, 110000038, 150051128, {631, 210, 692, 264}, {1066, 945, 1187, 1033}, 0.09, 0.04, 0.10}, // 13
    pump_gate_room_info{20051102, 40230255, 00000, 00000, {000, 000, 0000, 0000}, {000, 000, 0000, 0000}, 0,0 ,0 },//14
    pump_gate_room_info{20051102, 40230255, 20000077, 70102128, {704, 123, 792, 198}, {932, 984, 1034, 1080},0.18 ,0.13 ,0.10},//15
    pump_gate_room_info{20051102, 40230255, 165000051, 200051128, {933, 70, 1037, 172}, {780, 994, 862, 1080}, 0.18, 0.13, 0.10}, // 16
    pump_gate_room_info{20051102, 40230255, 95026013, 125153128, {920, 18, 1022, 120}, {1048, 884, 1410, 1080}, 0.18, 0.13, 0.10} // 17
};


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

                nlohmann::json new_json(pump_gate_status_new_param{.device = _config->_pump_gate_status_config.device,
                    .models_directory            = _config->_configure_directory.models_directory});
                char* new_result_c = parser_create_instance("g6.pump_gate_status.detect_code", new_json.dump().c_str());
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
    gx_pump_gate_status_api::gx_pump_gate_status_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_gate_status_api::gx_pump_gate_status_api(const std::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_gate_status_api::~gx_pump_gate_status_api() {}
    gx_pump_gate_status_api::gx_pump_gate_status_api(gx_pump_gate_status_api&&) noexcept            = default;
    gx_pump_gate_status_api& gx_pump_gate_status_api::operator=(gx_pump_gate_status_api&&) noexcept = default;
    class gx_pump_gate_status_api::impl {
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
        pump_gate_status_info safe_production_pump_gate_status(const gx_img_api& mat, int device_id) {
            if (device_id < 10 || device_id > 17)
                throw std::runtime_error("Error: Invalid device_id: 10 <= device_id <= 17.");
            device_id -= 10;
            try {
                auto result_pool = pool->enqueue([&] {
                    std::thread::id id_ = std::this_thread::get_id();
                    if (thread_algo_ptr[id_] == nullptr) {
                        thread_algo_ptr[id_] = new algo_ptr();
                    }
                    auto ptr = thread_algo_ptr[id_];
                    pump_gate_status_info ans;
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

                    nlohmann::json execute_json(
                        pump_gate_status_detect_param{
                            .algo_params =
                                pump_gate_status_detect_param::optional_params{
                                    .dyparams =
                                        pump_gate_status_detect_param::optional_params::dyparams_params{
                                            .door_close_ratio = rooms_list[device_id].door_close_ratio,
                                            .door_open_ratio  = rooms_list[device_id].door_open_ratio,
                                            .floor_ratio      = rooms_list[device_id].floor_ratio,
                                            .device_id        = device_id + 10},
                                    .rois =
                                        pump_gate_status_detect_param::optional_params::gate_roi{
                                            .door  = {rooms_list[device_id].door.x1, rooms_list[device_id].door.y1,
                                                 rooms_list[device_id].door.x2, rooms_list[device_id].door.y2},
                                            .floor = {rooms_list[device_id].floor.x1, rooms_list[device_id].floor.y1,
                                                rooms_list[device_id].floor.x2, rooms_list[device_id].floor.y2}},
                                    .yellow_hsv_lower = rooms_list[device_id].yellow_hsv_lower,
                                    .yellow_hsv_upper = rooms_list[device_id].yellow_hsv_upper,
                                    .gray_hsv_lower   = rooms_list[device_id].gray_hsv_lower,
                                    .gray_hsv_upper   = rooms_list[device_id].gray_hsv_upper},
                            .data_params = pump_gate_status_detect_param::basic_params{
                                .height = mat.get_rows(), .width = mat.get_cols()}});
                    char* execute_result_c = parser_execute(ptr->instance_guid.c_str(), execute_json.dump().c_str(),
                        str.data(), 3ll * mat.get_rows() * mat.get_cols(), nullptr, 0);
                    parser_execute_result execute_result = json::parse(execute_result_c).get<parser_execute_result>();
                    if (execute_result.status.code != 0)
                        throw std::runtime_error{execute_result_c};
                    printf("大门的结果  execute_result_c = %s\n", execute_result_c);
                    ans = std::move(json::parse(execute_result.result).get<pump_gate_status_detect_info_result>().detect_info);
                    return ans;
                });
                return result_pool.get();
            } catch (const std::exception& ex) {
                bool flag = write_dump_img(mat, "_pump_gate_status_dump.jpg", _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }
    private:


#if (GX_EMPOWER_FLAG)
        secret_key_empower empower;
        std::string empower_key               = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_pump_gate_status_V3.0.0";
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


    //  泵业大门关闭状态检测
    pump_gate_status_info gx_pump_gate_status_api::safe_production_pump_gate_status(const gx_img_api& mat, int device_id) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_pump_gate_status(mat, device_id);
    }

} // namespace glasssix