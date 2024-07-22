#pragma once

#include <cstdint>
#include <vector>

// 泵业大门状态信息
struct pump_gate_status_info {
    std::string security_status; // secure:安全   dangerous:危险
};
