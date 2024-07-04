#pragma once

#include "../../../include/g6/info_climb.hpp"
#include "../../../include/g6/info_pedestrian.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct climb_tumble_pedestrian_new_param {
        GX_BEGIN_FIELDS(climb_tumble_pedestrian_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb_tumble_pedestrian_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, conf_thres);
            GX_FIELD(std::optional<float>, nms_thres);
            GX_FIELD(std::optional<float>, little_target_conf_thres);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(climb_tumble_pedestrian_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_FIELD(abi::vector<pedestrian_info::boxes>, person_list);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb_tumble_pedestrian_detect_result {
        GX_BEGIN_FIELDS(climb_tumble_pedestrian_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(climb_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb_tumble_pedestrian : protocol_object {
        struct detect : parser_inout<climb_tumble_pedestrian_detect_param, climb_tumble_pedestrian_detect_result> {};
    };
} // namespace glasssix
