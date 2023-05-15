#pragma once

#include "../compat.hpp"

#include <cstddef>
#include <cstdint>

extern "C" {
GX_API(MPP)
void* g6_start_playback(const char* uri,
    void (*data_callback)(const std::uint8_t* data, std::size_t frame_index, std::int32_t stride, std::int32_t width,
        std::int32_t height),
    void (*error_callback)(const char* message));

GX_API(MPP) void g6_stop_playback(void* handle);
}
