#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 地盖未盖盖信息
    struct pump_cover_plate_info {
        GX_BEGIN_FIELDS(pump_cover_plate_info);
        GX_FIELD(float, score); // 置信度
        GX_FIELD(bool, cover_plate_status); // false 不报警盖盖了   true 报警没盖盖
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    
    // 盖板区域点
    typedef struct {
        std::int32_t x; //坐标x
        std::int32_t y; //坐标y
    } pump_cover_plate_point;

} // namespace glasssix
