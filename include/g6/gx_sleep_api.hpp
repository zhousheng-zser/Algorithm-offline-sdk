#pragma once
#include "gx_api.hpp"
#include "info_sleep.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_sleep_api {
    public:
        gx_sleep_api();
        gx_sleep_api(const abi::string& config_path);
        ~gx_sleep_api();
        gx_sleep_api(gx_sleep_api&&) noexcept;
        gx_sleep_api& operator=(gx_sleep_api&&) noexcept;

        //  安全生产 睡岗检测
        sleep_info safe_production_sleep(gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
