#pragma once
#include "gx_api.hpp"
#include "info_pedestrian.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pedestrian_api {
    public:
        gx_pedestrian_api();
        gx_pedestrian_api(const abi::string& config_path);
        ~gx_pedestrian_api();
        gx_pedestrian_api(gx_pedestrian_api&&) noexcept;
        gx_pedestrian_api& operator=(gx_pedestrian_api&&) noexcept;

        //  安全生产 行人检测
        pedestrian_info safe_production_pedestrian(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
