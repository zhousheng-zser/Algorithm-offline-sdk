#pragma once

#include <cstdint>
#include <vector>

// 打电话信息
struct onphone_info {
    struct norm_boxes {
        float head_score; // 人头置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
    };
    struct onphone_boxes {
        struct phone_boxes {
            float phone_score; // 手机置信度
            int x1; // 检出框体左上坐标x
            int y1; // 检出框体左上坐标y
            int x2; // 检出框体右下坐标x
            int y2; // 检出框体右下坐标y
        };
        float head_score; // 人头置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        std::vector<phone_boxes> phone_list;
    };

    std::vector<norm_boxes> norm_list; //  没打电话的
    std::vector<onphone_boxes> onphone_list; //  打电话的
};