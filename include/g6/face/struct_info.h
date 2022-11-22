#pragma once

#include <string>

//人脸属性
struct attributes {
    int glass_index; // 是否戴眼镜
    int mask_index; // 是否戴口罩
    float yaw; // 人脸偏航角
    float pitch; // 人脸俯仰角
    float roll; // 人脸翻滚角
};

//人脸关键点
struct landmark {
    int x; // x坐标
    int y; // y坐标
};

//人脸基础信息
struct face_box {
    int x; // 人脸x坐标
    int y; // 人脸y坐标
    int height; // 人脸高度
    int width; // 人脸宽度
    float confidence; // 人脸置信度
    attributes _attributes; // 人脸属性
    landmark _landmark[5]; // 人脸5点关键点
};

//人脸追踪
struct trackface_box {
    face_box _face_box; // 人脸基础信息
    bool trace_success; // 追踪是否成功
};

//人脸质量检测结果
struct blur {
    face_box _face_box; // 人脸基础信息
    float clarity; // 人脸质量程度
};

//静默活体检测结果
struct spoofing {
    face_box _face_box; // 人脸基础信息
    float prob[3]; //   活体检测分类结果
};

// 特征值
struct feature {
    face_box _face_box; // 特征值数组
    float feature[256]; //人脸基础信息
};

// 底库用户信息
struct face_info {
    std::string key; // 键值
    double similarity; //相似度
};

//图片参数
struct img {
    int height; // 图片高度
    int width; //  图片宽度
    char* date; //图片数据
    size_t data_len; // 图片字节长度
};


/**
 * @brief   动作活体类型枚举
 */
enum action_live_type {
    BDFACE_ACTION_LIVE_BLINK      = 0, // 眨眨眼
    BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // 张张嘴
    BDFACE_ACTION_LIVE_NOD        = 2, // 点点头
    BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // 左摇头
    BDFACE_ACTION_LIVE_RIGHT_HEAD = 4  // 右摇头
};

enum guid_type {
    longinus_guid = 0, //人脸识别
    romancia_guid = 1, //人脸对齐
    damocles_guid = 2, //活体检测
    selene_guid   = 3, // 256维特征提取
    irisviel_guid = 4, //人脸库
    irisviel_mask_guid = 5 //口罩人脸库
};