#pragma once
#include "gx_api.hpp"
#include "info_fighting.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_fighting_api {
    public:
        gx_fighting_api();
        gx_fighting_api(const abi::string& config_path);
        ~gx_fighting_api();
        gx_fighting_api(gx_fighting_api&&) noexcept;
        gx_fighting_api& operator=(gx_fighting_api&&) noexcept;

        //  安全生产 打架检测
        fighting_info safe_production_fighting(const abi::vector<gx_img_api>& mat_list);
    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
