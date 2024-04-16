#pragma once

#include <cstdint>
#include <optional>

#include <g6/abi/vector.hpp>

typedef unsigned char uchar;

namespace glasssix {
    // 人脸属性
    struct attributes_info {
        std::int32_t glass_index{}; // 0: 不戴眼镜, 1: 戴眼镜，2：戴墨镜
        std::int32_t mask_index{}; // 0:不戴口罩，1:戴口罩
        float yaw{}; // 人脸偏航角 -90°到90°
        float pitch{}; // 人脸俯仰角 -90°到90°
        float roll{}; // 人脸翻滚角 -90°到90°
        enum class json_serialization { snake_case };
    };

    // 人脸基础信息
    struct face_info {
        // 人脸关键点坐标
        struct point {
            std::int32_t x{};
            std::int32_t y{};
            enum class json_serialization { snake_case };
        };
        std::int32_t x{};
        std::int32_t y{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t ori_x{};
        std::int32_t ori_y{};
        std::int32_t ori_height{};
        std::int32_t ori_width{};
        float confidence{}; // 人脸置信度
        std::optional<attributes_info> attributes{}; // 人脸属性
        abi::vector<point> landmark{}; // 人脸关键点坐标
        enum class json_serialization { snake_case };
    };

    // 人脸追踪结果
    struct face_trace_info {
        bool trace_success{}; // 追踪成功与否
        std::optional<face_info> facerectwithfaceinfo{}; // 追踪人脸的新定位及信息
        std::optional <abi::string> trace_id; // 追踪人脸ID
        enum class json_serialization { snake_case };
    };

    // 人脸质量检测结果
    struct faces_blur {
        abi::vector<face_info> facerectwithfaceinfo_list{}; // 人脸的定位及信息
        abi::vector<float> clarity{}; // 人脸质量程度,值为[0, 1]，值越小表明人脸质量越好
        enum class json_serialization { snake_case };
    };
    // 人脸属性检测
    struct attributes {
        std::int32_t age{}; // 0: (0,15)岁 1:[15,35)岁 2:[35,55)岁 3:大于等于55岁
        std::int32_t gender{}; // 0:女 1:男
        std::int32_t mask{}; // 0不戴口罩 1:戴口罩
        std::int32_t glass{}; // 0:不戴眼镜 1:戴眼镜
        enum class json_serialization { snake_case };
    };

    // 静默活体检测结果
    struct spoofing_probability {
        abi::vector<float> prob; // 活体检测分类结果:prob[0]:打印图像概率 prob[1]:活体概率 prob[2]:视频图像概率
        enum class json_serialization { snake_case };
    };

    // 人脸静默活体检测结果
    struct faces_spoofing {
        abi::vector<face_info> facerectwithfaceinfo_list{}; // 人脸的定位及信息
        abi::vector<spoofing_probability> spoofing_result{}; // 静默活体检测结果
        enum class json_serialization { snake_case };
    };

    // 人脸特征值数据
    struct feature_info {
        abi::vector<float> feature{}; // 人脸特征向量
        enum class json_serialization { snake_case };
    };

    // 人脸特征值结果
    struct faces_feature {
        abi::vector<face_info> facerectwithfaceinfo_list{}; // 人脸的定位及信息
        abi::vector<feature_info> features{}; // 人脸特征值数组
        std::vector<uchar> img_buffer{}; // 最大人脸的图片buffer
        enum class json_serialization { snake_case };
    };

    // 人脸搜索数据
    struct faces_search_data {
        abi::string key{}; // 人脸键值
        enum class json_serialization { snake_case };
    };

    // 人脸搜索结果数组
    struct faces_search_info {
        // 人脸搜索结果
        struct database_result {
            faces_search_data data{}; // 人脸搜索数据
            float similarity{}; // 相似度
            enum class json_serialization { snake_case };
        };
        abi::vector<database_result> result{};
        enum class json_serialization { snake_case };
    };

    // 融合人脸识别结果数组
    struct faces_integration_search_info {
        // 人脸搜索结果
        abi::vector<faces_search_info::database_result> result{};
        float prob{}; // 活体得分
        enum class json_serialization { snake_case };
    };

    // 多人脸搜索数组的单个结果 一个人脸只需要最相似的一个结果
    struct faces_search_one_info {
        // 人脸搜索结果
        std::optional<faces_search_info::database_result> result{};
        std::optional<float> prob{}; // 活体得分
        face_info facerectwithfaceinfo{}; // 人脸基础信息
        enum class json_serialization { snake_case };
    };

    // 特征值库操作返回值
    struct face_user_result {
        abi::string key{}; // 键值
        int32_t success{}; // 状态码
        std::optional<face_info> facerectwithfaceinfo{}; // 人脸基础信息
        std::vector<uchar> img_buffer{}; // 裁剪后的图片
        enum class json_serialization { snake_case };
    };

    // 动作活体类型枚举
    enum action_live_type {
        BDFACE_ACTION_LIVE_BLINK      = 0, // 眨眨眼
        BDFACE_ACTION_LIVE_OPEN_MOUTH = 1, // 张张嘴
        BDFACE_ACTION_LIVE_NOD        = 2, // 点点头
        BDFACE_ACTION_LIVE_LEFT_HEAD  = 3, // 左摇头
        BDFACE_ACTION_LIVE_RIGHT_HEAD = 4 // 右摇头
    };

} // namespace glasssix
