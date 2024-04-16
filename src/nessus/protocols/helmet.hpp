#pragma once

#include "../../../include/g6/info_helmet.hpp"
#include "../../../include/g6/info_head.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct helmet_new_param {
        std::int32_t  device{};
        std::string  models_directory{};
        enum class json_serialization { snake_case };
    };

    struct helmet_detect_param {
        struct confidence_params {
            std::optional<float>  conf_thres{};
            std::optional<float>  nms_thres{};
            std::optional<std::int32_t>  min_size{};
            enum class json_serialization { snake_case };
        };
        std::string  instance_guid{};
        std::int32_t  format{};
        std::int32_t  height{};
        std::int32_t  width{};
        std::int32_t  roi_x{};
        std::int32_t  roi_y{};
        std::int32_t  roi_width{};
        std::int32_t  roi_height{};
        abi::vector<head_info>  head_info_list{};
        confidence_params  params{};
        enum class json_serialization { snake_case };
    };

    struct helmet_detect_result {
        parser_result_status  status{};
        helmet_info  detect_info{};
        enum class json_serialization { snake_case };
    };
    struct helmet : protocol_object {
        struct detect : parser_inout<helmet_detect_param, helmet_detect_result> {};
    };
} // namespace glasssix
