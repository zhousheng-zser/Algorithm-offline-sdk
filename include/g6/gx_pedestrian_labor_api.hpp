#pragma once
#include "gx_api.hpp"
#include "info_pedestrian_labor.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pedestrian_labor_api {
    public:
        gx_pedestrian_labor_api();
        gx_pedestrian_labor_api(const abi::string& config_path);
        ~gx_pedestrian_labor_api();
        gx_pedestrian_labor_api(gx_pedestrian_labor_api&&) noexcept;
        gx_pedestrian_labor_api& operator=(gx_pedestrian_labor_api&&) noexcept;

        //  安全生产 劳保检测
        pedestrian_labor_info safe_production_pedestrian_labor(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
