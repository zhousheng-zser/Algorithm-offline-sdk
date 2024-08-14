#pragma once
#include "gx_api.hpp"
#include "info_policeuniform.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_policeuniform_api {
    public:
        gx_policeuniform_api();
        gx_policeuniform_api(const abi::string& config_path);
        ~gx_policeuniform_api();
        gx_policeuniform_api(gx_policeuniform_api&&) noexcept;
        gx_policeuniform_api& operator=(gx_policeuniform_api&&) noexcept;

        //  ¾¯·þ¼ì²â
        policeuniform_info safe_production_policeuniform(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
