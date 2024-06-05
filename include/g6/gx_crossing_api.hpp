#pragma once
#include "gx_api.hpp"
#include "info_crossing.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_crossing_api {
    public:
        gx_crossing_api();
        gx_crossing_api(const abi::string& config_path);
        ~gx_crossing_api();
        gx_crossing_api(gx_crossing_api&&) noexcept;
        gx_crossing_api& operator=(gx_crossing_api&&) noexcept;

        //  翻越检测
        crossing_info safe_production_crossing(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
