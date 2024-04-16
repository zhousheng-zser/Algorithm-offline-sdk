#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 抽烟信息
    struct smoke_info {
        struct key_point {
            GX_BEGIN_FIELDS(key_point);
            GX_FIELD(float, point_score); // 关键点的置信度
            GX_FIELD(std::int32_t, x1);   // 关键点的坐标x
            GX_FIELD(std::int32_t, y1);   // 关键点的坐标y
            GX_END_FIELDS;
 
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_FIELD(abi::vector<key_point>, key_points);//关键点数组
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(smoke_info);

        GX_FIELD(abi::vector<boxes>, norm_list); // 不抽烟的
        GX_FIELD(abi::vector<boxes>, smoke_list); // 抽烟的
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
