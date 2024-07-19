#pragma once

#include <cstdint>
#include <vector>

// 车辆信息
struct vehicle_info {
    struct boxes {
        int category;
        float score; // 置信度
        // 目前会返回五边形:共五个顶点,以左上角的顶点为第一个点,顺时针//& 注意,会存在第五个点与第一个点重合的情况
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
        int x4;
        int y4;
        int x5;
        int y5;
    };
    std::vector<boxes> vehicle_list;
};
