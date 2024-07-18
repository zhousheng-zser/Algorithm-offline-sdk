#pragma once

#include <vector>

struct flame_info {
    struct boxes {
        int score;
        int x1;
        int y1;
        int x2;
        int y2;
    };
    std::vector<boxes> fire_list;
};
