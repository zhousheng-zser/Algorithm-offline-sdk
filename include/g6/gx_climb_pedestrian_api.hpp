#pragma once
#include "gx_api.hpp"
#include "info_climb.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_climb_pedestrian_api {
    public:
        gx_climb_pedestrian_api();
        gx_climb_pedestrian_api(const abi::string& config_path);
        ~gx_climb_pedestrian_api();
        gx_climb_pedestrian_api(gx_climb_pedestrian_api&&) noexcept;
        gx_climb_pedestrian_api& operator=(gx_climb_pedestrian_api&&) noexcept;

        //  安全生产 攀爬检测
        climb_info safe_production_climb_pedestrian(const gx_img_api& mat);

        //  安全生产 攀爬检测
        climb_info safe_production_climb_pedestrian(
            const gx_img_api& mat, const abi::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
