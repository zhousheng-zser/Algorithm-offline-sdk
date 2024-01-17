#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 徘徊信息
    struct wander_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(float, cosine_similarity); // 相似度   没匹配到人值为0
            GX_FIELD(std::int32_t, id); // 此人在特征库的id号
            GX_FIELD(std::int64_t, last_show_time); // 此人最后一次出现的时间
            GX_FIELD(std::int64_t, first_show_time); // 此人第一次出现的时间
            GX_FIELD(float, score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;
            std::int64_t sum_time;//出现时长

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(wander_info);

        GX_FIELD(abi::vector<boxes>, person_info); // 行人信息
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    // 越界信息
    struct wander_limit_info : public wander_info {
         wander_limit_info(wander_info& temp){
            person_info.swap(temp.person_info);
         }
        // 行人轨迹线段
         struct segment {
            std::int32_t x1, y1, x2, y2;
         };
         abi::vector<segment> segment_info;
    };
} // namespace glasssix
