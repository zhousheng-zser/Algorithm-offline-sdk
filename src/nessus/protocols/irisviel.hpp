#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/abi/string.hpp>
namespace glasssix {
    struct database_record {
        abi::vector<float> feature{};
        abi::string key{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_new_param {
        std::int32_t dimension{};
        abi::string working_directory{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_load_databases_param {
        std::string instance_guid{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_load_databases_result {
        parser_result_status status{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_search_nf_param {
        std::string instance_guid{};
        abi::vector<float> feature{};
        std::optional<std::int32_t> top{};
        std::optional<float> min_similarity{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_search_nf_result {
        parser_result_status status{};
        abi::vector<faces_search_info::database_result> result{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_search_result {
        parser_result_status status{};
        struct database_result {
            struct faces_search_data {
                abi::vector<float> feature{}; // 人脸特征向量
                abi::string key{}; // 人脸键值
                enum class json_serialization { snake_case };
            };
            database_result::faces_search_data data{}; // 人脸搜索数据
            float similarity{}; // 相似度
            enum class json_serialization { snake_case };
        };
        abi::vector<irisviel_search_result::database_result> result{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_contains_key_param {
        std::string instance_guid{};
        abi::string key{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_contains_key_result {
        parser_result_status status{};
        bool result{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_record_count_result {
        parser_result_status status{};
        std::uint64_t result{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_remove_all_param {
        std::string instance_guid{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_remove_all_result {
        parser_result_status status{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_remove_records_param {
        abi::string instance_guid{};
        abi::vector<abi::string> keys{};
        enum class json_serialization { snake_case };
    };

    struct irisviel_remove_record_param {
        std::string instance_guid{};
        abi::string key{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_add_records_param {
        std::string instance_guid{};
        abi::vector<database_record> data{};
        enum class json_serialization { snake_case };
    };
    struct faces_user_add {
        bool success{};
        abi::string reason{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_add_records_result {
        parser_result_status status{};
        abi::vector<faces_user_add> result{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_add_record_param {
        std::string instance_guid{};
        database_record data{};
        enum class json_serialization { snake_case };
    };
    struct irisviel_add_record_result {
        parser_result_status status{};
        enum class json_serialization { snake_case };
    };
    using irisviel_update_record_param   = irisviel_add_record_param;
    using irisviel_update_record_result  = irisviel_add_record_result;
    using irisviel_update_records_param  = irisviel_add_records_param;
    using irisviel_update_records_result = irisviel_add_records_result;
    using irisviel_remove_record_result  = irisviel_add_record_result;
    using irisviel_remove_records_result = irisviel_add_records_result;
    using irisviel_clear_param           = irisviel_remove_all_param;
    using irisviel_clear_result          = irisviel_remove_all_result;
    using irisviel_record_count_param    = irisviel_remove_all_param;
    using irisviel_search_param          = irisviel_search_nf_param;
    struct irisviel : protocol_object {
        struct load_databases : parser_inout<irisviel_load_databases_param, irisviel_load_databases_result> {};
        struct search : parser_inout<irisviel_search_param, irisviel_search_result> {};
        struct search_nf : parser_inout<irisviel_search_nf_param, irisviel_search_nf_result> {};
        struct contains_key : parser_inout<irisviel_contains_key_param, irisviel_contains_key_result> {};
        struct record_count : parser_inout<irisviel_record_count_param, irisviel_record_count_result> {};
        struct add_records : parser_inout<irisviel_add_records_param, irisviel_add_records_result> {};
        struct remove_records : parser_inout<irisviel_remove_records_param, irisviel_remove_records_result> {};
        struct update_records : parser_inout<irisviel_update_records_param, irisviel_update_records_result> {};
        struct add_record : parser_inout<irisviel_add_record_param, irisviel_add_record_result> {};
        struct remove_record : parser_inout<irisviel_remove_record_param, irisviel_remove_record_result> {};
        struct update_record : parser_inout<irisviel_update_record_param, irisviel_update_record_result> {};
        struct remove_all : parser_inout<irisviel_remove_all_param, irisviel_remove_all_result> {};
        struct clear : parser_inout<irisviel_clear_param, irisviel_clear_result> {};
    };
} // namespace glasssix
