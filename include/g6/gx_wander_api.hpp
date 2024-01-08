#pragma once
#include "gx_api.hpp"
#include "gx_pedestrian_api.hpp"
#include "info_wander.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_wander_api {
    public:
        gx_wander_api();
        gx_wander_api(const abi::string& config_path);
        ~gx_wander_api();
        gx_wander_api(gx_wander_api&&) noexcept;
        gx_wander_api& operator=(gx_wander_api&&) noexcept;

        //  安全生产 徘徊检测
        wander_info safe_production_wander(
            const gx_img_api& mat, std::int64_t current_time, int device_id);

        //  安全生产 徘徊检测
        wander_info safe_production_wander(const gx_img_api& mat, std::int64_t current_time, int device_id,
            const abi::vector<pedestrian_info::boxes>& person_list);

        //  清除摄像头徘徊缓存
        bool wander_remove_library();

        //  清除摄像头中指定ID的信息
        bool wander_remove_id(int id);
    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
