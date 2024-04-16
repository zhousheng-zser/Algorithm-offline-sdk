#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 定制灯光信息
    struct pump_light_info {
        float score{}; // 置信度
        bool light_status{}; // true 开灯  false 关灯
        enum class json_serialization { snake_case };
    };
    // 灯光区域点
    struct pump_light_point {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
    };

} // namespace glasssix
