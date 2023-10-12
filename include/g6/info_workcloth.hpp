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
            // 按整体、中、左、右顺序分为四个区域 每个区域十种颜色在检索区域的占比    数组长度为40(4*10)
            // 0:黑色，1:灰色，2:白色，3:红色，4:橙色，5:黄色，6:绿色，7:青色，8:蓝色，9:紫色,
            // 10:黑色，11:灰色，12:白色，13:红色，14:橙色，15:黄色，16:绿色，17:青色，18:蓝色，19:紫色,
            // 20:黑色，21:灰色，22:白色，23:红色，24:橙色，25:黄色，26:绿色，27:青色，28:蓝色，29:紫色
            // 30:黑色，31:灰色，32:白色，33:红色，34:橙色，35:黄色，36:绿色，37:青色，38:蓝色，39:紫色
            GX_FIELD(abi::vector<float>, color_ratios); 
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
