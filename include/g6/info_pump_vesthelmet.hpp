#pragma once

#include <cstdint>
#include <vector>

// 泵业天车工信息
struct pump_vesthelmet_info {
    struct boxes {
        float score;//置信度
        int category;// 类型  -1未穿反光衣、0不带安全帽、1戴安全帽、2戴其他帽子，3没戴安全帽低置信度
        int  x1;
        int  y1;
        int  x2;
        int  y2;
    };
    std::vector<boxes> pump_vesthelmet_list;// 天车工:穿了反光衣的人
};
