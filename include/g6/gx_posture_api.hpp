#pragma once
#include "gx_api.hpp"
#include "info_posture.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_posture_api {
    public:
        gx_posture_api();
        gx_posture_api(const abi::string& config_path);
        ~gx_posture_api();
        gx_posture_api(gx_posture_api&&) noexcept;
        gx_posture_api& operator=(gx_posture_api&&) noexcept;

        //  安全生产 姿态检测
        abi::vector<posture_info> safe_production_posture(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
