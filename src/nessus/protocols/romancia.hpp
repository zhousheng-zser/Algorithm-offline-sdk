#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>
namespace glasssix {
    struct romancia_new_param {
        std::int32_t device{};
        std::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct romancia_align_face_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        abi::vector<face_info> facerectwithfaceinfo_list{};
        enum class json_serialization { snake_case };
    };
    struct romancia_align_face_result {
        parser_result_status status{};
        abi::vector<std::string> aligned_images{};
        std::int32_t format{};
        enum class json_serialization { snake_case };
    };
    struct romancia_blur_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        abi::vector<face_info> facerect_list{};
        enum class json_serialization { snake_case };
    };
    struct romancia_blur_detect_result {
        parser_result_status status{};
        abi::vector<float> clarity{};
        enum class json_serialization { snake_case };
    };
    struct romancia : protocol_object {
        struct alignFace : parser_inout<romancia_align_face_param, romancia_align_face_result> {};
        struct blur_detect : parser_inout<romancia_blur_detect_param, romancia_blur_detect_result> {};
    };
} // namespace glasssix
