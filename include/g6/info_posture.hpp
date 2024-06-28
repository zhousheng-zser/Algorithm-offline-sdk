#pragma once

#include <cstdint>
#include <vector>

// 姿态信息

struct posture_info {
    struct location_boxes {
        int x1; // 检出框体左上坐标x
        int x2; // 检出框体右下坐标x
        int y1; // 检出框体左上坐标y
        int y2; // 检出框体右下坐标y
    };
    struct key_points_boxes {
        float point_score; // 关键点置信度
        int x; // 检出坐标x
        int y; // 检出坐标y
    };
    std::vector<key_points_boxes> key_points; // 17 个关键点数组
    location_boxes location; // 人物框体
    float score; // 置信度
};