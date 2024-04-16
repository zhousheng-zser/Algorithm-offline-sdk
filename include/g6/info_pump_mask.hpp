#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 防护面罩信息
    struct pump_mask_info {
        struct boxes {
            float score{}; // 置信度
            std::int32_t category{}; // 1戴了面罩 2没戴面罩 3不能判断戴没戴面罩
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> pump_head_list{}; // 没戴面罩的人
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
