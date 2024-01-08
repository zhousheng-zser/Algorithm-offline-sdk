#pragma once

#include "../../../include/g6/info_smoke.hpp"
#include "../../../include/g6/gx_posture_api.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct smoke_new_param {
        GX_BEGIN_FIELDS(smoke_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct smoke_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, conf_thres);
            GX_FIELD(std::optional<float>, nms_thres);
            GX_FIELD(std::optional<float>, little_target_conf_thres);
            GX_FIELD(std::optional<float>, smoke_conf_thres);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(smoke_detect_param);
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

    struct smoke_detect_result {
        GX_BEGIN_FIELDS(smoke_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(smoke_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct smoke : protocol_object {
        struct detect : parser_inout<smoke_detect_param, smoke_detect_result> {};
    };
} // namespace glasssix
