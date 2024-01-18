#pragma once
#include "gx_api.hpp"
#include "gx_posture_api.hpp"
#include "gx_head_api.hpp"
#include "info_onphone.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_onphone_api {
    public:
        gx_onphone_api();
        gx_onphone_api(const abi::string& config_path);
        ~gx_onphone_api();
        gx_onphone_api(gx_onphone_api&&) noexcept;
        gx_onphone_api& operator=(gx_onphone_api&&) noexcept;

        //  ��ȫ���� ��绰��� ������ͷ
        onphone_info safe_production_onphone(const gx_img_api& mat, const abi::vector<head_info>& head_info_list);

        //  ��ȫ���� ��绰��� ������̬
        onphone_info safe_production_onphone(const gx_img_api& mat, const abi::vector<posture_info>& posture_info_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
