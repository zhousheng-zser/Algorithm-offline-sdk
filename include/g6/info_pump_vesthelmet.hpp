#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>

typedef unsigned char uchar;

namespace glasssix {
    // 天车工信息
    struct pump_vesthelmet_info {
        struct boxes {
            float score{}; // 分类的置信度
            std::int32_t category{}; // 类型  -1未穿反光衣、0不带安全帽、1戴安全帽、2戴其他帽子，3没戴安全帽低置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> pump_vesthelmet_list{}; // 天车工:穿了反光衣的人
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
