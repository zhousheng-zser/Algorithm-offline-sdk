#pragma once

#include <cstdint>

#if GX_IS_GXOFFLINERECOGNITION_IMPL
#include <g6/json_extensions.hpp>
#endif
typedef unsigned char uchar;

namespace glasssix {
#include "detail/reflection_directive_compat_start.frag.hpp"
    // 劳保信息
    struct pedestrian_labor_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_FIELD(abi::vector<bool>, category); // 0.戴劳保手套 1.戴劳保口罩 2.戴劳保护目镜
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(pedestrian_labor_info);

        GX_FIELD(abi::vector<boxes>, pedestrian_labor_list); //  劳保
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
#include "detail/reflection_directive_compat_end.frag.hpp"
} // namespace glasssix
