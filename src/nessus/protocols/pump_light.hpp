#pragma once

#include "../../../include/g6/info_pump_light.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct pump_light_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pump_light_detect_param {
        struct confidence_params {
            std::int32_t x1{};
            std::int32_t y1{};
            std::int32_t x2{};
            std::int32_t y2{};
            std::int32_t x3{};
            std::int32_t y3{};
            std::int32_t x4{};
            std::int32_t y4{};
            float conf_thres{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_light_detect_result {
        parser_result_status status{};
        pump_light_info detect_info{};
        enum class json_serialization { snake_case };
    };

    struct pump_light : protocol_object {
        struct detect : parser_inout<pump_light_detect_param, pump_light_detect_result> {};
    };
} // namespace glasssix
