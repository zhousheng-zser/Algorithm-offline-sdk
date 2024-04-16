#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 人头信息
    struct head_info {
        float score{}; // 置信度
        std::int32_t x1{}; // 检出框体左上坐标x
        std::int32_t y1{}; // 检出框体左上坐标y
        std::int32_t x2{}; // 检出框体右下坐标x
        std::int32_t y2{}; // 检出框体右下坐标y
        enum class json_serialization { snake_case };
    };

} // namespace glasssix
