#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 打架信息
    struct fighting_info {
        struct box {
            GX_BEGIN_FIELDS(box);
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, category); // 是否打架
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(fighting_info);
        GX_FIELD(abi::vector<box>, fight_list); // 打架区域
        GX_FIELD(abi::vector<box>, normal_list); // 正常区域
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    // 打架区域点
    typedef struct fighting_roi {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
        std::int32_t w; // 宽度w
        std::int32_t h; // 高度h
    };
} // namespace glasssix
