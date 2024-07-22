#pragma once

#include <cstdint>
#include <vector>

// 焊接信息
struct pump_weld_info {
    struct boxes {
        struct weld_box {
            // 焊接框体
            int x1;
            int y1;
            int x2;
            int y2;
        };
        int category; // // 0标准焊接 1不规范焊接
        // 焊接候选框体
        int  can_x1;
        int  can_y1;
        int  can_x2;
        int  can_y2;
        std::vector<weld_box> weld_list;
    };
    std::vector<boxes> persons_weld; // 焊接人
};
