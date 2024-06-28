#pragma once
#include "gx_api.hpp"
#include "info_tumble.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_tumble_api {
    public:
        gx_tumble_api();
        gx_tumble_api(const std::string& config_path);
        ~gx_tumble_api();
        gx_tumble_api(gx_tumble_api&&) noexcept;
        gx_tumble_api& operator=(gx_tumble_api&&) noexcept;

        //  安全生产 跌倒检测
        tumble_info safe_production_tumble(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
