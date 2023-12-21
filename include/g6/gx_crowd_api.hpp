#pragma once
#include "gx_api.hpp"
#include "info_crowd.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_crowd_api {
    public:
        gx_crowd_api();
        gx_crowd_api(const abi::string& config_path);
        ~gx_crowd_api();
        gx_crowd_api(gx_crowd_api&&) noexcept;
        gx_crowd_api& operator=(gx_crowd_api&&) noexcept;

        //  安全生产 聚众检测
        crowd_info safe_production_crowd(const gx_img_api& mat, int min_cluster_size);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
