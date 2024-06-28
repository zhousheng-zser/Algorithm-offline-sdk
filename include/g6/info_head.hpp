#pragma once

#include <cstdint>
#include <vector>

// 人头信息

struct head_info {
    float score; // 置信度
    int x1; // 检出框体左上坐标x
    int x2; // 检出框体右下坐标x
    int y1; // 检出框体左上坐标y
    int y2; // 检出框体右下坐标y
};