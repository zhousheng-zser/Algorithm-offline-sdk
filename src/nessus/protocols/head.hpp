#pragma once

#include "../../../include/g6/info_head.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct head_new_param {
        GX_BEGIN_FIELDS(head_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct head_detect_param {
        GX_BEGIN_FIELDS(head_detect_param);
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

    struct head_detect_result {
        GX_BEGIN_FIELDS(head_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<head_info>, info_list);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct head : protocol_object {
        struct detect : parser_inout<head_detect_param, head_detect_result> {};
    };
} // namespace glasssix
