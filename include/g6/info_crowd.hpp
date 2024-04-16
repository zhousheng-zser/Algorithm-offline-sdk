#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 聚众信息
    struct crowd_info {
        struct boxes {
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            std::int32_t category{}; // 小团体分类
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> head_list{}; // 人头坐标
        abi::vector<boxes> cluster_list{}; // 小团体框
        enum class json_serialization { snake_case };
    };

} // namespace glasssix
