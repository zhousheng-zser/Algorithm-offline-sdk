#include "gx_pump_pumptop_person_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {
    gx_pump_pumptop_person_api::gx_pump_pumptop_person_api() : impl_{std::make_unique<impl>()} {}
    gx_pump_pumptop_person_api::gx_pump_pumptop_person_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_pump_pumptop_person_api::~gx_pump_pumptop_person_api() {}
    gx_pump_pumptop_person_api::gx_pump_pumptop_person_api(gx_pump_pumptop_person_api&&) noexcept            = default;
    gx_pump_pumptop_person_api& gx_pump_pumptop_person_api::operator=(gx_pump_pumptop_person_api&&) noexcept = default;
    class gx_pump_pumptop_person_api::impl {
    public:
        void init() {
            if (api_temp == nullptr) {
                api_temp = new gx_pedestrian_api();
            }
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
        gx_pedestrian_api* api_temp = nullptr;

    private:
        secret_key_empower empower;
        std::string empower_key = "";
        std::string empower_algorithm_id =
            share_platform_name + "_" + share_empower_language + "_PUMP_PUMPTOP_PERSON_V1.2.2";

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

    //  泵顶行人检测
    pump_pumptop_person_info gx_pump_pumptop_person_api::safe_production_pump_pumptop_person(
        const gx_img_api& mat, const abi::vector<pedestrian_info::boxes>& person_list) {
        pump_pumptop_person_info ans;
        // 过滤掉行人置信度小于person_conf的
        abi::vector<pedestrian_info::boxes> person_list_temp;
        for (int i = 0; i < person_list.size(); i++) {
            if (person_list[i].score >= _config->_pump_pumptop_person_config.conf_thres)
                person_list_temp.emplace_back(person_list[i]);
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
                auto result = ptr->protocol_ptr.invoke<pump_pumptop_person::detect>(ptr->pump_pumptop_person_handle,
                    pump_pumptop_person_detect_param{.instance_guid = "",
                        .format                                     = _config->_pump_pumptop_person_config.format,
                        .height                                     = mat.get_rows(),
                        .width                                      = mat.get_cols(),
                        .person_list                                = person_list_temp,
                        .params =
                            pump_pumptop_person_detect_param::confidence_params{
                                .person_area_ratio_thres =
                                    _config->_pump_pumptop_person_config.person_area_ratio_thres}},
                    str);
                return std::move(result.detect_info);
            });
            ans              = result_pool.get();
            return ans;
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_pump_pumptop_person_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

    //  泵顶行人检测
    pump_pumptop_person_info gx_pump_pumptop_person_api::safe_production_pump_pumptop_person(const gx_img_api& mat) {
        auto person_list = impl_->api_temp->safe_production_pedestrian(mat);
        return safe_production_pump_pumptop_person(mat, person_list.person_list);
    }

} // namespace glasssix