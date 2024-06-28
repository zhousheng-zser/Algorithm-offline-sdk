#pragma once

#include <cstdint>
#include <vector>

// 烟雾信息
struct smog_info {
    struct boxes {
        float score;
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> smog_list;
};
