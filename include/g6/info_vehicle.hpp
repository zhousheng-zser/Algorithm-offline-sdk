#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 车辆信息
    struct vehicle_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(int, category); // 类别
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(vehicle_info);

        GX_FIELD(abi::vector<boxes>, vehicle_list); // 车
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
