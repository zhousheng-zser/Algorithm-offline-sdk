#include "gx_pump_gate_status_api.hpp"

#include "sdk_share.hpp"

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
    pump_gate_room_info{25051128, 40230255, 15013051, 45038115, {720, 206, 777, 255}, {980, 915, 1260, 1010}, 0.16,0.04 ,0.22 },//10
    pump_gate_room_info{25051128, 40230255, 110038077, 130089140, {713, 218, 775, 269}, {890, 1003, 963, 1080},0.04 , 0.01,0.10 },//11
    pump_gate_room_info{25051128, 40230255, 145051102, 125128166, {750, 210, 811, 261}, {936, 1000, 1008, 1080},0.09 , 0.04, 0.10},//12
    pump_gate_room_info{25051128, 40230255, 110000038, 150051128, {631, 210, 692, 264}, {1066, 945, 1187, 1033}, 0.09, 0.04, 0.10}, // 13
    pump_gate_room_info{25051128, 40230255, 00000, 00000, {000, 000, 0000, 0000}, {000, 000, 0000, 0000}, 0,0 ,0 },//14
    pump_gate_room_info{25051128, 40230255, 20000077, 70102128, {704, 123, 792, 198}, {932, 984, 1034, 1080},0.18 ,0.13 ,0.10},//15
    pump_gate_room_info{25051128, 40230255, 165000051, 200051128, {933, 70, 1037, 172}, {780, 994, 862, 1080}, 0.18, 0.13, 0.10}, // 16
    pump_gate_room_info{25051128, 40230255, 95026013, 125153128, {920, 18, 1022, 120}, {1048, 884, 1410, 1080}, 0.18, 0.13, 0.10} // 17

};
    
namespace glasssix {

    gx_pump_gate_status_api::gx_pump_gate_status_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_gate_status_api::gx_pump_gate_status_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_gate_status_api::~gx_pump_gate_status_api() {}
    gx_pump_gate_status_api::gx_pump_gate_status_api(gx_pump_gate_status_api&&) noexcept            = default;
    gx_pump_gate_status_api& gx_pump_gate_status_api::operator=(gx_pump_gate_status_api&&) noexcept = default;
    class gx_pump_gate_status_api::impl {
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
        std::string empower_key = "";
        std::string empower_algorithm_id =
            share_platform_name + "_" + share_empower_language + "_PUMP_GATE_STATUS_V1.1.0";
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

    //  安全生产 大门状态检测
    abi::string gx_pump_gate_status_api::safe_production_pump_gate_status(const gx_img_api& mat, int device_id) {
        if (device_id < 10 || device_id > 17) 
            throw source_code_aware_runtime_error(
                "Error: Invalid device_id: 10 <= device_id <= 17.");
        device_id -= 10;
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                abi::string ans;
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result =
                    ptr->protocol_ptr.invoke<pump_gate_status::detect>(ptr->pump_gate_status_handle,
                        pump_gate_status_detect_param{.instance_guid = "",
                            .format                                  = _config->_pump_gate_status_config.format,
                            .height                                  = mat.get_rows(),
                            .width                                   = mat.get_cols(),
                            .roi_x                                   = 0,
                            .roi_y                                   = 0,
                            .roi_width                               = mat.get_cols(),
                            .roi_height                              = mat.get_rows(),
                            .yellow_hsv_lower                        = rooms_list[device_id].yellow_hsv_lower,
                            .yellow_hsv_upper                        = rooms_list[device_id].yellow_hsv_upper,
                            .gray_hsv_lower                          = rooms_list[device_id].gray_hsv_lower,
                            .gray_hsv_upper                          = rooms_list[device_id].gray_hsv_upper,
                            .rois =
                                pump_gate_status_detect_param::confidence_roi{
                                    .door  = {rooms_list[device_id].door.x1, rooms_list[device_id].door.y1,
                                         rooms_list[device_id].door.x2, rooms_list[device_id].door.y2},
                                    .floor = {rooms_list[device_id].floor.x1, rooms_list[device_id].floor.y1,
                                        rooms_list[device_id].floor.x2, rooms_list[device_id].floor.y2}},
                            .params =
                                pump_gate_status_detect_param::confidence_params{
                                    .door_close_ratio = rooms_list[device_id].door_close_ratio,
                                    .door_open_ratio  = rooms_list[device_id].door_open_ratio,
                                    .floor_ratio      = rooms_list[device_id].floor_ratio}},
                        str);

                ans = std::move(result.security_status);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pump_gate_status_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix