#pragma once

#include <cstdint>

#if GX_IS_GXOFFLINERECOGNITION_IMPL
#include <g6/json_extensions.hpp>
#endif
typedef unsigned char uchar;

namespace glasssix {
#include "detail/reflection_directive_compat_start.frag.hpp"
    // 睡岗信息
    struct sleep_info {
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
        GX_BEGIN_FIELDS(sleep_info);

        GX_FIELD(abi::vector<boxes>, desk_list); //   趴桌子
        GX_FIELD(abi::vector<boxes>, lying_list); //  躺着
        GX_FIELD(abi::vector<boxes>, standing_list); // 站着
        GX_FIELD(abi::vector<boxes>, work_list); // 工作
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
#include "detail/reflection_directive_compat_end.frag.hpp"
} // namespace glasssix
