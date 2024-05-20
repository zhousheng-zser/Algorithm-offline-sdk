#pragma once

#include "../../../include/g6/info_pedestrian.hpp"
#include "../../../include/g6/info_wander.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct wander_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct wander_detect_param {
        struct confidence_params {
            std::int64_t current_time{};
            std::int32_t feature_table_size{};
            double feature_match_threshold{};
            std::int32_t device_id{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t roi_x{};
        std::int32_t roi_y{};
        std::int32_t roi_width{};
        std::int32_t roi_height{};
        abi::vector<pedestrian_info::boxes> person_list{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct wander_remove_library_param {
        std::string instance_guid{};
        std::int32_t id{};
        enum class json_serialization { snake_case };
    };
    struct wander_remove_person_by_index_param {
        std::string instance_guid{};
        std::int32_t id{};
        std::int32_t device_id{};
        enum class json_serialization { snake_case };
    };
    struct wander_detect_result {
        parser_result_status status{};
        wander_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct wander_remove_library_result {
        parser_result_status status{};
        abi::string delete_info{};
        enum class json_serialization { snake_case };
    };
    using wander_remove_person_by_index_result = wander_remove_library_result;
    struct wander : protocol_object {
        struct detect : parser_inout<wander_detect_param, wander_detect_result> {};
        struct remove_library : parser_inout<wander_remove_library_param, wander_remove_library_result> {};
        struct remove_person_by_index
            : parser_inout<wander_remove_person_by_index_param, wander_remove_person_by_index_result> {};
    };
} // namespace glasssix
