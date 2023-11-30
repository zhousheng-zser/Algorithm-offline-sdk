#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 打电话信息
    struct onphone_info {
        struct norm_boxes {
            GX_BEGIN_FIELDS(norm_boxes);
            GX_FIELD(float, head_score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct onphone_boxes {

            struct phone_boxes {
                GX_BEGIN_FIELDS(phone_boxes);
                GX_FIELD(float, phone_score); // 置信度
                GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
                GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
                GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
                GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
                GX_END_FIELDS;

                GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
            };

            GX_BEGIN_FIELDS(onphone_boxes);
            GX_FIELD(float, head_score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_FIELD(abi::vector<phone_boxes>, phone_list);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(onphone_info);

        GX_FIELD(abi::vector<norm_boxes>, norm_list); //   没打电话
        GX_FIELD(abi::vector<onphone_boxes>, onphone_list); //  打电话的
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
