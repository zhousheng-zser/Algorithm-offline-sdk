#pragma once

#include "../../../include/g6/info_pump_vesthelmet.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct pump_vesthelmet_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pump_vesthelmet_detect_param {
        struct confidence_params {
            std::optional<float> posture_conf_thres{};
            std::optional<float> head_conf_thres{};
            std::optional<float> head_min_h_thres{};
            std::optional<float> head_min_w_thres{};
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
    struct pump_vesthelmet_detect_result {
        parser_result_status status{};
        pump_vesthelmet_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct pump_vesthelmet : protocol_object {
        struct detect : parser_inout<pump_vesthelmet_detect_param, pump_vesthelmet_detect_result> {};
    };
} // namespace glasssix
