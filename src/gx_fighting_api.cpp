#include "gx_fighting_api.hpp"

#include "sdk_share.hpp"

#include <queue>

namespace glasssix {

    gx_fighting_api::gx_fighting_api() : impl_{std::make_unique<impl>()} {}
    gx_fighting_api::gx_fighting_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_fighting_api::~gx_fighting_api() {}
    gx_fighting_api::gx_fighting_api(gx_fighting_api&&) noexcept            = default;
    gx_fighting_api& gx_fighting_api::operator=(gx_fighting_api&&) noexcept = default;
    class gx_fighting_api::impl {
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
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_FIGHTING_V2.1.0";
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

    //  打架检测
    fighting_info gx_fighting_api::safe_production_fighting(const abi::vector<gx_img_api>& mat_list) {
        try {
            auto result_pool = pool->enqueue([&] {
                std::thread::id id_ = std::this_thread::get_id();
                if (all_thread_algo_ptr[id_] == nullptr) {
                    all_thread_algo_ptr[id_] = new algo_ptr();
                }
                auto ptr = all_thread_algo_ptr[id_];
                if (_config->_fighting_config.batch != mat_list.size())
                    throw source_code_aware_runtime_error(
                        U8("Error: The config/fighting.json : batch != mat_list.size()"));
                fighting_info ans;
                std::vector<char> imgBatchDataArr(
                    _config->_fighting_config.batch * mat_list[0].get_data_len()); // push batch img to array
                for (int j = 0; j < _config->_fighting_config.batch; ++j) {
                    //   构造图片数组
                    std::memcpy(imgBatchDataArr.data() + j * mat_list[j].get_data_len(), mat_list[j].get_data(),
                        mat_list[j].get_data_len());
                }
                std::span<char> str{imgBatchDataArr.data(), imgBatchDataArr.size()};
                auto result = ptr->protocol_ptr.invoke<fighting::detect>(ptr->fighting_handle,
                    fighting_detect_param{.instance_guid = "",
                        .format                          = _config->_fighting_config.format,
                        .height                          = mat_list[0].get_rows(),
                        .width                           = mat_list[0].get_cols()},
                    str);

                ans = std::move(result.detect_info);
                return ans;
            });
            return result_pool.get();
        } catch (const std::exception& ex) {
            bool flag = 1;
            for (int i = 0; i < _config->_fighting_config.batch && flag; i++)
                flag = write_dump_img(mat_list[i], "_fighting_dump_" + std::to_string(i) + ".jpg");
            throw source_code_aware_runtime_error{
                ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
        }
    }
} // namespace glasssix