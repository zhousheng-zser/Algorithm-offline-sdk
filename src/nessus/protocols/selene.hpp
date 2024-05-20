#pragma once

#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct selene_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        std::int32_t model_type{};
        bool use_int8{};
        enum class json_serialization { snake_case };
    };

    struct selene_forward_param {
        std::string instance_guid{};
        abi::vector<std::string> aligned_images{};
        std::int32_t format{};
        enum class json_serialization { snake_case };
    };
    struct selene_forward_result {
        parser_result_status status{};
        abi::vector<feature_info> features{};
        enum class json_serialization { snake_case };
    };
    struct selene : protocol_object {
        struct forward : parser_inout<selene_forward_param, selene_forward_result> {};
    };
} // namespace glasssix
