#pragma once

#include <cstdint>
#include <vector>
#include <optional>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct attributes_info {
        GX_BEGIN_FIELDS(attributes_info);
        GX_FIELD(std::int32_t, glass_index);
        GX_FIELD(std::int32_t, mask_index);
        GX_FIELD(float, yaw);
        GX_FIELD(float, pitch);
        GX_FIELD(float, roll);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_info {
        struct point {
            GX_BEGIN_FIELDS(point);
            GX_FIELD(std::int32_t, x);
            GX_FIELD(std::int32_t, y);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(face_info);
        GX_FIELD(std::int32_t, x);
        GX_FIELD(std::int32_t, y);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(float, confidence);
        GX_FIELD(std::optional<attributes_info>, attributes);
        GX_FIELD(abi::vector<point>, landmark);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_rect {
        GX_BEGIN_FIELDS(face_rect);
        GX_FIELD(std::int32_t, x);
        GX_FIELD(std::int32_t, y);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_trace_info {
        GX_BEGIN_FIELDS(face_trace_info);
        GX_FIELD(bool, trace_success);
        GX_FIELD(std::optional<face_info>, facerectwithfaceinfo);
        GX_END_FIELDS;
        abi::string trace_id;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    //�������������
    struct faces_blur {
        GX_BEGIN_FIELDS(faces_blur);
        GX_FIELD(abi::vector<face_info> ,facerectwithfaceinfo_list); // ����������Ϣ
        GX_FIELD(abi::vector<float> ,clarity); // ���������̶�
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct spoofing_probability {
        GX_BEGIN_FIELDS(spoofing_probability);
        GX_FIELD(abi::vector<float>, prob);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct faces_spoofing {
        GX_BEGIN_FIELDS(faces_spoofing);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list); // ����������Ϣ
        GX_FIELD(abi::vector<spoofing_probability> ,spoofing_result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct feature_info {
        GX_BEGIN_FIELDS(feature_info);
        GX_FIELD(abi::vector<float>, feature);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // ����ֵ
    struct faces_feature {
        GX_BEGIN_FIELDS(faces_feature);
        GX_FIELD(abi::vector<face_info> ,facerectwithfaceinfo_list); // ����������Ϣ
        GX_FIELD(abi::vector<feature_info>, features); // ����ֵ����
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct faces_search_data {
        GX_BEGIN_FIELDS(faces_search_data);
        GX_FIELD(abi::vector<float>, feature);
        GX_FIELD(abi::string, key);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct faces_search_info {
        GX_BEGIN_FIELDS(faces_search_info);
        struct database_result {
            GX_BEGIN_FIELDS(database_result);
            GX_FIELD(faces_search_data, data);
            GX_FIELD(float, similarity);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_FIELD(abi::vector<database_result>, result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    //������������ö��
    enum action_live_type {
        BDFACE_ACTION_LIVE_BLINK      = 0, // գգ��
        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // ������
        BDFACE_ACTION_LIVE_NOD        = 2, // ���ͷ
        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // ��ҡͷ
        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // ��ҡͷ
    };

} // namespace glasssix::face
