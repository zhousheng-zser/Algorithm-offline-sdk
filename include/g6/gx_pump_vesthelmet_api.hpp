#pragma once
#include "gx_api.hpp"
#include "info_pump_vesthelmet.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_vesthelmet_api {
    public:
        gx_pump_vesthelmet_api();
        gx_pump_vesthelmet_api(const abi::string& config_path);
        ~gx_pump_vesthelmet_api();
        gx_pump_vesthelmet_api(gx_pump_vesthelmet_api&&) noexcept;
        gx_pump_vesthelmet_api& operator=(gx_pump_vesthelmet_api&&) noexcept;

        //  安全生产 天车工检测
        pump_vesthelmet_info safe_production_pump_vesthelmet(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
