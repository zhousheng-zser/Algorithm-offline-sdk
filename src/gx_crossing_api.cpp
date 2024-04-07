#include "gx_crossing_api.hpp"

#include "sdk_share.hpp"

#include <opencv2/opencv.hpp>

namespace glasssix {

    gx_crossing_api::gx_crossing_api() : impl_{std::make_unique<impl>()} {}
    gx_crossing_api::gx_crossing_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_crossing_api::~gx_crossing_api() {}
    gx_crossing_api::gx_crossing_api(gx_crossing_api&&) noexcept            = default;
    gx_crossing_api& gx_crossing_api::operator=(gx_crossing_api&&) noexcept = default;
    class gx_crossing_api::impl {
    public:
        void init() {
            if (api_temp == nullptr) {
                api_temp = new gx_posture_api();
            }
            for (int i = 0; i < empower_algorithm_id_list.size(); ++i) {
                try {
                    empower_key = get_empower_key(_config->_configure_directory.license_directory);
                    empower.set_serial_number(_config->_configure_directory.empower_serial_number);
                    empower.set_algorithm_id(empower_algorithm_id_list[i]);
                    empower.set_license(empower_key.c_str());
                    empower.evaluate_license(empower_Callback, nullptr);
                    break; // 不崩就直接跳出去
                } catch (const std::exception& ex) {
                    if (i == empower_algorithm_id_list.size() - 1) // 最后一个都崩就抛异常
                        throw source_code_aware_runtime_error{ex.what() + std::string{": empower_key install error"}};
                }
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
        gx_posture_api* api_temp = nullptr;

    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_version = share_platform_name + "_" + share_empower_language + "_CROSSING_V1.1.1";
        std::vector<std::string> empower_algorithm_id_list = {"35"};
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


    inline bool check(posture_info& val) {
        int person_height = val.location.y2 - val.location.y1;
        int condition2    = std::abs(val.key_points[15].y - val.key_points[16].y);

        int height_diff_1 = int(abs(val.key_points[13].y - val.key_points[5].y));
        int height_diff_2 = int(abs(val.key_points[14].y - val.key_points[6].y));
        int diff_limit    = 0.4 * person_height;

        if ((height_diff_1 < diff_limit || height_diff_2 < diff_limit) && (condition2 > 0.08 * person_height)) {
            return true;
        } else {
            return false;
        }
    }

    //  翻越检测
    crossing_info gx_crossing_api::safe_production_crossing(
        const abi::vector<posture_info>& posture_info_list, const abi::vector<crossing_point>& quadrangle) {
        if (quadrangle.size() < 3)
            throw source_code_aware_runtime_error("Error: Invalid quadrangle: quadrangle.size < 3.");
        crossing_info ans;
        abi::vector<posture_info> posture_list_temp;
        for (int i = 0; i < posture_info_list.size(); i++) {
            if (posture_info_list[i].score >= 0.7)
                posture_list_temp.emplace_back(posture_info_list[i]);
        }
        std::vector<cv::Point2f> vec;
        for (auto& temp : quadrangle)
            vec.emplace_back(cv::Point2f{temp.x, temp.y});
        for (auto& ss : posture_list_temp) {
            if (check(ss)) {
                int key15 = cv::pointPolygonTest(vec, cv::Point2f{ss.key_points[15].x, ss.key_points[15].y}, false);
                int key16 = cv::pointPolygonTest(vec, cv::Point2f{ss.key_points[16].x, ss.key_points[16].y}, false);
                if (key15 < 0 || key16 < 0)
                    continue;
                ans.crossing_list.push_back(crossing_info::boxes{.score = ss.score,
                    .x1                                                 = ss.location.x1,
                    .y1                                                 = ss.location.y1,
                    .x2                                                 = ss.location.x2,
                    .y2                                                 = ss.location.y2});
            }
        }
        return ans;
    }
    crossing_info gx_crossing_api::safe_production_crossing(
        const gx_img_api& mat, const abi::vector<crossing_point>& quadrangle) {
        if (quadrangle.size() < 3)
            throw source_code_aware_runtime_error("Error: Invalid quadrangle: quadrangle.size < 3.");
        auto posture_info_list = impl_->api_temp->safe_production_posture(mat);
        return safe_production_crossing(posture_info_list, quadrangle);
    }

} // namespace glasssix