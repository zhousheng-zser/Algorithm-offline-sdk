#pragma once

#include <cstdint>
#include <vector>

// 安全帽信息
struct helmet_info {
    struct boxes {
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
        float score; // 置信度
    };

    std::vector<boxes> with_helmet_list; //  带安全帽
    std::vector<boxes> with_hat_list; //  带了帽子,但不是安全帽 
    std::vector<boxes> head_list; //  检测出人头, 没有帽子
};