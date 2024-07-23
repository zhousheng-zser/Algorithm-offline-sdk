#pragma once
#include "gx_api.hpp"
#include "info_posture.hpp"
#include "info_head.hpp"
#include "info_onphone.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_onphone_api {
    public:
        gx_onphone_api();
        gx_onphone_api(const std::string& config_path);
        ~gx_onphone_api();
        gx_onphone_api(gx_onphone_api&&) noexcept;
        gx_onphone_api& operator=(gx_onphone_api&&) noexcept;

        //  安全生产 打电话检测 依赖人头
        onphone_info safe_production_onphone(const gx_img_api& mat, const std::vector<head_info>& head_info_list);

        //  安全生产 打电话检测 依赖姿态
        onphone_info safe_production_onphone(
            const gx_img_api& mat, const std::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
