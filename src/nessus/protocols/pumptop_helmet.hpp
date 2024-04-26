#pragma once

#include "../../../include/g6/info_pumptop_helmet.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct pumptop_helmet_new_param {
        GX_BEGIN_FIELDS(pumptop_helmet_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pumptop_helmet_detect_param {
        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::optional<float>, head_conf_thres);
            GX_FIELD(std::optional<float>, pump_conf_thres);
            GX_FIELD(std::optional<float>, people_conf_thres);
            GX_FIELD(std::optional<float>, head_score_conf_thres);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(pumptop_helmet_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pumptop_helmet_detect_result {
        GX_BEGIN_FIELDS(pumptop_helmet_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(pumptop_helmet_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pumptop_helmet : protocol_object {
        struct detect : parser_inout<pumptop_helmet_detect_param, pumptop_helmet_detect_result> {};
    };
} // namespace glasssix
