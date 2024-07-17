#pragma once

#include "../../../include/g6/info_subway_anomaly.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct subway_anomaly_new_param {
        GX_BEGIN_FIELDS(subway_anomaly_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct subway_anomaly_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::int32_t, type);
            GX_FIELD(float, conf_thres);
            GX_FIELD(float, normal_closedoor_thresh);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(subway_anomaly_detect_param);
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

    struct subway_anomaly_detect_result {
        GX_BEGIN_FIELDS(subway_anomaly_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(subway_anomaly_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct subway_anomaly : protocol_object {
        struct detect : parser_inout<subway_anomaly_detect_param, subway_anomaly_detect_result> {};
    };
} // namespace glasssix
