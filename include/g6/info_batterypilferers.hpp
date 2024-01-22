#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 偷电瓶信息
    struct batterypilferers_info {
        GX_BEGIN_FIELDS(batterypilferers_info);
        GX_FIELD(float, score); // 置信度
        GX_FIELD(std::int32_t, category); // 是否偷电瓶
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
