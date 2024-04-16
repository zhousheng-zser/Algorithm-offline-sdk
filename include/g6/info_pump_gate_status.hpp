#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 大门状态信息
    struct pump_gate_status_info {
        // GX_FIELD(abi::string, security_status); // secure:安全   dangerous:危险
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
