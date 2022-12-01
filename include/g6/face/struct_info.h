#pragma once

#include <unordered_map>
#include <vector>

#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>

#include <proxy/proxy.h>

namespace glasssix::face {
    //人脸属性
    struct face_box_attributes {
        GX_BEGIN_FIELDS(face_box_attributes);
        GX_FIELD(int, glass_index); // 是否戴眼镜
        GX_FIELD(int, mask_index); // 是否戴口罩
        GX_FIELD(float, yaw); // 人脸偏航角
        GX_FIELD(float, pitch); // 人脸俯仰角
        GX_FIELD(float, roll); // 人脸翻滚角
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸关键点
    struct face_box_landmark {
        GX_BEGIN_FIELDS(face_box_landmark);
        GX_FIELD(int, x); // x坐标
        GX_FIELD(int, y); // y坐标
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸基础信息
    struct face_box {
        GX_BEGIN_FIELDS(face_box);
        GX_FIELD(int, x); // 人脸x坐标
        GX_FIELD(int, y); // 人脸y坐标
        GX_FIELD(int, height); // 人脸高度
        GX_FIELD(int, width); // 人脸宽度
        GX_FIELD(float, confidence); // 人脸置信度
        GX_FIELD(face_box_attributes, attributes); // 人脸属性
        GX_FIELD(std::vector<face_box_landmark>, landmark); // 人脸5点关键点

        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸追踪
    struct track_face_box {
        GX_BEGIN_FIELDS(track_face_box);
        face_box _face_box; // 人脸基础信息
        bool trace_success; // 追踪是否成功
        abi::string trace_id; //人脸id
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸质量检测结果
    struct blur {
        GX_BEGIN_FIELDS(blur);
        face_box _face_box; // 人脸基础信息
        float clarity; // 人脸质量程度
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //静默活体检测结果
    struct spoofing {
        GX_BEGIN_FIELDS(spoofing);
        face_box _face_box; // 人脸基础信息
        GX_FIELD(std::vector<float>, prob); //   活体检测分类结果
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 特征值
    struct face_feature {
        GX_BEGIN_FIELDS(face_feature);
        face_box _face_box; //人脸基础信息
        GX_FIELD(std::vector<float>, feature); // 特征值数组
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 底库用户信息
    struct face_info_data {
        GX_BEGIN_FIELDS(face_info_data);
        GX_FIELD(abi::string, key); //键值
        GX_FIELD(std::vector<float>, feature); // 特征值数组
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 搜索底库用户结果
    struct face_info {
        GX_BEGIN_FIELDS(face_info);
        GX_FIELD(float, similarity); //相似度
        GX_FIELD(face_info_data, data); // 键值和特征值
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //图片参数
    struct img {
        int height; // 图片高度
        int width; //  图片宽度
        char* date; //图片数据
        size_t data_len; // 图片字节长度
    };

    struct track_cache {
        std::unordered_map<int, face_box> track_history;
        std::unordered_map<int, abi::string> track_history_id;
        int index = 0;
    };


    /**
     * @brief   动作活体类型枚举
     */
    enum action_live_type {
        BDFACE_ACTION_LIVE_BLINK      = 0, // 眨眨眼
        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // 张张嘴
        BDFACE_ACTION_LIVE_NOD        = 2, // 点点头
        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // 左摇头
        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // 右摇头
    };

    enum guid_type {
        longinus_guid      = 0, //人脸识别
        romancia_guid      = 1, //人脸对齐
        damocles_guid      = 2, //活体检测
        selene_guid        = 3, // 256维特征提取
        irisviel_guid      = 4, //人脸库
        irisviel_mask_guid = 5 //口罩人脸库
    };
} // namespace glasssix::face