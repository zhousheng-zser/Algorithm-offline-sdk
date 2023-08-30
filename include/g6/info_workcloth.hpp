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
            // 十种颜色在检索区域的占比  
            // 0:黑色，1:灰色，2:白色，3:红色，4:橙色，5:黄色，6:绿色，7:青色，8:蓝色，9:紫色 
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
