#pragma once

#include "../../../include/g6/info_sleep.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct sleep_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };

    struct sleep_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::int32_t frame_count_thres{};
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
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct sleep_detect_result {
        parser_result_status status{};
        sleep_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct sleep : protocol_object {
        struct detect : parser_inout<sleep_detect_param, sleep_detect_result> {};
    };
} // namespace glasssix
