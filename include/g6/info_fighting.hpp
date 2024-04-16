#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>

typedef unsigned char uchar;
namespace glasssix {
    // 打架信息
    struct fighting_info {
        float score{}; // 置信度
        std::int32_t category{}; // 是否打架
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
