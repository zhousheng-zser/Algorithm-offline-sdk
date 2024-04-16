#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 区域信息
    struct pump_hoisting_info {
        struct boxes {
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右上坐标x
            std::int32_t y2{}; // 检出框体右上坐标y
            std::int32_t x3{}; // 检出框体右下坐标x
            std::int32_t y3{}; // 检出框体右下坐标y
            std::int32_t x4{}; // 检出框体左下坐标x
            std::int32_t y4{}; // 检出框体左下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> dangerous_region{}; // 危险区域列表
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
