#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 泵顶安全帽信息信息
    struct pumptop_helmet_info {
        struct boxes {
            float score{}; // 人头置信度
            float helmet_score{}; // 安全帽分类置信度
            std::int32_t category{}; // 类型   0人头 1戴了安全帽 2不是人头
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> person_list{}; // 安全帽信息的人
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
