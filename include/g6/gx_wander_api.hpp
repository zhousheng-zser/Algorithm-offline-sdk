#pragma once
#include "gx_api.hpp"
#include "info_wander.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_wander_api {
    public:
        gx_wander_api();
        gx_wander_api(const abi::string& config_path);
        ~gx_wander_api();
        gx_wander_api(gx_wander_api&&) noexcept;
        gx_wander_api& operator=(gx_wander_api&&) noexcept;

        //  °²È«Éú²ú ÅÇ»²¼ì²â
        wander_info safe_production_wander(const gx_img_api& mat, std::int64_t current_time, int device_id);
        
        //  Çå³ýÉãÏñÍ·ÅÇ»²»º´æ
        bool wander_remove_library();

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
