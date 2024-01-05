#pragma once
#include "gx_api.hpp"
#include "gx_posture_api.hpp"
#include "info_climb.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_climb_api {
    public:
        gx_climb_api();
        gx_climb_api(const abi::string& config_path);
        ~gx_climb_api();
        gx_climb_api(gx_climb_api&&) noexcept;
        gx_climb_api& operator=(gx_climb_api&&) noexcept;

        //  安全生产 攀爬检测
        climb_info safe_production_climb(const gx_img_api& mat, const abi::vector<climb_point>& quadrangle);

        //  安全生产 攀爬检测
        climb_info safe_production_climb(const gx_img_api& mat, const abi::vector<climb_point>& quadrangle,
            const abi::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
