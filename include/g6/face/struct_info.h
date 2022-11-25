#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>


namespace glasssix::face {
    //��������
    struct face_box_attributes {
        GX_BEGIN_FIELDS(face_box_attributes);
        GX_FIELD(int, glass_index); // �Ƿ���۾�
        GX_FIELD(int, mask_index); // �Ƿ������
        GX_FIELD(float, yaw); // ����ƫ����
        GX_FIELD(float, pitch); // ����������
        GX_FIELD(float, roll); // ����������
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //�����ؼ���
    struct face_box_landmark {
        GX_BEGIN_FIELDS(face_box_landmark);
        GX_FIELD(int, x); // x����
        GX_FIELD(int, y); // y����
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //����������Ϣ
    struct face_box {
        GX_BEGIN_FIELDS(face_box);
        GX_FIELD(int, x); // ����x����
        GX_FIELD(int, y); // ����y����
        GX_FIELD(int, height); // �����߶�
        GX_FIELD(int, width); // �������
        GX_FIELD(float, confidence); // �������Ŷ�
        GX_FIELD(face_box_attributes, attributes); // ��������
        GX_FIELD(std::vector<face_box_landmark>, landmark); // ����5��ؼ���

        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //����׷��
    struct track_face_box {
        GX_BEGIN_FIELDS(track_face_box);
        face_box _face_box; // ����������Ϣ
        bool trace_success; // ׷���Ƿ�ɹ�
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //�������������
    struct blur {
        GX_BEGIN_FIELDS(blur);
        face_box _face_box; // ����������Ϣ
        float clarity; // ���������̶�
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //��Ĭ��������
    struct spoofing {
        GX_BEGIN_FIELDS(spoofing);
        face_box _face_box; // ����������Ϣ
        GX_FIELD(std::vector<float>, prob); //   �����������
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // ����ֵ
    struct face_feature {
        GX_BEGIN_FIELDS(face_feature);
        face_box _face_box; //����������Ϣ
        GX_FIELD(std::vector<float>, feature); // ����ֵ����
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_info_data {
        GX_BEGIN_FIELDS(face_info_data);
        GX_FIELD(std::string, key); //��ֵ
        GX_FIELD(std::vector<float>, feature); // ����ֵ����
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // �׿��û���Ϣ
    struct face_info {
        GX_BEGIN_FIELDS(face_info);
        GX_FIELD(float, similarity); //���ƶ�
        GX_FIELD(face_info_data, data); // ��ֵ������ֵ
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //ͼƬ����
    struct img {
        int height; // ͼƬ�߶�
        int width; //  ͼƬ���
        char* date; //ͼƬ����
        size_t data_len; // ͼƬ�ֽڳ���
    };

    struct track_cache {
        std::unordered_map<int, face_box> track_history;
        int index = 0;
    };


    /**
     * @brief   ������������ö��
     */
    enum action_live_type {
        BDFACE_ACTION_LIVE_BLINK      = 0, // գգ��
        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // ������
        BDFACE_ACTION_LIVE_NOD        = 2, // ���ͷ
        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // ��ҡͷ
        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // ��ҡͷ
    };

    enum guid_type {
        longinus_guid      = 0, //����ʶ��
        romancia_guid      = 1, //��������
        damocles_guid      = 2, //������
        selene_guid        = 3, // 256ά������ȡ
        irisviel_guid      = 4, //������
        irisviel_mask_guid = 5 //����������
    };
} // namespace glasssix::face