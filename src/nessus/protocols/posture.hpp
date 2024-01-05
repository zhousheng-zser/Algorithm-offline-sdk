#pragma once

#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct posture_new_param {
        GX_BEGIN_FIELDS(posture_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_FIELD(std::int32_t, model_type);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct posture_detect_param {

        GX_BEGIN_FIELDS(posture_detect_param);
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

    struct posture_detect_result {
        GX_BEGIN_FIELDS(posture_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<posture_info>, info_list);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct posture : protocol_object {
        struct detect : parser_inout<posture_detect_param, posture_detect_result> {};
    };
} // namespace glasssix
