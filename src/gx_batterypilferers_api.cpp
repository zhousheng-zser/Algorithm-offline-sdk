#include "gx_batterypilferers_api.hpp"

#include "sdk_share.hpp"

#include <queue>

namespace glasssix {

    gx_batterypilferers_api::gx_batterypilferers_api() : impl_{std::make_unique<impl>()} {}
    gx_batterypilferers_api::gx_batterypilferers_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_batterypilferers_api::~gx_batterypilferers_api() {}
    gx_batterypilferers_api::gx_batterypilferers_api(gx_batterypilferers_api&&) noexcept            = default;
    gx_batterypilferers_api& gx_batterypilferers_api::operator=(gx_batterypilferers_api&&) noexcept = default;
    class gx_batterypilferers_api::impl {
    public:
        void init() {
            mat_list.clear();
            cnt         = 0;
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

        std::vector<gx_img_api> mat_list;
        std::int64_t cnt;

    private:
        secret_key_empower empower;
        std::string empower_key = "";
        std::string empower_algorithm_id =
            share_platform_name + "_" + share_empower_language + "_batterypilferers_V1.0.0";
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

    //  偷电瓶检测
    batterypilferers_info gx_batterypilferers_api::safe_production_batterypilferers(const gx_img_api& mat) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                if (_config->_batterypilferers_config.interval <= 0)
                    throw source_code_aware_runtime_error(
                        U8("Error: The config/batterypilferers.json : interval <= 0"));
                if (_config->_batterypilferers_config.batch <= 0)
                    throw source_code_aware_runtime_error(U8("Error: The config/batterypilferers.json : batch <= 0"));
                int temp_id = (impl_->cnt - 1 + _config->_batterypilferers_config.batch)
                            % _config->_batterypilferers_config.batch;
                if (impl_->cnt && mat.get_cols() != impl_->mat_list[temp_id].get_cols()) // 宽和之前的图片不一样
                    throw source_code_aware_runtime_error(
                        "Error: gx_img_api get_cols: " + std::to_string(mat.get_cols())
                        + " !=  before gx_img_api: " + std::to_string(impl_->mat_list[temp_id].get_cols()));
                if (impl_->cnt && mat.get_rows() != impl_->mat_list[temp_id].get_rows()) // 高和之前的图片不一样
                    throw source_code_aware_runtime_error(
                        "Error: gx_img_api get_rows: " + std::to_string(mat.get_rows())
                        + " !=  before gx_img_api: " + std::to_string(impl_->mat_list[temp_id].get_rows()));
                if (impl_->mat_list.size() < _config->_batterypilferers_config.batch - 1) {
                    impl_->mat_list.emplace_back(mat);
                    impl_->cnt++;
                    return batterypilferers_info{.score = 0, .category = 0};
                } else if (impl_->mat_list.size() == _config->_batterypilferers_config.batch - 1) {
                    impl_->mat_list.emplace_back(mat);
                    impl_->cnt++;
                } else {
                    impl_->mat_list[impl_->cnt % _config->_batterypilferers_config.batch] =
                        mat; // 覆盖之后原本的gx_img_api会自动析构
                    impl_->cnt++;
                }
                if (impl_->cnt % _config->_batterypilferers_config.interval)
                    return batterypilferers_info{.score = 0, .category = 0};
                batterypilferers_info ans;
                std::vector<char> imgBatchDataArr(
                    _config->_batterypilferers_config.batch * mat.get_data_len()); // push batch img to array
                for (int i = impl_->cnt, j = 0; j < _config->_batterypilferers_config.batch; ++i, ++j) {
                    //   构造图片数组
                    int id = i % _config->_batterypilferers_config.batch;
                    std::memcpy(imgBatchDataArr.data() + j * impl_->mat_list[id].get_data_len(),
                        impl_->mat_list[id].get_data(), impl_->mat_list[id].get_data_len());
                }
                std::span<char> str{imgBatchDataArr.data(), imgBatchDataArr.size()};
                auto result = ptr->protocol_ptr.invoke<batterypilferers::detect>(ptr->batterypilferers_handle,
                    batterypilferers_detect_param{.instance_guid = "",
                        .format                                  = _config->_batterypilferers_config.format,
                        .height                                  = mat.get_rows(),
                        .width                                   = mat.get_cols(),
                        .roi_x                                   = 0,
                        .roi_y                                   = 0,
                        .roi_width                               = mat.get_cols(),
                        .roi_height                              = mat.get_rows(),
                        .params =
                            batterypilferers_detect_param::confidence_params{
                                .conf_thres = _config->_batterypilferers_config.conf_thres,
                                .nms_thres  = _config->_batterypilferers_config.nms_thres}},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = write_dump_img(mat, "_batterypilferers_dump.jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }


} // namespace glasssix