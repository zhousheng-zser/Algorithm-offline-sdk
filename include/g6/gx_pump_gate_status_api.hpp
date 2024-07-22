#pragma once
#include "gx_api.hpp"
#include "info_pump_gate_status.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_gate_status_api {
    public:
        gx_pump_gate_status_api();
        gx_pump_gate_status_api(const std::string& config_path);
        ~gx_pump_gate_status_api();
        gx_pump_gate_status_api(gx_pump_gate_status_api&&) noexcept;
        gx_pump_gate_status_api& operator=(gx_pump_gate_status_api&&) noexcept;

        //  泵业大门关闭检测
        pump_gate_status_info safe_production_pump_gate_status(const gx_img_api& mat, int device_id);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
