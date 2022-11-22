#pragma once

#include <string>

//��������
struct attributes {
    int glass_index; // �Ƿ���۾�
    int mask_index; // �Ƿ������
    float yaw; // ����ƫ����
    float pitch; // ����������
    float roll; // ����������
};

//�����ؼ���
struct landmark {
    int x; // x����
    int y; // y����
};

//����������Ϣ
struct face_box {
    int x; // ����x����
    int y; // ����y����
    int height; // �����߶�
    int width; // �������
    float confidence; // �������Ŷ�
    attributes _attributes; // ��������
    landmark _landmark[5]; // ����5��ؼ���
};

//����׷��
struct trackface_box {
    face_box _face_box; // ����������Ϣ
    bool trace_success; // ׷���Ƿ�ɹ�
};

//�������������
struct blur {
    face_box _face_box; // ����������Ϣ
    float clarity; // ���������̶�
};

//��Ĭ��������
struct spoofing {
    face_box _face_box; // ����������Ϣ
    float prob[3]; //   �����������
};

// ����ֵ
struct feature {
    face_box _face_box; // ����ֵ����
    float feature[256]; //����������Ϣ
};

// �׿��û���Ϣ
struct face_info {
    std::string key; // ��ֵ
    double similarity; //���ƶ�
};

//ͼƬ����
struct img {
    int height; // ͼƬ�߶�
    int width; //  ͼƬ���
    char* date; //ͼƬ����
    size_t data_len; // ͼƬ�ֽڳ���
};


/**
 * @brief   ������������ö��
 */
enum action_live_type {
    BDFACE_ACTION_LIVE_BLINK      = 0, // գգ��
    BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // ������
    BDFACE_ACTION_LIVE_NOD        = 2, // ���ͷ
    BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // ��ҡͷ
    BDFACE_ACTION_LIVE_RIGHT_HEAD = 4  // ��ҡͷ
};

enum guid_type {
    longinus_guid = 0, //����ʶ��
    romancia_guid = 1, //��������
    damocles_guid = 2, //������
    selene_guid   = 3, // 256ά������ȡ
    irisviel_guid = 4, //������
    irisviel_mask_guid = 5 //����������
};