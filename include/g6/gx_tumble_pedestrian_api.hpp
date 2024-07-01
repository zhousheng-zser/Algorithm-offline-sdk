#pragma once
#include "gx_api.hpp"
#include "info_tumble.hpp"

#include "gx_pedestrian_api.hpp"
namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_tumble_pedestrian_api {
    public:
        gx_tumble_pedestrian_api();
        gx_tumble_pedestrian_api(const abi::string& config_path);
        ~gx_tumble_pedestrian_api();
        gx_tumble_pedestrian_api(gx_tumble_pedestrian_api&&) noexcept;
        gx_tumble_pedestrian_api& operator=(gx_tumble_pedestrian_api&&) noexcept;

        
        //  安全生产 跌倒_行人检测
        tumble_info safe_production_tumble_pedestrian(
            const gx_img_api& mat);

        //  安全生产 跌倒_行人检测
        tumble_info safe_production_tumble_pedestrian(
            const gx_img_api& mat, const abi::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
