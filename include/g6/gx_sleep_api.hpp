#pragma once
#include "gx_api.hpp"
#include "info_sleep.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_sleep_api {
    public:
        gx_sleep_api();
        gx_sleep_api(const std::string& config_path);
        ~gx_sleep_api();
        gx_sleep_api(gx_sleep_api&&) noexcept;
        gx_sleep_api& operator=(gx_sleep_api&&) noexcept;

        //  安全生产 睡岗检测
        sleep_info safe_production_sleep(const gx_img_api& mat);

        //  安全生产 睡岗检测
        sleep_info safe_production_sleep(const gx_img_api& mat, int device_id);

    private:
        class impl; 
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
