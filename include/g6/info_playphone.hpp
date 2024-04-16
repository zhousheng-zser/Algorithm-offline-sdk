#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 玩手机信息
    struct playphone_info {
        struct boxes {
            float man_score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        struct error_list {
            float nose{}; // 检出鼻子
            float r_eye{}; // 检出右眼
            float l_eye{}; // 检出左眼
            float r_hand{}; // 检出右手
            float l_hand{}; // 检出左手
            enum class json_serialization { snake_case };
        };
        struct bodyerror_boxes {
            error_list error_keypoints{}; // 错误列表
            float man_score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        struct playphone {
            float phone_score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        struct playphone_boxes {
            abi::vector<playphone> phone_list{}; // 手机列表
            float man_score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<bodyerror_boxes> bodyerror_list{}; //  错误列表
        abi::vector<boxes> norm_list{}; //  没在玩手机
        abi::vector<playphone_boxes> playphone_list{}; //  在玩手机
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
