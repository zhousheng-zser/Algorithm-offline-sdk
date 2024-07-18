#pragma once
#include "gx_api.hpp"
#include "info_subway_anomaly.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_subway_anomaly_api {
    public:
        gx_subway_anomaly_api();
        gx_subway_anomaly_api(const abi::string& config_path);
        ~gx_subway_anomaly_api();
        gx_subway_anomaly_api(gx_subway_anomaly_api&&) noexcept;
        gx_subway_anomaly_api& operator=(gx_subway_anomaly_api&&) noexcept;

        //  µÿÃ˙“Ï≥£ºÏ≤‚
        subway_anomaly_info safe_production_subway_anomaly(const gx_img_api& mat, const subway_anomaly_roi& roi,int type);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
