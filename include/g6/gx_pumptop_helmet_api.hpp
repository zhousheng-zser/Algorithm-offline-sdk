#pragma once
#include "gx_api.hpp"
#include "info_pumptop_helmet.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pumptop_helmet_api {
    public:
        gx_pumptop_helmet_api();
        gx_pumptop_helmet_api(const std::string& config_path);
        ~gx_pumptop_helmet_api();
        gx_pumptop_helmet_api(gx_pumptop_helmet_api&&) noexcept;
        gx_pumptop_helmet_api& operator=(gx_pumptop_helmet_api&&) noexcept;

        //  �ö���ȫñ���
        pumptop_helmet_info safe_production_pumptop_helmet(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
