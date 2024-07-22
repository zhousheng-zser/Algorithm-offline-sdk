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
    std::int32_t x; // 坐标x
    std::int32_t y; // 坐标y
};
