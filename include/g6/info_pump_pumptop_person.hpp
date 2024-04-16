#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 泵顶行人信息
    struct pump_pumptop_person_info {
        struct boxes {
            struct pump_point {
                std::int32_t x{}; // 坐标x
                std::int32_t y{}; // 坐标y
                enum class json_serialization { snake_case };
            };
            abi::vector<pump_point> pump{};
            std::int32_t category{}; // 类型
            float score{}; // 置信度
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> persons_in_pumptop{}; // 泵顶行人信息
        abi::vector<boxes> persons_out_pumptop{}; // 非泵顶行人信息
        enum class json_serialization { snake_case };
    };

} // namespace glasssix
