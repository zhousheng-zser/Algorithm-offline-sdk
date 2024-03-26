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
            //目前会返回五边形:共五个顶点,以左上角的顶点为第一个点,顺时针//& 注意,会存在第五个点与第一个点重合的情况
            GX_FIELD(std::int32_t, x1);
            GX_FIELD(std::int32_t, y1);
            GX_FIELD(std::int32_t, x2);
            GX_FIELD(std::int32_t, y2);
            GX_FIELD(std::int32_t, x3);
            GX_FIELD(std::int32_t, y3);
            GX_FIELD(std::int32_t, x4);
            GX_FIELD(std::int32_t, y4);
            GX_FIELD(std::int32_t, x5);
            GX_FIELD(std::int32_t, y5);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(vehicle_info);

        GX_FIELD(abi::vector<boxes>, vehicle_list); // 车
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
