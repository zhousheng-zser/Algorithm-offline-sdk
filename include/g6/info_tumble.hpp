#pragma once

#include <cstdint>

#include "gx_pedestrian_api.hpp"
#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 跌倒信息
    struct tumble_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(tumble_info);

        GX_FIELD(abi::vector<boxes>, tumble_list); // 跌倒的
        GX_FIELD(abi::vector<boxes>, stand_list); // 站立的
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
