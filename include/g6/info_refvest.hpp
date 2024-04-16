#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>

typedef unsigned char uchar;

namespace glasssix {
    // 反光衣框体信息
    struct refvest_info {
        // 人脸关键点坐标
        struct boxes {
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> without_refvest_list{}; // 没穿反光衣
        abi::vector<boxes> with_refvest_list{}; // 穿了反光衣
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
