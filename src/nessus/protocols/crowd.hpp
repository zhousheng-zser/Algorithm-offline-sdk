#pragma once

#include "../../../include/g6/info_crowd.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct crowd_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct crowd_detect_param {
        struct confidence_params {
            std::optional<float> area_threshold{};
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
        std::int32_t min_cluster_size{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };

    struct crowd_detect_result {
        parser_result_status status{};
        crowd_info detect_info{};
        enum class json_serialization { snake_case };
    };

    struct crowd : protocol_object {
        struct detect : parser_inout<crowd_detect_param, crowd_detect_result> {};
    };
} // namespace glasssix
