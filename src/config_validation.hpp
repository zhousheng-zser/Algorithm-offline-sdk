#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include <g6/char8_t_remediation.hpp>
#include <g6/error_extensions.hpp>
#include <g6/reflection.hpp>

namespace glasssix::face {
    template <typename T>
    struct data_range {};

    template <typename T>
    concept has_data_range = requires {
                                 { data_range<T>::min } -> std::convertible_to<T>;
                                 { data_range<T>::max } -> std::convertible_to<T>;
                             };

    template <typename T>
        requires meta::reflectable<T> && has_data_range<T>
    void validate_data(const T& data) {
        using fields_t = meta::get_fields_t<T>;

        for_each_as_values<fields_t>([&]<typename... Ts>(std::type_identity<Ts>...) {
            auto validator = [&]<typename U>(std::type_identity<U>) {
                if constexpr (std::is_arithmetic_v<U>) {
                    auto&& current = U::value_ref(data);
                    auto&& min     = U::value_ref(data_range<U>::min);
                    auto&& max     = U::value_ref(data_range<U>::max);

                    if (current < min || current > max) {
                        throw source_code_aware_runtime_error{U8("Entity"), meta::name_of_v<T>, U8("Field"),
                            std::string_view{U::name}, U8("Actual Value"), current, U8("Min"), min, U8("Max"), max};
                    }
                }
            };

            (validator(std::type_identity<Ts>{}), ...);
        });
    }
} // namespace glasssix::face
