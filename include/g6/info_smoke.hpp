#pragma once

#include <cstdint>
#include <vector>

// 抽烟信息
struct smoke_info {

    struct key_point {
        float point_score; // 关键点置信度
        int x; // 关键点坐标x
        int y; // 关键点坐标y
    };

    struct boxes {
        float score; // 置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        std::vector<key_point> key_points; //关键点数组
    };

    std::vector<boxes> norm_list; //  没抽烟
    std::vector<boxes> smoke_list; // 抽烟的

};