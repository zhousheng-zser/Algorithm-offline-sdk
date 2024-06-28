#pragma once

#include <cstdint>
#include <vector>

// 攀爬信息
struct climb_info {
    struct boxes {
        float score;
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> climb_list;
    std::vector<boxes> normal_list;
};
