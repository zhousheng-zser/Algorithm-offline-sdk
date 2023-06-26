#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 安全帽信息
    struct helmet_info {
        struct detected {
            GX_BEGIN_FIELDS(detected);
            GX_FIELD(float, score);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct cant_detected {
            GX_BEGIN_FIELDS(cant_detected);
            GX_FIELD(float, score);
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(helmet_info);

        GX_FIELD(abi::vector<detected>, detected_list);
        GX_FIELD(abi::vector<cant_detected>, cant_detected_list);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };


} // namespace glasssix
