#pragma once

#include "../../../include/g6/info_posture.hpp"
#include "../../../include/g6/info_workcloth.hpp"
#include "../../config.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct workcloth_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct workcloth_detect_param {
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
        abi::vector<posture_info> posture_info_list{};
        confidence_params params{};
        workcloth_config::confidence_color_hsv_cfg color_hsv_cfg{};
        enum class json_serialization { snake_case };
    };
    struct workcloth_detect_result {
        parser_result_status status{};
        workcloth_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct workcloth : protocol_object {
        struct detect : parser_inout<workcloth_detect_param, workcloth_detect_result> {};
    };
} // namespace glasssix
