#pragma once

#include "../../../include/g6/info_pump_work_status.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct pump_work_status_new_param {
        std::int32_t device{};
        enum class json_serialization { snake_case };
    };
    struct pump_work_status_detect_param {
        struct confidence_params {
            std::int32_t big_paint_room{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        abi::vector<std::int32_t> mask_roi{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_work_status_detect_result {
        parser_result_status status{};
        abi::string security_status{};
        enum class json_serialization { snake_case };
    };
    struct pump_work_status : protocol_object {
        struct detect : parser_inout<pump_work_status_detect_param, pump_work_status_detect_result> {};
    };
} // namespace glasssix
