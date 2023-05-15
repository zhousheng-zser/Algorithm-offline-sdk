#pragma once

#include "../compat.hpp"
#include "common_types.hpp"

#include <cstddef>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <string_view>

namespace glasssix {
    class raw_packet_reader {
    public:
        GX_API(MPP) raw_packet_reader();
        GX_API(MPP) raw_packet_reader(std::span<const std::pair<std::string, std::string>> options);
        GX_API(MPP) raw_packet_reader(raw_packet_reader&&) noexcept;
        GX_API(MPP) ~raw_packet_reader();
        GX_API(MPP) raw_packet_reader& operator=(raw_packet_reader&&) noexcept;
        GX_API(MPP) void open(std::string_view uri, demuxing_media_type media_type = demuxing_media_type::video) const;
        GX_API(MPP) void close() const;
        GX_API(MPP) std::optional<std::span<const std::byte>> read_packet() const;

    private:
        class impl;

        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
