#pragma once

#include "../../../include/g6/info_pump_weld.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct pump_weld_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pump_weld_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::optional<float> wmachine_conf_thres{};
            std::optional<float> wlight_conf_thres{};
            std::optional<float> candidate_box_width{};
            std::optional<float> candidate_box_height{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t batch{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_weld_detect_result {
        parser_result_status status{};
        pump_weld_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct pump_weld : protocol_object {
        struct detect : parser_inout<pump_weld_detect_param, pump_weld_detect_result> {};
    };
} // namespace glasssix
