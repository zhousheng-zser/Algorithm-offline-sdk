#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 定制灯光信息
    struct pump_light_info {
        GX_BEGIN_FIELDS(pump_light_info);
        GX_FIELD(float, score); // 置信度
        GX_FIELD(bool, light_status); // true 开灯  false 关灯
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    
    // 灯光区域点
    struct pump_light_point {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
    };

} // namespace glasssix
