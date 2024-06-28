#pragma once
#include "gx_api.hpp"
#include "info_batterypilferers.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_batterypilferers_api {
    public:
        gx_batterypilferers_api();
        gx_batterypilferers_api(const std::string& config_path);
        ~gx_batterypilferers_api();
        gx_batterypilferers_api(gx_batterypilferers_api&&) noexcept;
        gx_batterypilferers_api& operator=(gx_batterypilferers_api&&) noexcept;

        //  安全生产 偷电瓶检测
        batterypilferers_info safe_production_batterypilferers(const std::vector<gx_img_api>& mat_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
