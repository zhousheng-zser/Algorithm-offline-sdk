#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 区域信息
    struct pump_hoisting_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右上坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右上坐标y
            GX_FIELD(std::int32_t, x3); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y3); // 检出框体右下坐标y
            GX_FIELD(std::int32_t, x4); // 检出框体左下坐标x
            GX_FIELD(std::int32_t, y4); // 检出框体左下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(pump_hoisting_info);

        GX_FIELD(abi::vector<boxes>, dangerous_region); // 危险区域列表
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
