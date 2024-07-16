#pragma once
#include "gx_api.hpp"
#include "info_climb_tumble_pedestrian.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_climb_tumble_pedestrian_api {
    public:
        gx_climb_tumble_pedestrian_api();
        gx_climb_tumble_pedestrian_api(const abi::string& config_path);
        ~gx_climb_tumble_pedestrian_api();
        gx_climb_tumble_pedestrian_api(gx_climb_tumble_pedestrian_api&&) noexcept;
        gx_climb_tumble_pedestrian_api& operator=(gx_climb_tumble_pedestrian_api&&) noexcept;

        //  安全生产 攀爬检测
        climb_tumble_info safe_production_climb_tumble_pedestrian(const gx_img_api& mat, int device_id);

        //  安全生产 攀爬检测
        climb_tumble_info safe_production_climb_tumble_pedestrian(
            const gx_img_api& mat, int device_id, const abi::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
