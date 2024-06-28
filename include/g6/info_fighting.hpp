#pragma once

#include <cstdint>
#include <vector>

// 打架信息
struct fighting_info {
    struct boxes {
        float score; //置信度
        int category; // 是否打架
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> fight_list; // 打架区域
    std::vector<boxes> normal_list; // 正常区域
};


    // 打架区域点(roi区域)
struct fighting_roi {
    int x; // 坐标x
    int y; // 坐标y
    int w; // 宽度w
    int h; // 高度h
} ;
