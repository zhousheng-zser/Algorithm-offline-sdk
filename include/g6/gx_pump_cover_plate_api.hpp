#pragma once
#include "gx_api.hpp"
#include "info_pump_cover_plate.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_cover_plate_api {
    public:
        gx_pump_cover_plate_api();
        gx_pump_cover_plate_api(const abi::string& config_path);
        ~gx_pump_cover_plate_api();
        gx_pump_cover_plate_api(gx_pump_cover_plate_api&&) noexcept;
        gx_pump_cover_plate_api& operator=(gx_pump_cover_plate_api&&) noexcept;

        //  ±√“µµÿ∏«Œ¥∏«∏«ºÏ≤‚
        pump_cover_plate_info safe_production_pump_cover_plate(
            const gx_img_api& mat, const abi::vector<pump_cover_plate_point>& quadrangle);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
