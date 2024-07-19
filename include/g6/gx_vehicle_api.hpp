#pragma once
#include "gx_api.hpp"
#include "info_vehicle.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_vehicle_api {
    public:
        gx_vehicle_api();
        gx_vehicle_api(const std::string& config_path);
        ~gx_vehicle_api();
        gx_vehicle_api(gx_vehicle_api&&) noexcept;
        gx_vehicle_api& operator=(gx_vehicle_api&&) noexcept;

        //  安全生产 车辆检测
        vehicle_info safe_production_vehicle(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
