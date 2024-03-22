#pragma once
#include "gx_api.hpp"
#include "gx_posture_api.hpp"
#include "info_crossing.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_crossing_api {
    public:
        gx_crossing_api();
        gx_crossing_api(const abi::string& config_path);
        ~gx_crossing_api();
        gx_crossing_api(gx_crossing_api&&) noexcept;
        gx_crossing_api& operator=(gx_crossing_api&&) noexcept;

        //  ·­Ô½¼ì²â
        crossing_info safe_production_crossing(const gx_img_api& mat);

        //  ·­Ô½¼ì²â
        crossing_info safe_production_crossing(const abi::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
