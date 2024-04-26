#pragma once

#include "../../../include/g6/info_climb.hpp"
#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct climb_new_param {
        GX_BEGIN_FIELDS(climb_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, conf_thres);
            GX_FIELD(std::optional<float>, nms_thres);
            GX_FIELD(std::optional<float>, little_target_conf_thres);
            GX_FIELD(std::int32_t, x1);
            GX_FIELD(std::int32_t, y1);
            GX_FIELD(std::int32_t, x2);
            GX_FIELD(std::int32_t, y2);
            GX_FIELD(std::int32_t, x3);
            GX_FIELD(std::int32_t, y3);
            GX_FIELD(std::int32_t, x4);
            GX_FIELD(std::int32_t, y4);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(climb_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_FIELD(abi::vector<posture_info>, posture_info_list);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb_detect_result {
        GX_BEGIN_FIELDS(climb_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(climb_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct climb : protocol_object {
        struct detect : parser_inout<climb_detect_param, climb_detect_result> {};
    };
} // namespace glasssix
