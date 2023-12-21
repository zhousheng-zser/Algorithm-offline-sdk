#pragma once

#include "../../../include/g6/info_playphone.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct playphone_new_param {
        GX_BEGIN_FIELDS(playphone_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct playphone_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, head_conf_thres);
            GX_FIELD(std::optional<float>, head_nms_thres);
            GX_FIELD(std::optional<float>, phone_conf_thres);
            GX_FIELD(std::optional<float>, phone_nms_thres);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(playphone_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct playphone_detect_result {
        GX_BEGIN_FIELDS(playphone_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(playphone_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct playphone : protocol_object {
        struct detect : parser_inout<playphone_detect_param, playphone_detect_result> {};
    };
} // namespace glasssix
