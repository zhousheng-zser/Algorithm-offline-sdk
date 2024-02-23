#pragma once
#include "gx_api.hpp"
#include "gx_pedestrian_api.hpp"
#include "info_pump_pumptop_person.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_pump_pumptop_person_api {
    public:
        gx_pump_pumptop_person_api();
        gx_pump_pumptop_person_api(const abi::string& config_path);
        ~gx_pump_pumptop_person_api();
        gx_pump_pumptop_person_api(gx_pump_pumptop_person_api&&) noexcept;
        gx_pump_pumptop_person_api& operator=(gx_pump_pumptop_person_api&&) noexcept;

        //  安全生产 泵顶无人检测
        pump_pumptop_person_info safe_production_pump_pumptop_person(const gx_img_api& mat);

        //  安全生产 泵顶无人检测
        pump_pumptop_person_info safe_production_pump_pumptop_person(
            const gx_img_api& mat, const abi::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
