#pragma once
#include "gx_api.hpp"
#include "info_pedestrian_min.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pedestrian_min_api {
    public:
        gx_pedestrian_min_api();
        gx_pedestrian_min_api(const std::string& config_path);
        ~gx_pedestrian_min_api();
        gx_pedestrian_min_api(gx_pedestrian_min_api&&) noexcept;
        gx_pedestrian_min_api& operator=(gx_pedestrian_min_api&&) noexcept;

        //  安全生产 行人检测
        pedestrian_min_info safe_production_pedestrian_min(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
