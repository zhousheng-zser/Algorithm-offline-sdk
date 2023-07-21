#pragma once
#include "gx_api.hpp"
#include "info_playphone.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_playphone_api {
    public:
        gx_playphone_api();
        gx_playphone_api(const abi::string& config_path);
        ~gx_playphone_api();
        gx_playphone_api(gx_playphone_api&&) noexcept;
        gx_playphone_api& operator=(gx_playphone_api&&) noexcept;

        //  安全生产 玩手机检测
        playphone_info safe_production_playphone(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
