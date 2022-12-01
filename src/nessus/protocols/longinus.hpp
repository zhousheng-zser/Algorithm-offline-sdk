#pragma once

#include "../common_protocols.hpp"
#include "face_info.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct longinus_new_param {
        GX_BEGIN_FIELDS(longinus_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct longinus_detect_param {
        GX_BEGIN_FIELDS(longinus_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, min_size);
        GX_FIELD(float, threshold);
        GX_FIELD(bool, do_attributing);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct longinus_detect_result {
        GX_BEGIN_FIELDS(longinus_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(std::vector<face_rect_with_face_info>, facerectwithfaceinfo_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct longinus_trace_param {
        GX_BEGIN_FIELDS(longinus_trace_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(face_rect, face);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct longinus_trace_result {
        GX_BEGIN_FIELDS(longinus_trace_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(bool, trace_success);
        GX_FIELD(std::vector<face_rect_with_face_info>, facerectwithfaceinfo);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct longinus : protocol_object {
        struct detect : parser_inout<longinus_detect_param, longinus_detect_result> {};
        struct trace : parser_inout<longinus_trace_param, longinus_trace_result> {};
    };
} // namespace glasssix::face
