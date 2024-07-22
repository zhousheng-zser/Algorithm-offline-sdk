#pragma once
#include "gx_api.hpp"
#include "info_pump_vesthelmet.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_vesthelmet_api {
    public:
        gx_pump_vesthelmet_api();
        gx_pump_vesthelmet_api(const std::string& config_path);
        ~gx_pump_vesthelmet_api();
        gx_pump_vesthelmet_api(gx_pump_vesthelmet_api&&) noexcept;
        gx_pump_vesthelmet_api& operator=(gx_pump_vesthelmet_api&&) noexcept;

        //  ��ҵ�쳵�����
        pump_vesthelmet_info safe_production_pump_vesthelmet(const gx_img_api& mat, float head_conf_thres);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
