#pragma once
#include "gx_api.hpp"
#include "info_pump_light.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_light_api {
    public:
        gx_pump_light_api();
        gx_pump_light_api(const std::string& config_path);
        ~gx_pump_light_api();
        gx_pump_light_api(gx_pump_light_api&&) noexcept;
        gx_pump_light_api& operator=(gx_pump_light_api&&) noexcept;

        //  ±√“µµ∆π‚ºÏ≤‚
        pump_light_info safe_production_pump_light(
            const gx_img_api& mat, const std::vector<pump_light_point>& quadrangle);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
