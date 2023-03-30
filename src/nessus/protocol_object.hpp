#pragma once

#include <memory>
#include <type_traits>

#include <concepts/concepts.hpp>

namespace glasssix::face {
    struct protocol_object {
        std::shared_ptr<void> opaque;

        template <concepts::derived_from<protocol_object> T>
            requires std::is_aggregate_v<T>
        explicit operator T() const {
            return T{{opaque}};
        }
    };

    template <typename T>
    concept concrete_protocol_object = concepts::derived_from<T, protocol_object> && std::is_aggregate_v<T>;
} // namespace glasssix::face
