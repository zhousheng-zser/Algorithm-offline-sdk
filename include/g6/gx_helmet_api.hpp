#pragma once
#include "gx_api.hpp"
#include "info_helmet.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_helmet_api {
    public:
        gx_helmet_api();
        gx_helmet_api(const abi::string& config_path);
        ~gx_helmet_api();
        gx_helmet_api(gx_helmet_api&&) noexcept;
        gx_helmet_api& operator=(gx_helmet_api&&) noexcept;
        //  安全生产 安全帽检测
        helmet_info safe_production_helmet(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
