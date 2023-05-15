#pragma once

#include "../compat.hpp"
#include "image_info.hpp"

#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <span>

namespace glasssix {
    class image_converter {
    public:
        using result_handler = std::function<void(std::span<const std::byte> buffer)>;

        GX_API(MPP) image_converter(const image_info& source, const image_info& destination);
        GX_API(MPP) image_converter(image_converter&&) noexcept;
        GX_API(MPP) ~image_converter();
        GX_API(MPP) image_converter& operator=(image_converter&&) noexcept;
        GX_API(MPP) void commit(std::span<const std::byte> buffer, const result_handler& handler) const;

    private:
        class impl;

        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
