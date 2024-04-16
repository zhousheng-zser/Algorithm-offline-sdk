#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;
namespace glasssix {
    // 焊接信息
    struct pump_weld_info {
        struct boxes {
            struct weld_box {
                std::int32_t x1{}; // 焊接框体左上坐标x
                std::int32_t y1{}; // 焊接框体左上坐标y
                std::int32_t x2{}; // 焊接框体右下坐标x
                std::int32_t y2{}; // 焊接框体右下坐标y
                enum class json_serialization { snake_case };
            };
            std::int32_t category{}; // 0标准焊接 1不规范焊接
            std::int32_t can_x1{}; // 焊接候选框体左上坐标x
            std::int32_t can_y1{}; // 焊接候选框体左上坐标y
            std::int32_t can_x2{}; // 焊接候选框体右下坐标x
            std::int32_t can_y2{}; // 焊接候选框体右下坐标y
            abi::vector<weld_box> weld_list{}; // 焊接框体列表
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> persons_weld{}; // 人焊接
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
