#pragma once

#include "common_protocols.hpp"
#include "protocol_object.hpp"

#include <memory>
#include <mutex>
#include <span>
#include <string>
#include <string_view>

#include <g6/char8_t_remediation.hpp>
#include <g6/error_extensions.hpp>
#include <g6/exception.hpp>
#include <g6/meta/literal_string.hpp>
#include <g6/naming_convention.hpp>
#include <g6/reflection.hpp>

namespace glasssix {
    namespace detail {
        template <typename T>
        struct protocol_family {
            inline static constexpr meta::literal_string value{
                convert_naming_convention_v<meta::name_of_v<T>, naming_convention::lower_case_with_underscores>,
                meta::literal_string{"."}};
        };

        std::string make_procotol_full_name(std::string_view family, std::string_view name);
    } // namespace detail

    class nessus_protocol {
    public:
        nessus_protocol();
        nessus_protocol(nessus_protocol&&) noexcept = delete;
        ~nessus_protocol();
        nessus_protocol& operator=(nessus_protocol&&) noexcept = delete;
        void init(std::string_view config_file_path) const;
        protocol_object make_instance(std::string_view family, const json& param) const;
        json invoke(
            protocol_object instance, std::string_view full_name, const json& param, std::span<char> data = {}) const;

        template <concrete_protocol_object T>
        T make_instance(const json& param) const {
            return static_cast<T>(make_instance(detail::protocol_family<T>::value, param));
        }

        template <parser_inout_prototype T, concrete_protocol_object U>
        auto invoke(U instance, const parser_in_t<T>& param, std::span<char> data = {}) const {
            return throw_nested_and_flatten(
                source_code_aware_runtime_error{U8("Message"), U8("Failed to invoke the protocol.")}, [&] {
                    auto raw_result = invoke(instance,
                        detail::make_procotol_full_name(detail::protocol_family<U>::value, parser_text_v<T>),
                        json(param), data);

                    try {
                        return raw_result.template get<parser_out_t<T>>();
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error{U8("JSON"), raw_result.dump(4), U8("Error"), ex.what()};
                    }
                });
        }

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
