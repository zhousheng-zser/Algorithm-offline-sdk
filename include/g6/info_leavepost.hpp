#pragma once

#include <cstdint>
#include <vector>

// 离岗信息
struct leavepost_info {
    struct boxes {
        float score;
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> hat_list; // 在岗人头 
};
