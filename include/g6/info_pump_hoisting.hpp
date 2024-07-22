#pragma once

#include <cstdint>
#include <vector>

// 区域信息
struct pump_hoisting_info {
    struct boxes {
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
        int x4;
        int y4;
    };
    std::vector<boxes> dangerous_region;
};
