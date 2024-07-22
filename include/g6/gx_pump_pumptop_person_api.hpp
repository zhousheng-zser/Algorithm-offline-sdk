#pragma once
#include "gx_api.hpp"
#include "info_pedestrian.hpp"
#include "info_pump_pumptop_person.hpp"

namespace glasssix {

    class GX_API(GXAPI) gx_pump_pumptop_person_api {
    public:
        gx_pump_pumptop_person_api();
        gx_pump_pumptop_person_api(const std::string& config_path);
        ~gx_pump_pumptop_person_api();
        gx_pump_pumptop_person_api(gx_pump_pumptop_person_api&&) noexcept;
        gx_pump_pumptop_person_api& operator=(gx_pump_pumptop_person_api&&) noexcept;

        //  ±√“µ ±√∂•Œﬁ»ÀºÏ≤‚
        pump_pumptop_person_info safe_production_pump_pumptop_person(const gx_img_api& mat);

        //  ±√“µ ±√∂•Œﬁ»ÀºÏ≤‚
        pump_pumptop_person_info safe_production_pump_pumptop_person(
            const gx_img_api& mat, const std::vector<pedestrian_info::boxes>& person_list);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
