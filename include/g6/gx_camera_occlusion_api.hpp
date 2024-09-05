#pragma once
#include "gx_api.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_camera_occlusion_api {
    public:
        gx_camera_occlusion_api();
        gx_camera_occlusion_api(const std::string& config_path);
        ~gx_camera_occlusion_api();
        gx_camera_occlusion_api(gx_camera_occlusion_api&&) noexcept;
        gx_camera_occlusion_api& operator=(gx_camera_occlusion_api&&) noexcept;

        //ÉãÏñÍ·ÕÚµ²¼ì²â
        bool safe_production_camera_occlusion(const gx_img_api& mat, int device_id);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
