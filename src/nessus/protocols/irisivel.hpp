#pragma once

#include "../common_protocols.hpp"
#include "../protocol_object.hpp"
#include "face_info.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct database_record {
        GX_BEGIN_FIELDS(database_record);
        GX_FIELD(std::vector<float>, feature);
        GX_FIELD(std::string, key);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_new_param {
        GX_BEGIN_FIELDS(irisviel_new_param);
        GX_FIELD(std::int32_t, dimension);
        GX_FIELD(std::string, working_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_load_databases_param {
        GX_BEGIN_FIELDS(irisviel_load_databases_param);
        GX_FIELD(std::string, instance_guid);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_load_databases_result {
        GX_BEGIN_FIELDS(irisviel_load_databases_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_search_param {
        GX_BEGIN_FIELDS(irisviel_search_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::vector<float>, feature);
        GX_FIELD(std::optional<std::int32_t>, top);
        GX_FIELD(std::optional<float>, min_similarity);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_search_result {
        struct database_result {
            GX_BEGIN_FIELDS(database_result);
            GX_FIELD(database_record, data);
            GX_FIELD(float, similarity);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(irisviel_search_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(std::vector<database_result>, result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_contains_key_param {
        GX_BEGIN_FIELDS(irisviel_contains_key_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::string, key);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_contains_key_result {
        GX_BEGIN_FIELDS(irisviel_contains_key_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(bool, result);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_all_param {
        GX_BEGIN_FIELDS(irisviel_remove_all_param);
        GX_FIELD(std::string, instance_guid);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_all_result {
        GX_BEGIN_FIELDS(irisviel_remove_all_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_records_param {
        GX_BEGIN_FIELDS(irisviel_remove_records_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::vector<std::string>, keys);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_records_result {
        GX_BEGIN_FIELDS(irisviel_remove_records_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_record_param {
        GX_BEGIN_FIELDS(irisviel_remove_record_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::string, key);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_remove_record_result {
        GX_BEGIN_FIELDS(irisviel_remove_record_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_add_records_param {
        GX_BEGIN_FIELDS(irisviel_add_records_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::vector<database_record>, data);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_add_records_result {
        GX_BEGIN_FIELDS(irisviel_add_records_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_add_record_param {
        GX_BEGIN_FIELDS(irisviel_add_record_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(database_record, data);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct irisviel_add_record_result {
        GX_BEGIN_FIELDS(irisviel_add_record_result);
        GX_FIELD(parser_result_status, status);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    using irisviel_update_record_param   = irisviel_add_record_param;
    using irisviel_update_record_result  = irisviel_add_record_result;
    using irisviel_update_records_param  = irisviel_add_records_param;
    using irisviel_update_records_result = irisviel_add_records_result;

    struct irisviel : protocol_object {
        struct load_databases : parser_inout<irisviel_load_databases_param, irisviel_load_databases_result> {};
        struct search : parser_inout<irisviel_search_param, irisviel_search_result> {};
        struct contains_key : parser_inout<irisviel_contains_key_param, irisviel_contains_key_result> {};
        struct add_records : parser_inout<irisviel_add_records_param, irisviel_add_records_result> {};
        struct remove_records : parser_inout<irisviel_remove_records_param, irisviel_remove_records_result> {};
        struct update_records : parser_inout<irisviel_update_records_param, irisviel_update_records_result> {};
        struct add_record : parser_inout<irisviel_add_record_param, irisviel_add_record_result> {};
        struct remove_record : parser_inout<irisviel_remove_record_param, irisviel_remove_record_result> {};
        struct update_record : parser_inout<irisviel_update_record_param, irisviel_update_record_result> {};
        struct remove_all : parser_inout<irisviel_remove_all_param, irisviel_remove_all_result> {};
    };
} // namespace glasssix::face
