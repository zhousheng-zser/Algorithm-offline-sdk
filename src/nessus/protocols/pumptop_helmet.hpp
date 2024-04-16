#pragma once

#include "../../../include/g6/info_pumptop_helmet.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct pumptop_helmet_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pumptop_helmet_detect_param {
        struct confidence_params {
            std::optional<float> head_conf_thres{};
            std::optional<float> pump_conf_thres{};
            std::optional<float> people_conf_thres{};
            std::optional<float> head_score_conf_thres{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pumptop_helmet_detect_result {
        parser_result_status status{};
        pumptop_helmet_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct pumptop_helmet : protocol_object {
        struct detect : parser_inout<pumptop_helmet_detect_param, pumptop_helmet_detect_result> {};
    };
} // namespace glasssix
