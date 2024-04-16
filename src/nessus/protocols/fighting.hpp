#pragma once

#include "../../../include/g6/info_fighting.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct fighting_new_param {
        std::int32_t device{};
        std::string models_directory{};
        std::int32_t batch{};
        enum class json_serialization { snake_case };
    };

    struct fighting_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        enum class json_serialization { snake_case };
    };

    struct fighting_detect_result {
        parser_result_status status{};
        fighting_info detect_info{};
        enum class json_serialization { snake_case };
    };

    struct fighting : protocol_object {
        struct detect : parser_inout<fighting_detect_param, fighting_detect_result> {};
    };
} // namespace glasssix
