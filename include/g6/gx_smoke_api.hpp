#pragma once
#include "gx_api.hpp"
#include "info_posture.hpp"
#include "info_smoke.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_smoke_api {
    public:
        gx_smoke_api();
        gx_smoke_api(const std::string& config_path);
        ~gx_smoke_api();
        gx_smoke_api(gx_smoke_api&&) noexcept;
        gx_smoke_api& operator=(gx_smoke_api&&) noexcept;

        //  ��ȫ���� ���̼��
        smoke_info safe_production_smoke(const gx_img_api& mat);

        //  ��ȫ���� ���̼��
        smoke_info safe_production_smoke(
            const gx_img_api& mat, const std::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
