#pragma once
#include "gx_api.hpp"
#include "info_smog.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_smog_api {
    public:
        gx_smog_api();
        gx_smog_api(const abi::string& config_path);
        ~gx_smog_api();
        gx_smog_api(gx_smog_api&&) noexcept;
        gx_smog_api& operator=(gx_smog_api&&) noexcept;

        //  安全生产 烟雾检测
        smog_info safe_production_smog(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
