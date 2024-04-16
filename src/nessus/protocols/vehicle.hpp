#pragma once

#include "../../../include/g6/info_vehicle.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct vehicle_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };

    struct vehicle_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
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

    struct vehicle_detect_result {
        parser_result_status status{};
        vehicle_info detect_info{};
        enum class json_serialization { snake_case };
    };

    struct vehicle : protocol_object {
        struct detect : parser_inout<vehicle_detect_param, vehicle_detect_result> {};
    };
} // namespace glasssix
