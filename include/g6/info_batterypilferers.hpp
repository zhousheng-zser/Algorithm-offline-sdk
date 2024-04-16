#pragma once

#include <cstdint>
typedef unsigned char uchar;

namespace glasssix {
    // 偷电瓶信息
    struct batterypilferers_info {
        float score{}; // 置信度
        std::int32_t category{}; // 是否偷电瓶
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
