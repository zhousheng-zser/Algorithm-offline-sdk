#pragma once

#include "common_types.hpp"

#include <cstddef>
#include <span>

namespace glasssix {
    struct frame_info {
        pixel_format_type format;
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t h_stride;
        std::uint32_t v_stride;
        std::span<const std::byte> buffer;
    };
} // namespace glasssix
