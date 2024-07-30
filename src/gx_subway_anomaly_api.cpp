#include "gx_subway_anomaly_api.hpp"

#include "sdk_share.hpp"

namespace glasssix {

    gx_subway_anomaly_api::gx_subway_anomaly_api() : impl_{std::make_unique<impl>()} {}
    gx_subway_anomaly_api::gx_subway_anomaly_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_subway_anomaly_api::~gx_subway_anomaly_api() {}
    gx_subway_anomaly_api::gx_subway_anomaly_api(gx_subway_anomaly_api&&) noexcept            = default;
    gx_subway_anomaly_api& gx_subway_anomaly_api::operator=(gx_subway_anomaly_api&&) noexcept = default;
    class gx_subway_anomaly_api::impl {
    public:
        void init() {
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

    private:
#if (GX_EMPOWER_FLAG) 
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version =
            share_platform_name + "_" + share_empower_language + "_subway_anomaly_V2.0.0";
        std::vector<std::string> empower_algorithm_id_list = {"24"};
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

    //  地铁异常检测
    subway_anomaly_info gx_subway_anomaly_api::safe_production_subway_anomaly(
        const gx_img_api& mat, const std::vector<subway_anomaly_roi>& rois, int type) {
        try {

            if (type != 0 && type != 1)
                throw source_code_aware_runtime_error(U8("Error: safe_production_subway_anomaly : type != 0 && type != 1"));

            if (type == 0 && rois.size() != 2)
                throw source_code_aware_runtime_error(
                    U8("Error: safe_production_subway_anomaly : type = 0, but rois.size() != 2"));

            if (type == 1 && rois.size() !=1)
                throw source_code_aware_runtime_error(
                    U8("Error: safe_production_subway_anomaly : type = 1, but rois.size() != 1"));

            subway_anomaly_roi transverse, vertical;//横的和竖的roi
            if (type == 0) {
                transverse = rois[0].w > rois[1].w ? rois[0] : rois[1];
                vertical   = rois[0].h > rois[1].h ? rois[0] : rois[1];
            }
            else {
                transverse = {};
                vertical = rois[0];
            }

            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                subway_anomaly_info ans;
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
                auto result = ptr->protocol_ptr.invoke<subway_anomaly::detect>(ptr->subway_anomaly_handle,
                    subway_anomaly_detect_param{.instance_guid = "",
                        .format                                = _config->_subway_anomaly_config.format,
                        .height                                = mat.get_rows(),
                        .width                                 = mat.get_cols(),
                        .roi_x                                 = vertical.x,
                        .roi_y                                 = vertical.y,
                        .roi_width                             = vertical.w,
                        .roi_height                            = vertical.h,
                        .params = subway_anomaly_detect_param::confidence_params{.type = type,
                            .conf_thres              = _config->_subway_anomaly_config.conf_thres,
                            .normal_closedoor_thresh = _config->_subway_anomaly_config.normal_closedoor_thresh,
                            .transverse_x            = transverse.x,
                            .transverse_y            = transverse.y,
                            .transverse_w            = transverse.w,
                            .transverse_h            = transverse.h}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_subway_anomaly_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }

} // namespace glasssix