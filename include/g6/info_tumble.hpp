#pragma once

#include <cstdint>
#include <vector>

// 跌倒信息
struct tumble_info {
    struct boxes {
        float score;
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> tumble_list;// 跌倒的
    std::vector<boxes> stand_list;// 站立的
};
