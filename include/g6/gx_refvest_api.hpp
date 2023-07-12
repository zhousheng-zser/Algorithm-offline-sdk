#pragma once
#include "gx_api.hpp"
#include "info_refvest.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_refvest_api {
    public:
        gx_refvest_api();
        gx_refvest_api(const abi::string& config_path);
        ~gx_refvest_api();
        gx_refvest_api(gx_refvest_api&&) noexcept;
        gx_refvest_api& operator=(gx_refvest_api&&) noexcept;

        //  安全生产 反光衣检测
        refvest_info safe_production_refvest(gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
