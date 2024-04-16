#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>

typedef unsigned char uchar;

namespace glasssix {
    // 车辆信息
    struct vehicle_info {
        struct boxes {
            int category{}; // 类别
            float score{}; // 置信度
            // 目前会返回五边形:共五个顶点,以左上角的顶点为第一个点,顺时针//& 注意,会存在第五个点与第一个点重合的情况
            std::int32_t x1{};
            std::int32_t y1{};
            std::int32_t x2{};
            std::int32_t y2{};
            std::int32_t x3{};
            std::int32_t y3{};
            std::int32_t x4{};
            std::int32_t y4{};
            std::int32_t x5{};
            std::int32_t y5{};
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> vehicle_list{}; // 车
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
