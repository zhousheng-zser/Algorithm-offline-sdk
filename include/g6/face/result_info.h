#pragma once

#include <unordered_map>

#include <g6/format_remediation.hpp>
#include <g6/char8_t_remediation.hpp>
#include <g6/logger.hpp>
#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
#include <proxy/proxy.h>
#include <optional>


//namespace glasssix::face {
//
//    struct attributes {
//        std::int32_t glass_index;
//        std::int32_t mask_index;
//        float yaw;
//        float pitch;
//        float roll;
//    };
//    struct face_info {
//        struct point {
//            std::int32_t x;
//            std::int32_t y;
//        };
//        std::int32_t  x;
//        std::int32_t  y;
//        std::int32_t  height;
//        std::int32_t  width;
//        float confidence;
//        std::optional<attributes> attributes;
//        abi::vector<point> landmark;
//    };
//
//    struct face_trace_info {
//        bool trace_success;
//        face_info facerectwithfaceinfo;
//        abi::string trace_id;
//
//    };
//    //人脸质量检测结果
//    struct faces_blur {
//        abi::vector<face_info> facerectwithfaceinfo_list; // 人脸基础信息
//        abi::vector<float> clarity; // 人脸质量程度
//
//    };
//
//    struct spoofing_probability {
//        abi::vector<float>  prob;
//    };
//
//    struct faces_spoofing {
//        abi::vector<face_info> facerectwithfaceinfo_list; // 人脸基础信息
//        abi::vector<spoofing_probability>  spoofing_result;
//    };
//
//    struct feature_info {
//        abi::vector<float> feature;
//    };
//
//    // 特征值
//    struct faces_feature {
//        abi::vector<face_info> facerectwithfaceinfo_list; // 人脸基础信息
//        abi::vector<feature_info> features; // 特征值数组
//
//    };
//    
//    struct faces_search_data {
//        abi::vector<float> feature;
//        abi::string key;
//    };
//
//    struct faces_search_info {
//        struct database_result {
//            faces_search_data data;
//            float similarity;
//        };
//        abi::vector<database_result> result;
//    };
//
//
//
//
//    ////人脸属性
//    //struct face_box_attributes {
//    //    GX_BEGIN_FIELDS(face_box_attributes);
//    //    GX_FIELD(int, glass_index); // 是否戴眼镜
//    //    GX_FIELD(int, mask_index); // 是否戴口罩
//    //    GX_FIELD(float, yaw); // 人脸偏航角
//    //    GX_FIELD(float, pitch); // 人脸俯仰角
//    //    GX_FIELD(float, roll); // 人脸翻滚角
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//    ////人脸关键点
//    //struct face_box_landmark {
//    //    GX_BEGIN_FIELDS(face_box_landmark);
//    //    GX_FIELD(int, x); // x坐标
//    //    GX_FIELD(int, y); // y坐标
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//    ////人脸基础信息
//    //struct face_box {
//    //    GX_BEGIN_FIELDS(face_box);
//    //    GX_FIELD(int, x); // 人脸x坐标
//    //    GX_FIELD(int, y); // 人脸y坐标
//    //    GX_FIELD(int, height); // 人脸高度
//    //    GX_FIELD(int, width); // 人脸宽度
//    //    GX_FIELD(float, confidence); // 人脸置信度
//    //    GX_FIELD(face_box_attributes, attributes); // 人脸属性
//    //    GX_FIELD(abi::vector<face_box_landmark>, landmark); // 人脸5点关键点
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//    ////人脸追踪
//    //struct track_face_box {
//    //    GX_BEGIN_FIELDS(track_face_box);
//    //    face_info _face_box; // 人脸基础信息
//    //    bool trace_success; // 追踪是否成功
//    //    abi::string trace_id; //人脸id
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//    // 底库用户信息
//    //struct face_info_data {
//    //    GX_BEGIN_FIELDS(face_info_data);
//    //    GX_FIELD(abi::string, key); //键值
//    //    GX_FIELD(abi::vector<float>, feature); // 特征值数组
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//    //// 搜索底库用户结果
//    //struct face_info {
//    //    GX_BEGIN_FIELDS(face_info);
//    //    GX_FIELD(float, similarity); //相似度
//    //    GX_FIELD(face_info_data, data); // 键值和特征值
//    //    GX_END_FIELDS;
//    //    GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
//    //};
//
//
//    
//    //动作活体类型枚举
//    enum action_live_type {
//        BDFACE_ACTION_LIVE_BLINK      = 0, // 眨眨眼
//        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // 张张嘴
//        BDFACE_ACTION_LIVE_NOD        = 2, // 点点头
//        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // 左摇头
//        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // 右摇头
//    };
//
//} // namespace glasssix::face