#pragma once
#include "gx_api.hpp"
#include "info_posture.hpp"
#include "info_workcloth.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_workcloth_api {
    public:
        gx_workcloth_api();
        gx_workcloth_api(const std::string& config_path);
        ~gx_workcloth_api();
        gx_workcloth_api(gx_workcloth_api&&) noexcept;
        gx_workcloth_api& operator=(gx_workcloth_api&&) noexcept;

        //  安全生产 工服检测
        workcloth_info safe_production_workcloth(const gx_img_api& mat, int color_hsv_list_id);

        //  安全生产 工服衣检测
        workcloth_info safe_production_workcloth(
            const gx_img_api& mat, int color_hsv_list_id, const std::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
