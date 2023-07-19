#pragma once
#include "gx_api.hpp"
#include "info_leavepost.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_leavepost_api {
    public:
        gx_leavepost_api();
        gx_leavepost_api(const abi::string& config_path);
        ~gx_leavepost_api();
        gx_leavepost_api(gx_leavepost_api&&) noexcept;
        gx_leavepost_api& operator=(gx_leavepost_api&&) noexcept;

        //  安全生产 离岗检测
        leavepost_info safe_production_leavepost(gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
