#pragma once

#include "../../../include/g6/info_head.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct head_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct head_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t roi_x{};
        std::int32_t roi_y{};
        std::int32_t roi_width{};
        std::int32_t roi_height{};
        enum class json_serialization { snake_case };
    };

    struct head_detect_result {
        parser_result_status status{};
        abi::vector<head_info> info_list{};
        enum class json_serialization { snake_case };
    };

    struct head : protocol_object {
        struct detect : parser_inout<head_detect_param, head_detect_result> {};
    };
} // namespace glasssix
