#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 姿态信息
    struct posture_info {
        GX_BEGIN_FIELDS(posture_info);
        struct location_boxes {
            GX_BEGIN_FIELDS(location_boxes);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct key_points_boxes {
            GX_BEGIN_FIELDS(key_points_boxes);
            GX_FIELD(std::int32_t, x); // 检出坐标x
            GX_FIELD(std::int32_t, y); // 检出坐标y
            GX_FIELD(float, point_score); // 关键点置信度
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_FIELD(abi::vector<key_points_boxes>, key_points); // 17 个关键点数组
        GX_FIELD(location_boxes, location); // 人物框体
        GX_FIELD(float, score); // 置信度

        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
