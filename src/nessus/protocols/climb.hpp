#pragma once

#include "../../../include/g6/info_climb.hpp"
#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct climb_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };

    struct climb_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::optional<float> little_target_conf_thres{};
            std::int32_t x1{};
            std::int32_t y1{};
            std::int32_t x2{};
            std::int32_t y2{};
            std::int32_t x3{};
            std::int32_t y3{};
            std::int32_t x4{};
            std::int32_t y4{};
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

    struct climb_detect_result {
        parser_result_status status{};
        climb_info detect_info{};
        enum class json_serialization { snake_case };
    };

    struct climb : protocol_object {
        struct detect : parser_inout<climb_detect_param, climb_detect_result> {};
    };
} // namespace glasssix
