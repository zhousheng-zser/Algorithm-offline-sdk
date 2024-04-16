#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

namespace glasssix {
    struct face_attributes_new_param {
        std::int32_t  device{};
        std::string  models_directory{};
        enum class json_serialization { snake_case };
    };

    struct face_attributes_detect_param {
        std::string  instance_guid{};
        std::int32_t  format{};
        std::int32_t  height{};
        std::int32_t  width{};
        abi::vector<face_info>  facerect_list{};
        enum class json_serialization { snake_case };
    };

    struct face_attributes_detect_result {
        parser_result_status  status{};
        abi::vector<attributes>  face_attributes{};
        enum class json_serialization { snake_case };
    };

    struct face_attributes : protocol_object {
        struct detect : parser_inout<face_attributes_detect_param, face_attributes_detect_result> {};
    };
} // namespace glasssix
