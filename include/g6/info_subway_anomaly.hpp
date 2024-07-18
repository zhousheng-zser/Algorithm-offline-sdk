#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 地铁异常信息
    struct subway_anomaly_info {
        GX_BEGIN_FIELDS(subway_anomaly_info);
        GX_FIELD(float, score); // 置信度
        GX_FIELD(bool, anomaly_status); // false 有异常  true 无异常
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    
    // 地铁门区域(roi区域)
    typedef struct {
        std::int32_t x; // 左上坐标x
        std::int32_t y; // 左上坐标y
        std::int32_t w; // 宽度w
        std::int32_t h; // 高度h
    } subway_anomaly_roi;

} // namespace glasssix
