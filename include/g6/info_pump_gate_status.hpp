#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 大门状态信息
    struct pump_gate_status_info {
        GX_BEGIN_FIELDS(pump_gate_status_info);

        //GX_FIELD(abi::string, security_status); // secure:安全   dangerous:危险
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

} // namespace glasssix
