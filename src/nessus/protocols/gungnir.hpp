#pragma once

#include "../common_protocols.hpp"
#include "../protocol_object.hpp"

#include <cstdint>
#include <string>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct gungnir_new_param {
        GX_BEGIN_FIELDS(gungnir_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct gungnir_detect_param {
        GX_BEGIN_FIELDS(gungnir_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct gungnir_detect_result {
        struct face_info {
            GX_BEGIN_FIELDS(face_info);
            GX_FIELD(std::int32_t, x);
            GX_FIELD(std::int32_t, y);
            GX_FIELD(std::int32_t, height);
            GX_FIELD(std::int32_t, width);
            GX_FIELD(float, prob);
            GX_FIELD(std::int32_t, label);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(gungnir_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct gungnir : protocol_object {
        struct detect : parser_inout<gungnir_detect_param, gungnir_detect_result> {};
    };
} // namespace glasssix
