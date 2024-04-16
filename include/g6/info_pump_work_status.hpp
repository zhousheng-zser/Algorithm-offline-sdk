#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 工作状态信息
    struct pump_work_status_info {
        // abi::string  security_status(); // working:工作中   vacancy:空置
        enum class json_serialization { snake_case };
    };
    // 工作区域点
    struct pump_work_status_point {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
    };

} // namespace glasssix
