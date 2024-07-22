#pragma once

#include <cstdint>
#include <vector>

// 泵顶行人信息
struct pump_pumptop_person_info {
    struct boxes {
        struct pump_point {
            int x; // 坐标x
            int y; // 坐标y
        };
        std::vector<pump_point> pump;
        int category;//类型
        float score; // 置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y
    };

    std::vector<boxes> persons_in_pumptop; // 泵顶行人信息
    std::vector<boxes> persons_out_pumptop; // 非泵顶行人信息
};