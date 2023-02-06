#pragma once

#include "../../../include/g6/face/face_info.hpp"
#include "../common_protocols.hpp"
#include "../protocol_object.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct damocles_new_param {
        GX_BEGIN_FIELDS(damocles_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(bool, use_int8);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct damocles_spoofing_detect_param {
        GX_BEGIN_FIELDS(damocles_spoofing_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<face_info>, facerect_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct damocles_spoofing_detect_result {
        // struct spoofing_probability_info {
        //     GX_BEGIN_FIELDS(spoofing_probability_info);
        //     GX_FIELD(abi::vector<float>, prob);
        //     GX_END_FIELDS;

        //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        //};
        // using spoofing_probability_info = spoofing_probability;
        GX_BEGIN_FIELDS(damocles_spoofing_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<spoofing_probability>, spoofing_result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct damocles_presentation_attack_detect_param {
        GX_BEGIN_FIELDS(damocles_presentation_attack_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, action_cmd);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(face_info, facerect);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct damocles_presentation_attack_detect_result {
        GX_BEGIN_FIELDS(damocles_presentation_attack_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(bool, presentation_attack_result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct damocles : protocol_object {
        struct spoofing_detect : parser_inout<damocles_spoofing_detect_param, damocles_spoofing_detect_result> {};
        struct presentation_attack_detect
            : parser_inout<damocles_presentation_attack_detect_param, damocles_presentation_attack_detect_result> {};
    };

} // namespace glasssix::face
