#pragma once
#include "gx_api.hpp"
#include "info_pump_weld.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_weld_api {
    public:
        gx_pump_weld_api();
        gx_pump_weld_api(const abi::string& config_path);
        ~gx_pump_weld_api();
        gx_pump_weld_api(gx_pump_weld_api&&) noexcept;
        gx_pump_weld_api& operator=(gx_pump_weld_api&&) noexcept;

        //  安全生产 泵业定制化焊接检测
        pump_weld_info safe_production_pump_weld(
            const gx_img_api& mat,float wlight_conf_thres = 0.5, float candidate_box_width=500, float candidate_box_height=500);
        //  安全生产 清空数据
        void safe_production_clear();
    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
