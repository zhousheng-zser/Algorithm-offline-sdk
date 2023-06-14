#pragma once

#include "common_types.hpp"

#include <cstdint>

namespace glasssix {
    struct image_info {
        std::int32_t width;
        std::int32_t height;
        pixel_format_type format;
    };
}
