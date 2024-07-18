#pragma once

#include <cstdint>
#include <vector>

// 睡岗信息
struct sleep_info {
    struct boxes {
        float score;
        int  x1;
        int  y1;
        int  x2;
        int  y2;
    };
    std::vector<boxes> lying_list;//躺着
    std::vector<boxes> work_list;//工作
};
