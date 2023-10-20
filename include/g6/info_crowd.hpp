#pragma once

#include <cstdint>

#if GX_IS_GXOFFLINERECOGNITION_IMPL
#include <g6/json_extensions.hpp>
#endif
typedef unsigned char uchar;

namespace glasssix {
#include "detail/reflection_directive_compat_start.frag.hpp"
    // 聚众信息
    struct crowd_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(crowd_info);

        GX_FIELD(abi::vector<boxes>, head_list); // 人头坐标
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
#include "detail/reflection_directive_compat_end.frag.hpp"
    
} // namespace glasssix
