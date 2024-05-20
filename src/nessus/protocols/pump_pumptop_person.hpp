#pragma once

#include "../../../include/g6/info_pedestrian.hpp"
#include "../../../include/g6/info_pump_pumptop_person.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct pump_pumptop_person_new_param {
        std::int32_t device{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct pump_pumptop_person_detect_param {
        struct confidence_params {
            std::optional<float> person_area_ratio_thres{};
            enum class json_serialization { snake_case };
        };
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        abi::vector<pedestrian_info::boxes> person_list{};
        confidence_params params{};
        enum class json_serialization { snake_case };
    };
    struct pump_pumptop_person_detect_result {
        parser_result_status status{};
        pump_pumptop_person_info detect_info{};
        enum class json_serialization { snake_case };
    };
    struct pump_pumptop_person : protocol_object {
        struct detect : parser_inout<pump_pumptop_person_detect_param, pump_pumptop_person_detect_result> {};
    };
} // namespace glasssix
