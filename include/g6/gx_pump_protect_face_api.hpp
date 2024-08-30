#pragma once
#include "gx_api.hpp"
#include "info_pump_protect_face.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_protect_face_api {
    public:
        gx_pump_protect_face_api();
        gx_pump_protect_face_api(const abi::string& config_path);
        ~gx_pump_protect_face_api();
        gx_pump_protect_face_api(gx_pump_protect_face_api&&) noexcept;
        gx_pump_protect_face_api& operator=(gx_pump_protect_face_api&&) noexcept;

        //  安全生产 保护人脸检测
        pump_protect_face_info safe_production_pump_protect_face(const gx_img_api& mat);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
