#pragma once

#include "../../../include/g6/info_pump_gate_status.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct pump_gate_status_new_param {
        GX_BEGIN_FIELDS(pump_gate_status_new_param);
        GX_FIELD(std::int32_t, device);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_gate_status_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, door_close_ratio);
            GX_FIELD(std::optional<float>, door_open_ratio);
            GX_FIELD(std::optional<float>, floor_ratio);
            GX_FIELD(std::optional<float>, device_id);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct confidence_roi {

            struct boxes {
                GX_BEGIN_FIELDS(boxes);
                GX_FIELD(int, x1);
                GX_FIELD(int, y1);
                GX_FIELD(int, x2);
                GX_FIELD(int, y2);
                GX_END_FIELDS;

                GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
            };

            GX_BEGIN_FIELDS(confidence_roi);
            GX_FIELD(boxes, door);
            GX_FIELD(boxes, floor);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(pump_gate_status_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_FIELD(std::int32_t, yellow_hsv_lower);
        GX_FIELD(std::int32_t, yellow_hsv_upper);
        GX_FIELD(std::int32_t, gray_hsv_lower);
        GX_FIELD(std::int32_t, gray_hsv_upper);
        GX_FIELD(confidence_roi, rois);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_gate_status_detect_result {
        GX_BEGIN_FIELDS(pump_gate_status_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::string, security_status);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_gate_status : protocol_object {
        struct detect : parser_inout<pump_gate_status_detect_param, pump_gate_status_detect_result> {};
    };
} // namespace glasssix
