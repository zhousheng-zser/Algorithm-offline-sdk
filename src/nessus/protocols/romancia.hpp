#pragma once

#include "../../../include/g6/info.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct romancia_new_param {
        GX_BEGIN_FIELDS(romancia_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct romancia_align_face_param {
        GX_BEGIN_FIELDS(romancia_align_face_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct romancia_align_face_result {
        GX_BEGIN_FIELDS(romancia_align_face_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<std::string>, aligned_images);
        GX_FIELD(std::int32_t, format);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct romancia_blur_detect_param {
        GX_BEGIN_FIELDS(romancia_blur_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<face_info>, facerect_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct romancia_blur_detect_result {
        GX_BEGIN_FIELDS(romancia_blur_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<float>, clarity);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct romancia : protocol_object {
        struct alignFace : parser_inout<romancia_align_face_param, romancia_align_face_result> {};
        struct blur_detect : parser_inout<romancia_blur_detect_param, romancia_blur_detect_result> {};
    };
} // namespace glasssix
