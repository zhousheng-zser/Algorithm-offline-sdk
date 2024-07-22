#pragma once
#include "gx_api.hpp"
#include "info_pump_hoisting.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_hoisting_api {
    public:
        gx_pump_hoisting_api();
        gx_pump_hoisting_api(const std::string& config_path);
        ~gx_pump_hoisting_api();
        gx_pump_hoisting_api(gx_pump_hoisting_api&&) noexcept;
        gx_pump_hoisting_api& operator=(gx_pump_hoisting_api&&) noexcept;

        //  泵业定制狭小区域检测
        pump_hoisting_info safe_production_pump_hoisting(const gx_img_api& mat, int device_id);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
