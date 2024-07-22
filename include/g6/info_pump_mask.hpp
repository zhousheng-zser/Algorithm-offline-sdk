#pragma once

#include <cstdint>
#include <vector>

// 防护面罩信息
struct pump_mask_info {
    struct boxes {
        float score;
        int category;// 2:人脸什么都没带 3 : 戴了口罩(口罩不 是防护面罩)
        int  x1;
        int  y1;
        int  x2;
        int  y2;
    };
    std::vector<boxes> pump_head_list;// 没戴面罩的人
};
