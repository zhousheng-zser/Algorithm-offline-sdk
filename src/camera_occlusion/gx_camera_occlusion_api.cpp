#include "gx_camera_occlusion_api.hpp"

#include "../sdk_share.hpp"
#include "config.hpp"

#include <unordered_map>

#include <opencv2/opencv.hpp>

namespace glasssix {
    config* _config = nullptr;
    struct camera_status {
        int cnt = 0;
        std::vector<double> laplacian_variances;
        std::int64_t last_time;
        int normal_frame_count = 0; // 连续正常帧数
        int obscured_count     = 0; // 连续报警帧数
    };
    gx_camera_occlusion_api::gx_camera_occlusion_api() : impl_{std::make_unique<impl>()} {}
    gx_camera_occlusion_api::gx_camera_occlusion_api(const abi::string& config_path)
        : impl_{std::make_unique<impl>(config_path)} {}
    gx_camera_occlusion_api::~gx_camera_occlusion_api() {}
    gx_camera_occlusion_api::gx_camera_occlusion_api(gx_camera_occlusion_api&&) noexcept            = default;
    gx_camera_occlusion_api& gx_camera_occlusion_api::operator=(gx_camera_occlusion_api&&) noexcept = default;
    class gx_camera_occlusion_api::impl {
    public:
        void init() {}
        impl() {
            if (_config == nullptr) {
                _config = new config();
            }
            init();
        }
        impl(const abi::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
            }
            init();
        }
        ~impl() {}
        double computeLaplacianVariance(const cv::Mat& frame) {
            // 将图像转换为灰度图像
            cv::Mat gray;
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

            // 计算Laplacian
            cv::Mat laplacian;
            cv::Laplacian(gray, laplacian, CV_64F);

            // 计算方差
            cv::Scalar mean, stddev;
            cv::meanStdDev(laplacian, mean, stddev);
            double variance = stddev[0] * stddev[0];

            return variance;
        }

        void update_normal_range(std::vector<double>& laplacian_variances, double sigma, double& l, double& r) {
            if (laplacian_variances.size() == 0)
                return;
            // 计算均值
            double sum  = std::accumulate(laplacian_variances.begin(), laplacian_variances.end(), 0.0);
            double mean = sum / laplacian_variances.size();
            // 计算标准差
            double accum = 0.0;
            for (double val : laplacian_variances) {
                accum += (val - mean) * (val - mean);
            }
            double std_dev = std::sqrt(accum / laplacian_variances.size());
            l              = mean - sigma * std_dev;
            r              = mean + sigma * std_dev;
        }
        bool gx_camera_occlusion_api::safe_production_camera_occlusion(
            const gx_img_api& mat, std::int64_t current_time, int device_id, double sigma) {
            try {
                bool ans = false;
                camera_status status_now;
                cv::Mat frame(mat.get_rows(), mat.get_cols(), CV_8UC3, const_cast<uchar*>(mat.get_data()));
                { // 获取值
                    std::lock_guard<std::mutex> lock(impl_->list_camera_mutex);
                    status_now = impl_->list_camera_map[device_id];
                }
                if (status_now.cnt == 0) {
                    status_now.laplacian_variances.clear();
                    status_now.last_time          = current_time;
                    status_now.obscured_count     = 0;
                    status_now.normal_frame_count = 0;
                }
                status_now.cnt++;
                double normal_range_l = _config->_camera_occlusion_config.initial_normal_range_l;
                double normal_range_r = _config->_camera_occlusion_config.initial_normal_range_r;
                double variance       = computeLaplacianVariance(frame);
                if (status_now.cnt <= _config->_camera_occlusion_config.num_frames * 5
                    && status_now.cnt % (_config->_camera_occlusion_config.frames_interval * 5) == 0) {
                    status_now.laplacian_variances.emplace_back(variance);
                } else if (status_now.cnt == _config->_camera_occlusion_config.num_frames * 5 + 1) {
                    update_normal_range(status_now.laplacian_variances, sigma, normal_range_l, normal_range_r);
                    status_now.laplacian_variances.clear();
                }
                if (variance > normal_range_l) {
                    status_now.normal_frame_count++;
                    if (status_now.normal_frame_count >= _config->_camera_occlusion_config.restart_normal_count) {
                        status_now.normal_frame_count = 0;
                        status_now.obscured_count     = 0;
                    }
                } else {
                    status_now.obscured_count++;
                    status_now.normal_frame_count = 0;
                    if (status_now.obscured_count >= _config->_camera_occlusion_config.repeated_outside_threshold)
                        ans = true;
                }

                if (current_time - status_now.last_time > _config->_camera_occlusion_config.update_interval) // 一小时
                    status_now.cnt = 0;

                { // 更新状态
                    std::lock_guard<std::mutex> lock(impl_->list_camera_mutex);
                    impl_->list_camera_map[device_id] = status_now;
                }
                return ans;
            } catch (const std::exception& ex) {
                bool flag = write_dump_img(mat, "_camera_occlusion_dump.jpg");
                throw source_code_aware_runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }
        bool gx_camera_occlusion_api::camera_occlusion_remove_id(int id) {
            std::lock_guard<std::mutex> lock(impl_->list_camera_mutex);
            impl_->list_camera_map.erase(id);
            return true;
        }

        static std::mutex list_camera_mutex;
        static std::unordered_map<int, camera_status> list_camera_map;
    };
    bool gx_camera_occlusion_api::safe_production_camera_occlusion(
        const gx_img_api& mat, std::int64_t current_time, int device_id, double sigma) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_camera_occlusion(mat, current_time, device_id sigma);
    }
    bool gx_camera_occlusion_api::camera_occlusion_remove_id(int id) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->camera_occlusion_remove_id(id);
    }

    std::mutex gx_camera_occlusion_api::impl::list_camera_mutex;
    std::unordered_map<int, camera_status> gx_camera_occlusion_api::impl::list_camera_map;

} // namespace glasssix