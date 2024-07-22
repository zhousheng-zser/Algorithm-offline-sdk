#pragma once
#include "gx_api.hpp"
#include "info_pump_work_status.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_work_status_api {
    public:
        gx_pump_work_status_api();
        gx_pump_work_status_api(const std::string& config_path);
        ~gx_pump_work_status_api();
        gx_pump_work_status_api(gx_pump_work_status_api&&) noexcept;
        gx_pump_work_status_api& operator=(gx_pump_work_status_api&&) noexcept;

        //  ±ÃÒµ¹¤×÷×´Ì¬¼ì²â
        pump_work_status_info safe_production_pump_work_status(
            const gx_img_api& mat, int big_paint_room, const std::vector<pump_work_status_point>& polygon);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
