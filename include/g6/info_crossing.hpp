#pragma once

#include <cstdint>
#include <vector>

// 翻越信息
struct crossing_info {
    struct boxes {
        float score;
        int  x1;
        int  y1;
        int  x2;
        int  y2;
    };
    std::vector<boxes> crossing_list;//翻越的人
};