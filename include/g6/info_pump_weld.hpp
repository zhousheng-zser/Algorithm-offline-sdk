#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 焊接信息
    struct pump_weld_info {
        struct boxes {
            struct weld_box {
                GX_FIELD(weld_box);
                GX_FIELD(std::int32_t, x1); // 焊接框体左上坐标x
                GX_FIELD(std::int32_t, y1); // 焊接框体左上坐标y
                GX_FIELD(std::int32_t, x2); // 焊接框体右下坐标x
                GX_FIELD(std::int32_t, y2); // 焊接框体右下坐标y
                GX_END_FIELDS;
                GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
            } GX_BEGIN_FIELDS(boxes);
            GX_FIELD(std::int32_t, category); // 0标准焊接 1不规范焊接
            GX_FIELD(std::int32_t, can_x1); // 焊接候选框体左上坐标x
            GX_FIELD(std::int32_t, can_y1); // 焊接候选框体左上坐标y
            GX_FIELD(std::int32_t, can_x2); // 焊接候选框体右下坐标x
            GX_FIELD(std::int32_t, can_y2); // 焊接候选框体右下坐标y
            GX_FIELD(abi::vector<weld_box>, weld_list); // 焊接框体列表
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(pump_weld_info);

        GX_FIELD(abi::vector<boxes>, persons_weld); // 人焊接
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
