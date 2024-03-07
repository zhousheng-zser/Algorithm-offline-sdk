#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct face_attributes_new_param {
        GX_BEGIN_FIELDS(face_attributes_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_attributes_detect_param {
        GX_BEGIN_FIELDS(face_attributes_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<face_info>, facerect_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_attributes_detect_result {
        GX_BEGIN_FIELDS(face_attributes_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<attributes>, face_attributes);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_attributes : protocol_object {
        struct detect : parser_inout<face_attributes_detect_param, face_attributes_detect_result> {};
    };
} // namespace glasssix
