#pragma once

#include <cstdint>
#include <vector>

// 反光衣信息
struct refvest_info {
    struct boxes {
        float score; // 置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
    };

    std::vector<boxes> without_refvest_list; //  没穿反光衣
    std::vector<boxes> with_refvest_list; //  穿了反光衣

};