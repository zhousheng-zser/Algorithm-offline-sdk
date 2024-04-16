#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 烟雾信息
    struct smog_info {
        struct boxes {
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> smog_list{}; // 烟
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
