#pragma once
#include "gx_api.hpp"
#include "info_head.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_head_api {
    public:
        gx_head_api();
        gx_head_api(const abi::string& config_path);
        ~gx_head_api();
        gx_head_api(gx_head_api&&) noexcept;
        gx_head_api& operator=(gx_head_api&&) noexcept;
        //  安全生产 人头检测
        abi::vector<head_info> safe_production_head(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
