#pragma once

#include "../../../include/g6/gx_posture_api.hpp"
#include "../../../include/g6/info_smoke.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct smoke_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct smoke_detect_param {
        struct confidence_params {
            std::optional<float> conf_thres{};
            std::optional<float> nms_thres{};
            std::optional<float> little_target_conf_thres{};
            std::optional<float> smoke_conf_thres{};
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
    struct smoke_detect_result {
        parser_result_status status{};
        smoke_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct smoke : protocol_object {
        struct detect : parser_inout<smoke_detect_param, smoke_detect_result> {};
    };
} // namespace glasssix
