#pragma once

#include <cstdint>
#include <vector>

// 攀爬信息
struct crowd_info {
    struct boxes {
        int category;
        int  x1;
        int  x2;
        int  y1;
        int  y2;
    };
    std::vector<boxes> head_list;// 人头坐标
    std::vector<boxes> cluster_list;// 小团体框
};
