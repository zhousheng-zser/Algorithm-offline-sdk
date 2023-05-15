#pragma once

#include "../compat.hpp"
#include "common_types.hpp"
#include "frame_info.hpp"

#include <cstddef>
#include <functional>
#include <memory>
#include <optional>
#include <span>
#include <string_view>

namespace glasssix {
    class video_decoder {
    public:
        using stop_handler           = std::function<void()>;
        using frame_handler          = std::function<void(const frame_info& info, bool changed)>;
        using async_error_handler    = std::function<void(std::string_view message)>;
        using request_packet_handler = std::function<std::optional<std::span<const std::byte>>()>;

        GX_API(MPP) video_decoder(video_coding_type coding_type);
        GX_API(MPP) video_decoder(video_decoder&&) noexcept;
        GX_API(MPP) ~video_decoder();
        GX_API(MPP) video_decoder& operator=(video_decoder&&) noexcept;
        GX_API(MPP) void start() const;
        GX_API(MPP) void stop() const;
        GX_API(MPP) void on_stop(const stop_handler& handler) const;
        GX_API(MPP) void on_frame(const frame_handler& handler) const;
        GX_API(MPP) void on_async_error(const async_error_handler& handler) const;
        GX_API(MPP) void on_request_packet(const request_packet_handler& handler) const;

    private:
        class impl;

        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
