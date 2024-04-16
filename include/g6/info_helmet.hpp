#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 安全帽信息
    struct helmet_info {
        struct boxes {
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> with_helmet_list{}; // 带安全帽
        abi::vector<boxes> with_hat_list{}; // 带了帽子,但不是安全帽
        abi::vector<boxes> head_list{}; // 检测出人头, 没有帽子
        enum class json_serialization { snake_case };
    };

} // namespace glasssix
