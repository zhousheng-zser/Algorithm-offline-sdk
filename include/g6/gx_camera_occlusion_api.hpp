#pragma once
#include "gx_api.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_camera_occlusion_api {
    public:
        gx_camera_occlusion_api();
        gx_camera_occlusion_api(const abi::string& config_path);
        ~gx_camera_occlusion_api();
        gx_camera_occlusion_api(gx_camera_occlusion_api&&) noexcept;
        gx_camera_occlusion_api& operator=(gx_camera_occlusion_api&&) noexcept;

        //  摄像头遮挡检测
        bool safe_production_camera_occlusion(
            const gx_img_api& mat, std::int64_t current_time, int device_id, double sigma = 2);
        
        // 清空摄像头信息
        bool camera_occlusion_remove_id(int id);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
