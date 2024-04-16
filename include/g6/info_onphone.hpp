#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 打电话信息
    struct onphone_info {
        struct norm_boxes {
            float head_score{}; // 人头置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };

        struct onphone_boxes {
            struct phone_boxes {
                float phone_score{}; // 手机置信度
                std::int32_t x1{}; // 检出框体左上坐标x
                std::int32_t y1{}; // 检出框体左上坐标y
                std::int32_t x2{}; // 检出框体右下坐标x
                std::int32_t y2{}; // 检出框体右下坐标y
                enum class json_serialization { snake_case };
            };
            float head_score{}; // 人头置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            abi::vector<phone_boxes> phone_list{};
            enum class json_serialization { snake_case };
        };
        abi::vector<norm_boxes> norm_list{}; //   没打电话
        abi::vector<onphone_boxes> onphone_list{}; //  打电话的
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
