#pragma once
#include "gx_api.hpp"
#include "info_pump_mask.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_mask_api {
    public:
        gx_pump_mask_api();
        gx_pump_mask_api(const std::string& config_path);
        ~gx_pump_mask_api();
        gx_pump_mask_api(gx_pump_mask_api&&) noexcept;
        gx_pump_mask_api& operator=(gx_pump_mask_api&&) noexcept;

        //  ±√“µ∑¿ª§√Ê’÷ºÏ≤‚
        pump_mask_info safe_production_pump_mask(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
