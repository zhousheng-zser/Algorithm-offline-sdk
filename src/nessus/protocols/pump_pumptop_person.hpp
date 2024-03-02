#pragma once

#include "../../../include/g6/info_pump_pumptop_person.hpp"
#include "../../../include/g6/info_pedestrian.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct pump_pumptop_person_new_param {
        GX_BEGIN_FIELDS(pump_pumptop_person_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_pumptop_person_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, person_area_ratio_thres);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(pump_pumptop_person_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<pedestrian_info::boxes>, person_list);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_pumptop_person_detect_result {
        GX_BEGIN_FIELDS(pump_pumptop_person_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(pump_pumptop_person_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_pumptop_person : protocol_object {
        struct detect : parser_inout<pump_pumptop_person_detect_param, pump_pumptop_person_detect_result> {};
    };
} // namespace glasssix
