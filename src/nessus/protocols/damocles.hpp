#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct damocles_new_param {
        std::int32_t device{};
        int model_type{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };

    struct damocles_spoofing_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        abi::vector<face_info> facerect_list{};
        enum class json_serialization { snake_case };
    };

    struct damocles_spoofing_detect_result {
        parser_result_status status{};
        abi::vector<spoofing_probability> spoofing_result{};
        enum class json_serialization { snake_case };
    };

    struct damocles_presentation_attack_detect_param {
        std::string instance_guid{};
        std::int32_t action_cmd{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        face_info facerect{};
        enum class json_serialization { snake_case };
    };

    struct damocles_presentation_attack_detect_result {
        parser_result_status status{};
        bool presentation_attack_result{};
        enum class json_serialization { snake_case };
    };

    struct damocles : protocol_object {
        struct spoofing_detect : parser_inout<damocles_spoofing_detect_param, damocles_spoofing_detect_result> {};
        struct presentation_attack_detect
            : parser_inout<damocles_presentation_attack_detect_param, damocles_presentation_attack_detect_result> {};
    };

} // namespace glasssix
