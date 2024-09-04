#pragma once
#include "gx_api.hpp"
#include "info_pump_glove.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_glove_api {
    public:
        gx_pump_glove_api();
        gx_pump_glove_api(const abi::string& config_path);
        ~gx_pump_glove_api();
        gx_pump_glove_api(gx_pump_glove_api&&) noexcept;
        gx_pump_glove_api& operator=(gx_pump_glove_api&&) noexcept;

        //  ÊÖÌ×¼ì²â
        pump_glove_info safe_production_pump_glove(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
