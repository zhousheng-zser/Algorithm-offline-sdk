#pragma once

#include <cstdint>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 工服信息
    struct workcloth_info {
        struct boxes {
            std::int32_t x1{}; // 检出框体左上坐标x
            std::int32_t y1{}; // 检出框体左上坐标y
            std::int32_t x2{}; // 检出框体右下坐标x
            std::int32_t y2{}; // 检出框体右下坐标y
            std::int32_t is_sleeve{}; // 1 长袖 0短袖
            // 按整体、中、左、右顺序分为四个区域 每个区域十种颜色在检索区域的占比    数组长度为40(4*10)
            // 0:黑色，1:灰色，2:白色，3:红色，4:橙色，5:黄色，6:绿色，7:青色，8:蓝色，9:紫色,
            // 10:黑色，11:灰色，12:白色，13:红色，14:橙色，15:黄色，16:绿色，17:青色，18:蓝色，19:紫色,
            // 20:黑色，21:灰色，22:白色，23:红色，24:橙色，25:黄色，26:绿色，27:青色，28:蓝色，29:紫色
            // 30:黑色，31:灰色，32:白色，33:红色，34:橙色，35:黄色，36:绿色，37:青色，38:蓝色，39:紫色
            abi::vector<float> color_ratios{};
            enum class json_serialization { snake_case };
        };
        abi::vector<boxes> cloth_list{}; //   穿工服的
        enum class json_serialization { snake_case };
    };
} // namespace glasssix
