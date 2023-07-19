#pragma once
#include "gx_api.hpp"
#include "info_onphone.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_onphone_api {
    public:
        gx_onphone_api();
        gx_onphone_api(const abi::string& config_path);
        ~gx_onphone_api();
        gx_onphone_api(gx_onphone_api&&) noexcept;
        gx_onphone_api& operator=(gx_onphone_api&&) noexcept;

        //  安全生产 打电话检测
        onphone_info safe_production_onphone(gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
