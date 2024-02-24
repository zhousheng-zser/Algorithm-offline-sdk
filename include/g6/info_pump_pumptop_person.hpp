#pragma once

#include <cstdint>

#include <g6/json_extensions.hpp>
typedef unsigned char uchar;

namespace glasssix {
    // 泵顶行人信息
    struct pump_pumptop_person_info {
        struct boxes {
        struct pump_point {
                GX_BEGIN_FIELDS(pump_point);
                GX_FIELD(std::int32_t, x); // 坐标x
                GX_FIELD(std::int32_t, y); // 坐标y
                GX_END_FIELDS;
                GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
            };
            GX_BEGIN_FIELDS(boxes);

            GX_FIELD(abi::vector<pump_point>, pump);
            GX_FIELD(std::int32_t, category); // 置信度
            GX_FIELD(std::int32_t, x1); // 检出框体左上坐标x
            GX_FIELD(std::int32_t, y1); // 检出框体左上坐标y
            GX_FIELD(std::int32_t, x2); // 检出框体右下坐标x
            GX_FIELD(std::int32_t, y2); // 检出框体右下坐标y
            GX_END_FIELDS;
            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(pump_pumptop_person_info);

        GX_FIELD(abi::vector<boxes>, persons_in_pumptop); // 泵顶行人信息
        GX_FIELD(abi::vector<boxes>, persons_out_pumptop); // 非泵顶行人信息
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

} // namespace glasssix
