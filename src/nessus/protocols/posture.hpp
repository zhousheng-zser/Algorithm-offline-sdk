#pragma once

#include "../../../include/g6/info_posture.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct posture_new_param {
        std::int32_t device{};
        std::string models_directory{};
        std::int32_t model_type{};
        enum class json_serialization { snake_case };
    };
    struct posture_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t roi_x{};
        std::int32_t roi_y{};
        std::int32_t roi_width{};
        std::int32_t roi_height{};
        enum class json_serialization { snake_case };
    };
    struct posture_detect_result {
        parser_result_status status{};
        abi::vector<posture_info> info_list{};
        enum class json_serialization { snake_case };
    };
    struct posture : protocol_object {
        struct detect : parser_inout<posture_detect_param, posture_detect_result> {};
    };
} // namespace glasssix
