#pragma once

#include <cstdint>

#if GX_IS_GXOFFLINERECOGNITION_IMPL
#include <g6/json_extensions.hpp>
#endif
typedef unsigned char uchar;

namespace glasssix {
#include "detail/reflection_directive_compat_start.frag.hpp"
    // 攀爬信息
    struct climb_info {
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
        GX_BEGIN_FIELDS(climb_info);

        GX_FIELD(abi::vector<boxes>, climb_list); // 攀爬的人
        GX_FIELD(abi::vector<boxes>, normal_list); // 没攀爬的人
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
#include "detail/reflection_directive_compat_end.frag.hpp"

    // 攀爬线   由两个不同的点确定一条直线  
    struct climb_line {  
        int x1; // 第一个点坐标x
        int y1; // 第一个点坐标y
        int x2; // 第二个点坐标x
        int y2; // 第二个点坐标y
    };
    
} // namespace glasssix
