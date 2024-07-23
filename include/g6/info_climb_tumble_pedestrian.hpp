#pragma once

#include <cstdint>
#include <vector>

// 攀爬跌倒信息
struct climb_tumble_pedestrian_info {
    struct boxes {
        float score; // 置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
    };
    std::vector<boxes> persion_list; // 正常状态的人
    std::vector<boxes> climb_list; // 攀爬的人
    std::vector<boxes> tumble_list; // 跌倒的人
    std::vector<boxes> disabled_list; // 残缺
    std::vector<boxes> other_list; // 其他
};