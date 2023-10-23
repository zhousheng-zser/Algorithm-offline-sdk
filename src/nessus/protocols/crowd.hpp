#pragma once

#include "../../../include/g6/info_crowd.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct crowd_new_param {
        GX_BEGIN_FIELDS(crowd_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct crowd_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::int32_t, x1);
            GX_FIELD(std::int32_t, y1);
            GX_FIELD(std::int32_t, x2);
            GX_FIELD(std::int32_t, y2);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(crowd_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct crowd_detect_result {
        GX_BEGIN_FIELDS(crowd_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(crowd_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct crowd : protocol_object {
        struct detect : parser_inout<crowd_detect_param, crowd_detect_result> {};
    };
} // namespace glasssix
