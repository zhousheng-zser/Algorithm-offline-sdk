#pragma once

#include <cstdint>
#include <vector>

// 泵顶安全帽信息信息
struct pumptop_helmet_info {
    struct boxes {
        float score; // 人头置信度
        float helmet_score; // 安全帽分类置信度
        int category; // 类型   0人头 1戴了安全帽 2不是人头
        int  x1;
        int  y1;
        int  x2;
        int  y2;
    };
    std::vector<boxes> person_list; // 安全帽信息的人
};
