#pragma once

#include <cstdint>

#include <g6/abi/vector.hpp>

typedef unsigned char uchar;
namespace glasssix {
    // 打架信息
    struct fighting_info {
        struct box {
        float score{}; // 置信度
        std::int32_t category{}; // 是否打架
		std::int32_t x1{}; // 检出框体左上坐标x
		std::int32_t y1{}; // 检出框体左上坐标y
		std::int32_t x2{}; // 检出框体右下坐标x
		std::int32_t y2{}; // 检出框体右下坐标y
        enum class json_serialization { snake_case };
        };
        abi::vector<box> fight_list{}; // 打架区域
        abi::vector<box> normal_list{}; // 正常区域
        enum class json_serialization { snake_case };
    };
    // 打架区域点(roi区域)
    typedef struct {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
        std::int32_t w; // 宽度w
        std::int32_t h; // 高度h
    } fighting_roi;
} // namespace glasssix
