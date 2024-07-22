#pragma once
#include "gx_api.hpp"
#include "info_pump_weld.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_weld_api {
    public:
        gx_pump_weld_api();
        gx_pump_weld_api(const std::string& config_path);
        ~gx_pump_weld_api();
        gx_pump_weld_api(gx_pump_weld_api&&) noexcept;
        gx_pump_weld_api& operator=(gx_pump_weld_api&&) noexcept;

        //  泵业定制化焊接检测
        pump_weld_info safe_production_pump_weld(const std::vector<gx_img_api>& mat_list, float wlight_conf_thres = 0.5,
            float candidate_box_width = 500, float candidate_box_height = 500);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
