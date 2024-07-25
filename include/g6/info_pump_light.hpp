#pragma once

#include <cstdint>
#include <vector>

// 泵业灯光信息
struct pump_light_info {
        float score;
        bool light_status;
};

// 灯光区域点
struct pump_light_point {
    int x; // 坐标x
    int y; // 坐标y
};
