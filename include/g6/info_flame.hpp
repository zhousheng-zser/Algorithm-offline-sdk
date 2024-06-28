#pragma once

#include <cstdint>

#include <struct_json.hpp>
typedef unsigned char uchar;

namespace glasssix {

    struct flame_info {
        struct boxes {
            int x1;
            int y1;
            int x2;
            int y2;
        };
        std::vector<boxes> fire_list;
    };

    DEFINE_STRUCT_SCHEMA(flame_info::boxes, 
        DEFINE_STRUCT_FIELD(int ,x1),
        DEFINE_STRUCT_FIELD(int ,y1),
        DEFINE_STRUCT_FIELD(int ,x2),
        DEFINE_STRUCT_FIELD(int ,y2)
    );

    DEFINE_STRUCT_SCHEMA(flame_info, 
        DEFINE_STRUCT_FIELD(boxes, "boxes"), 
        DEFINE_STRUCT_FIELD(fire_list, "fire_list")
    );

} // namespace glasssix
