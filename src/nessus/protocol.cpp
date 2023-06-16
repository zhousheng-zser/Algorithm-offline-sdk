#include "protocol.hpp"

#include "common_protocols.hpp"

#include <cstdint>
#include <functional>

#include <g6/error_extensions.hpp>
#include <g6/exception.hpp>
#include <g6/format_remediation.hpp>
#include <g6/functional.hpp>
#include <g6/json_extensions.hpp>
#include <g6/reflection.hpp>

#include <parser_c.hpp>
//#include "include/parser.hpp"

namespace glasssix {
    namespace {
        template <typename T>
        using nessus_resource = std::unique_ptr<T, decltype([](T* inner) { parser_free(inner); })>;

        struct parser_delete_param {
            GX_BEGIN_FIELDS(parser_delete_param);
            GX_FIELD(std::string, instance_guid);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE_DEFAULT;
        };

        struct parser_init_plugin_result {
            GX_BEGIN_FIELDS(parser_init_plugin_result);
            GX_FIELD(parser_result_status, status);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE_DEFAULT;
        };

        struct parser_new_result {
            GX_BEGIN_FIELDS(parser_new_result);
            GX_FIELD(parser_result_status, status);
            GX_FIELD(std::string, instance_guid);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct protocol_object_data {
            std::string instance_uuid;
            std::function<void()> deleter;

            protocol_object_data(std::string_view instance_uuid, const std::function<void()>& deleter)
                : instance_uuid{instance_uuid}, deleter{deleter} {}

            ~protocol_object_data() {
                invoke_optional(deleter);
            }
        };

        std::shared_ptr<protocol_object_data> get_protocol_object_data(const protocol_object& instance) {
            return std::static_pointer_cast<protocol_object_data>(instance.opaque);
        }

        std::string to_string(const protocol_object& obj) {
            return std::to_string(reinterpret_cast<std::uintptr_t>(obj.opaque.get()));
        }

        template <typename T = json>
        T parse_raw_result(char* raw_result) {
            if (nessus_resource<char> scoped_raw_result{raw_result}) {
                auto json_value = json::parse(scoped_raw_result.get(), nullptr, true, true);

                if (json_value.is_discarded()) {
                    throw source_code_aware_runtime_error(U8("Failed to parse the result as a JSON."));
                }

                if (std::same_as<T, json>) {
                    return json_value;
                } else {
                    return json_value.template get<T>();
                }
            }

            throw source_code_aware_runtime_error(U8("The result contains a null value."));
        }
    } // namespace

    namespace detail {
        std::string make_procotol_full_name(std::string_view family, std::string_view name) {
            return glasssix::format(U8("{}{}"), family, name);
        }
    } // namespace detail

    class nessus_protocol::impl {
    public:
        impl() : instance_{parser_new_instance()} {}

        void init(std::string_view config_file_path) const {
            throw_nested_and_flatten(source_code_aware_runtime_error{U8("Failed to init the nessus parser.")}, [&] {
                auto result = parse_raw_result<parser_init_plugin_result>(
                    parser_init_plugin(instance_.get(), config_file_path.data(), U8("")));

                check_result(result);
            });
        }

        protocol_object make_instance(std::string_view family, const json& param) const {
            return throw_nested_and_flatten(
                source_code_aware_runtime_error{U8("Family"), family, U8("Failed to make an instance.")}, [&] {
                    auto raw_result = invoke_raw({}, detail::make_procotol_full_name(family, U8("new")), json(param));

                    try {

                        auto result = raw_result.get<parser_new_result>();

                        check_result(result);

                        return make_protocol_object(family, result.instance_guid);
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error{U8("JSON"), raw_result.dump(4), U8("Error"), ex.what()};
                    }
                });
        }

        json invoke(
            protocol_object instance, std::string_view full_name, const json& param, std::span<char> data = {}) const {
            return throw_nested_and_flatten(
                source_code_aware_runtime_error{U8("Protocol"), full_name, U8("Instance"), to_string(instance),
                    U8("Message"), U8("Failed to invoke the protocol.")},
                [&, object_data = get_protocol_object_data(instance)] {
                    return invoke_raw(object_data ? object_data->instance_uuid : "", full_name, json(param), data);
                });
        }

    private:
        json invoke_raw(
            std::string_view instance_uuid, std::string_view full_name, json&& param, std::span<char> data = {}) const {
            if (!instance_uuid.empty()) {
                param[U8("instance_guid")] = instance_uuid;
            }
            void* instanc  = instance_.get();
            return parse_raw_result(parser_parse(
                instance_.get(), full_name.data(), param.dump().c_str(), data.data(), data.size(), nullptr, 0));
        }

        protocol_object make_protocol_object(std::string_view family, std::string_view instance_uuid) const {
            return protocol_object{.opaque{std::make_shared<protocol_object_data>(
                instance_uuid, [this, family = std::string{family}, instance_uuid = std::string{instance_uuid}] {
                    static_cast<void>(invoke_raw(instance_uuid, detail::make_procotol_full_name(family, U8("delete")),
                        parser_delete_param{.instance_guid{instance_uuid}}));
                })}};
        }

        std::unique_ptr<void, decltype([](void* inner) { parser_release_instance(inner); })> instance_;
    };

    nessus_protocol::~nessus_protocol() {}


    void nessus_protocol::init(std::string_view config_file_path) const {
        impl_->init(config_file_path);
    }

    protocol_object nessus_protocol::make_instance(std::string_view family, const json& param) const {
        return impl_->make_instance(family, param);
    }

    json nessus_protocol::invoke(
        protocol_object instance, std::string_view full_name, const json& param, std::span<char> data) const {
        return impl_->invoke(instance, full_name, param, data);
    }

    nessus_protocol::nessus_protocol() : impl_{std::make_unique<impl>()} {}
} // namespace glasssix
