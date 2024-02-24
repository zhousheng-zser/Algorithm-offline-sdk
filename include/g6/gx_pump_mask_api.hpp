#pragma once
#include "gx_api.hpp"
#include "info_pump_mask.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_mask_api {
    public:
        gx_pump_mask_api();
        gx_pump_mask_api(const abi::string& config_path);
        ~gx_pump_mask_api();
        gx_pump_mask_api(gx_pump_mask_api&&) noexcept;
        gx_pump_mask_api& operator=(gx_pump_mask_api&&) noexcept;

        //  安全生产 防护面罩检测
        pump_mask_info safe_production_pump_mask(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
