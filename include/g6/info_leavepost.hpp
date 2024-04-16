#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 离岗信息
    struct leavepost_info {
        struct boxes {
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> hat_list{}; // 在岗人头
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
