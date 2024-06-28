#pragma once

#include <cstdint>
#include <vector>

// 玩手机信息
struct playphone_info {
    struct boxes {
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        float man_score; // 置信度
    };
    struct error_list {
        float nose; // 检出鼻子
        float r_eye; // 检出右眼
        float l_eye; // 检出左眼
        float r_hand; // 检出右手
        float l_hand; // 检出左手
    };
    struct bodyerror_boxes {
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        float man_score; // 置信度
        error_list error_keypoints;
    };
    struct playphone {
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        float phone_score; // 置信度
    };
    struct playphone_boxes {
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        float man_score; // 置信度
        std::vector<playphone> phone_list; // 手机列表
    };

    std::vector<bodyerror_boxes> bodyerror_list; //  错误列表
    std::vector<boxes> norm_list; //  没在玩手机
    std::vector<playphone_boxes> playphone_list; //  在玩手机
};