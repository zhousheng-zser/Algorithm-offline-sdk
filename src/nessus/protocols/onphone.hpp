#pragma once

#include "../../../include/g6/info_head.hpp"
#include "../../../include/g6/info_onphone.hpp"
#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct onphone_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct onphone_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::optional<float> phone_distance_thres{};
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
        abi::vector<head_info> head_info_list{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct onphone_detect2_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::optional<float> phone_distance_thres{};
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
    struct onphone_detect_result {
        parser_result_status status{};
        onphone_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct onphone : protocol_object {
        struct detect : parser_inout<onphone_detect_param, onphone_detect_result> {};
        struct detect2 : parser_inout<onphone_detect2_param, onphone_detect_result> {};
    };
} // namespace glasssix
