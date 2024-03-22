#include "gx_pump_work_status_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_pump_work_status_api::gx_pump_work_status_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_work_status_api::gx_pump_work_status_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_work_status_api::~gx_pump_work_status_api() {}
    gx_pump_work_status_api::gx_pump_work_status_api(gx_pump_work_status_api&&) noexcept            = default;
    gx_pump_work_status_api& gx_pump_work_status_api::operator=(gx_pump_work_status_api&&) noexcept = default;
    class gx_pump_work_status_api::impl {
    public:
        void init() {
            try {
                empower_key = get_empower_key(_config->_configure_directory.license_directory);
                empower.set_serial_number(_config->_configure_directory.empower_serial_number);
                empower.set_algorithm_id(empower_algorithm_id);
                empower.set_license(empower_key.c_str());
                empower.evaluate_license(empower_Callback, nullptr);
                
            } catch (const std::exception& ex) {
                throw source_code_aware_runtime_error {
                    ex.what() + std::string{": empower_key install error"}};
            }
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
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_PUMP_WORK_STATUS_V1.0.1";
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

    //  安全生产 定制工作状态检测
    abi::string gx_pump_work_status_api::safe_production_pump_work_status(
        const gx_img_api& mat, int big_paint_room, const abi::vector<pump_work_status_point>& polygon) {
        if (polygon.size() <3)
            throw source_code_aware_runtime_error("Error: Invalid polygon: polygon.size < 3.");
        if (big_paint_room != 1 && big_paint_room !=0)
            throw source_code_aware_runtime_error("Error: Invalid big_paint_room: big_paint_room != 1 && big_paint_room !=0.");
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                abi::string ans;
                abi::vector<std::int32_t> mask_list;
                for (int i = 0; i < polygon.size(); i++) {
                    mask_list.emplace_back(polygon[i].x);
                    mask_list.emplace_back(polygon[i].y);
                }
                std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
                auto result = ptr->protocol_ptr.invoke<pump_work_status::detect>(ptr->pump_work_status_handle,
                    pump_work_status_detect_param{.instance_guid = "",
                        .format                                  = _config->_pump_work_status_config.format,
                        .height                                  = mat.get_rows(),
                        .width                                   = mat.get_cols(),
                        .mask_roi                                = mask_list,
                        .params = pump_work_status_detect_param::confidence_params{.big_paint_room = big_paint_room}},
                    str);

                ans = std::move(result.security_status);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pump_work_status_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix