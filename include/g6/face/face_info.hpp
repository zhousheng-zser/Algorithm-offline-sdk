#pragma once

#include <cstdint>
#include <optional>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    //人脸属性
    struct attributes_info {
        GX_BEGIN_FIELDS(attributes_info);
        GX_FIELD(std::int32_t, glass_index); // 0: 不戴眼镜, 1: 戴眼镜，2：戴墨镜
        GX_FIELD(std::int32_t, mask_index); // 0:不戴口罩，1:戴口罩
        GX_FIELD(float, yaw); // 人脸偏航角 -90°到90°
        GX_FIELD(float, pitch); // 人脸俯仰角 -90°到90°
        GX_FIELD(float, roll); // 人脸翻滚角 -90°到90°
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸基础信息
    struct face_info {
        // 人脸关键点坐标
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
        GX_FIELD(float, confidence); // 人脸置信度
        GX_FIELD(std::optional<attributes_info>, attributes); //人脸属性
        GX_FIELD(abi::vector<point>, landmark); // 人脸关键点坐标
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //人脸追踪结果
    struct face_trace_info {
        GX_BEGIN_FIELDS(face_trace_info);
        GX_FIELD(bool, trace_success); //追踪成功与否
        GX_FIELD(std::optional<face_info>, facerectwithfaceinfo); //追踪人脸的新定位及信息
        GX_END_FIELDS;
        abi::string trace_id; // 追踪人脸ID

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    //人脸质量检测结果
    struct faces_blur {
        GX_BEGIN_FIELDS(faces_blur);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list); // 人脸的定位及信息
        GX_FIELD(abi::vector<float>, clarity); // 人脸质量程度,值为[0, 1]，值越小表明人脸质量越好
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 静默活体检测结果
    struct spoofing_probability {
        GX_BEGIN_FIELDS(spoofing_probability);
        GX_FIELD(
            abi::vector<float>, prob); //活体检测分类结果:prob[0]:打印图像概率 prob[1]:活体概率 prob[2]:视频图像概率
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 人脸静默活体检测结果
    struct faces_spoofing {
        GX_BEGIN_FIELDS(faces_spoofing);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list); // 人脸的定位及信息
        GX_FIELD(abi::vector<spoofing_probability>, spoofing_result); // 静默活体检测结果
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 人脸特征值数据
    struct feature_info {
        GX_BEGIN_FIELDS(feature_info);
        GX_FIELD(abi::vector<float>, feature); //人脸特征向量
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 人脸特征值结果
    struct faces_feature {
        GX_BEGIN_FIELDS(faces_feature);
        GX_FIELD(abi::vector<face_info>, facerectwithfaceinfo_list); // 人脸的定位及信息
        GX_FIELD(abi::vector<feature_info>, features); // 人脸特征值数组
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 人脸搜索数据
    struct faces_search_data {
        GX_BEGIN_FIELDS(faces_search_data);
        GX_FIELD(abi::vector<float>, feature); //人脸特征向量
        GX_FIELD(abi::string, key); //人脸键值
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 人脸搜索结果数组
    struct faces_search_info {
        // 人脸搜索结果
        GX_BEGIN_FIELDS(faces_search_info);
        struct database_result {
            GX_BEGIN_FIELDS(database_result);
            GX_FIELD(faces_search_data, data); // 人脸搜索数据
            GX_FIELD(float, similarity); // 相似度
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_FIELD(abi::vector<database_result>, result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    //特征值库增删改结果数组
    struct faces_user_add {
        GX_BEGIN_FIELDS(faces_user_add);
        GX_FIELD(bool, success);
        GX_FIELD(abi::string, reason);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    using faces_user_remove = faces_user_add;
    using faces_user_update = faces_user_add;

    //动作活体类型枚举
    enum action_live_type {
        BDFACE_ACTION_LIVE_BLINK      = 0, // 眨眨眼
        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // 张张嘴
        BDFACE_ACTION_LIVE_NOD        = 2, // 点点头
        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // 左摇头
        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // 右摇头
    };

} // namespace glasssix::face
