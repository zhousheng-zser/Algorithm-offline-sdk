#pragma once

#include <cstdint>
#include <vector>

// 泵业工作状态信息
struct pump_work_status_info {
    std::string security_status; // working:工作中   vacancy:空置
};

// 工作区域点
struct pump_work_status_point {
    std::int32_t x; // 坐标x
    std::int32_t y; // 坐标y
};
