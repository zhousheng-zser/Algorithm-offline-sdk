#pragma once

#include "../../../include/g6/info_pump_mask.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct pump_mask_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pump_mask_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_mask_detect_result {
        parser_result_status status{};
        pump_mask_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct pump_mask : protocol_object {
        struct detect : parser_inout<pump_mask_detect_param, pump_mask_detect_result> {};
    };
} // namespace glasssix
