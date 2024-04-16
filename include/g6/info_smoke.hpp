#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 抽烟信息
    struct smoke_info {
        struct boxes {
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> norm_list{}; // 不抽烟的
        abi::vector<boxes> smoke_list{}; // 抽烟的
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
