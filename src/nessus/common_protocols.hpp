#pragma once

#include <concepts>
#include <string_view>
#include <type_traits>
#include <utility>

#include <g6/json_compat.hpp>
#include <g6/meta/literal_string.hpp>
#include <g6/meta/identifier.hpp>


namespace glasssix {
    struct parser_result_status {

        std::int32_t code{};
        std::string message{};


        enum class json_serialization { snake_case };

        void ensure() const;
    };

    template <typename T>
    concept parser_status_result = requires(T obj) {
        { obj.status } -> std::same_as<parser_result_status&>;
                                   };

    template <json_serializable In, json_serializable Out>
    struct parser_inout {
        using in_type  = In;
        using out_type = Out;
    };

    template <typename T>
    concept parser_inout_prototype = json_serializable<typename T::in_type> && json_serializable<typename T::out_type>;

    template <parser_inout_prototype T>
    using parser_in_t = typename T::in_type;

    template <parser_inout_prototype T>
    using parser_out_t = typename T::out_type;

    template <parser_inout_prototype T>
    inline constexpr auto parser_text_v = [] {
        constexpr std::string_view text{meta::get_literal_string_t<T, {.shortened = true}>()};

        return text.substr(text.rfind(U8("::")) + 1);
    }();

    template <typename T>
        requires parser_status_result<std::decay_t<T>>
    void check_result(T&& result) {
        std::forward<T>(result).status.ensure();
    }
} // namespace glasssix
