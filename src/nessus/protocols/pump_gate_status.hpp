#pragma once

#include "../../../include/g6/info_pump_gate_status.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct pump_gate_status_new_param {
        std::int32_t device{};
        enum class json_serialization { snake_case };
    };
    struct pump_gate_status_detect_param {
        struct confidence_params {
            std::optional<float> door_close_ratio{};
            std::optional<float> door_open_ratio{};
            std::optional<float> floor_ratio{};
            std::optional<float> device_id{};
            enum class json_serialization { snake_case };
        };
        struct confidence_roi {
            struct boxes {
                int x1{};
                int y1{};
                int x2{};
                int y2{};
                enum class json_serialization { snake_case };
            };
            boxes door{};
            boxes floor{};
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
        std::int32_t yellow_hsv_lower{};
        std::int32_t yellow_hsv_upper{};
        std::int32_t gray_hsv_lower{};
        std::int32_t gray_hsv_upper{};
        confidence_roi rois{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_gate_status_detect_result {
        parser_result_status status{};
        abi::string security_status{};
        enum class json_serialization { snake_case };
    };
    struct pump_gate_status : protocol_object {
        struct detect : parser_inout<pump_gate_status_detect_param, pump_gate_status_detect_result> {};
    };
} // namespace glasssix
