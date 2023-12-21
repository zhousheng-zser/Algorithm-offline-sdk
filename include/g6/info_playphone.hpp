#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 玩手机信息
    struct playphone_info {
        struct boxes {
            GX_BEGIN_FIELDS(boxes);
            GX_FIELD(float, man_score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct error_list {
            GX_BEGIN_FIELDS(error_list);
            GX_FIELD(float, nose);  // 检出鼻子
            GX_FIELD(float, r_eye);  // 检出右眼
            GX_FIELD(float, l_eye);  // 检出左眼
            GX_FIELD(float, r_hand); // 检出右手
            GX_FIELD(float, l_hand); // 检出左手
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct bodyerror_boxes {
            GX_BEGIN_FIELDS(bodyerror_boxes);
            GX_FIELD(error_list, error_keypoints); // 错误列表
            GX_FIELD(float, man_score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct playphone {
            GX_BEGIN_FIELDS(playphone);
            GX_FIELD(float, phone_score); // 置信度
            GX_FIELD(std::int32_t, x1);   // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1);   // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2);   // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2);   // 检出框体右下坐标y
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        struct playphone_boxes {
            GX_BEGIN_FIELDS(playphone_boxes);
            GX_FIELD(abi::vector<playphone>,phone_list);//手机列表
            GX_FIELD(float, man_score); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(playphone_info);

        GX_FIELD(abi::vector<bodyerror_boxes>, bodyerror_list); //  错误列表
        GX_FIELD(abi::vector<boxes>, norm_list);                //  没在玩手机
        GX_FIELD(abi::vector<playphone_boxes>, playphone_list); //  在玩手机
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix
