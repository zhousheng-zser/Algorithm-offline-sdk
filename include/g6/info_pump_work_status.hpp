#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 工作状态信息
    struct pump_work_status_info {
        GX_BEGIN_FIELDS(pump_work_status_info);

        // GX_FIELD(abi::string, security_status); // working:工作中   vacancy:空置
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    
    // 工作区域点
    struct pump_work_status_point {
        std::int32_t x; // 坐标x
        std::int32_t y; // 坐标y
    };

} // namespace glasssix
