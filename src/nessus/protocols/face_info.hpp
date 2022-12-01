#pragma once

#include <cstdint>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct attributes_info {
        GX_BEGIN_FIELDS(attributes_info);
        GX_FIELD(std::int32_t, glass_index);
        GX_FIELD(std::int32_t, mask_index);
        GX_FIELD(float, yaw);
        GX_FIELD(float, pitch);
        GX_FIELD(float, roll);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_rect_with_face_info {
        struct point {
            GX_BEGIN_FIELDS(point);
            GX_FIELD(std::int32_t, x);
            GX_FIELD(std::int32_t, y);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(face_rect_with_face_info);
        GX_FIELD(std::int32_t, x);
        GX_FIELD(std::int32_t, y);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(float, confidence);
        GX_FIELD(attributes_info, attributes);
        GX_FIELD(std::vector<point>, landmark);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct face_rect {
        GX_BEGIN_FIELDS(face_rect);
        GX_FIELD(std::int32_t, x);
        GX_FIELD(std::int32_t, y);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
} // namespace glasssix::face
