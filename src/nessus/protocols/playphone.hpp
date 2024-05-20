#pragma once

#include "../../../include/g6/info_playphone.hpp"
#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct playphone_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct playphone_detect_param {
        struct confidence_params {
            std::optional<float> head_conf_thres{};
            std::optional<float> head_nms_thres{};
            std::optional<float> phone_conf_thres{};
            std::optional<float> phone_nms_thres{};
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
        enum class json_serialization { snake_case };
    };
    struct playphone_detect_result {
        parser_result_status status{};
        playphone_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct playphone : protocol_object {
        struct detect : parser_inout<playphone_detect_param, playphone_detect_result> {};
    };
} // namespace glasssix
