#pragma once
#include "gx_api.hpp"
#include "info_pedestrian.hpp"
#include "info_climb_tumble_pedestrian.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_climb_tumble_pedestrian_api {
    public:
        gx_climb_tumble_pedestrian_api();
        gx_climb_tumble_pedestrian_api(const std::string& config_path);
        ~gx_climb_tumble_pedestrian_api();
        gx_climb_tumble_pedestrian_api(gx_climb_tumble_pedestrian_api&&) noexcept;
        gx_climb_tumble_pedestrian_api& operator=(gx_climb_tumble_pedestrian_api&&) noexcept;

        //  ÅÊÅÀµøµ¹¼ì²â
        climb_tumble_pedestrian_info safe_production_climb_tumble_pedestrian(const gx_img_api& mat, int device_id);

        //  ÅÊÅÀµøµ¹¼ì²â
        climb_tumble_pedestrian_info safe_production_climb_tumble_pedestrian(
            const gx_img_api& mat, int device_id, const std::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
