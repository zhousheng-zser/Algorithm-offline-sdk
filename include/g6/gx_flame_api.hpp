#pragma once
#include "gx_api.hpp"
#include "info_flame.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_flame_api {
    public:
        gx_flame_api();
        gx_flame_api(const abi::string& config_path);
        ~gx_flame_api();
        gx_flame_api(gx_flame_api&&) noexcept;
        gx_flame_api& operator=(gx_flame_api&&) noexcept;

        //  安全生产 烟雾火焰检测
        flame_info safe_production_flame(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
