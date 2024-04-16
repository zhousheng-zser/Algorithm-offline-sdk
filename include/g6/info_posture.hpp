#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 姿态信息
    struct posture_info {
        struct location_boxes {
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        struct key_points_boxes {
            std::int32_t x{}; // 检出坐标x
            std::int32_t y{}; // 检出坐标y
            float point_score{}; // 关键点置信度
            enum class json_serialization { snake_case };
        };
        abi::vector<key_points_boxes> key_points{}; // 17 个关键点数组
        location_boxes location{}; // 人物框体
        float score{}; // 置信度
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
