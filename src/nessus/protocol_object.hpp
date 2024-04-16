#pragma once

#include <memory>
#include <type_traits>

#include <concepts>

namespace glasssix {
    struct protocol_object {
        std::shared_ptr<void> opaque;

        template <std::derived_from<protocol_object> T>
            requires std::is_aggregate_v<T>
        explicit operator T() const {
            return T{{opaque}};
        }
    };

    template <typename T>
    concept concrete_protocol_object = std::derived_from<T, protocol_object> && std::is_aggregate_v<T>;
} // namespace glasssix
