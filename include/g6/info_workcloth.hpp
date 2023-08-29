#pragma once

#include <cstdint>

#if GX_IS_GXOFFLINERECOGNITION_IMPL
#include <g6/json_extensions.hpp>
#endif
typedef unsigned char uchar;

namespace glasssix {
#include "detail/reflection_directive_compat_start.frag.hpp"
    // 工服信息
    struct workcloth_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_FIELD(std::int32_t, is_sleeve); // 1 长袖 0短袖
            GX_FIELD(float, color_conf); // 排除黑白灰后最大颜色在检索区域的占比
            /* 3:red,4:orange,5:yellow,6:green,7:cyan,8:blue,9:purple */
            GX_FIELD(std::int32_t, color_type); // 颜色类型
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(workcloth_info);

        GX_FIELD(abi::vector<boxes>, cloth_list); //   穿工服的
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
#include "detail/reflection_directive_compat_end.frag.hpp"
} // namespace glasssix
