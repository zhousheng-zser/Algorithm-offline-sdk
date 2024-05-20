#pragma once

#include "../../../include/g6/info_face.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace glasssix {
    struct longinus_new_param {
        std::int32_t device{};
        std::int32_t model_type{};
        std::int32_t algo_type{};
        abi::string models_directory{};
        enum class json_serialization { snake_case };
    };
    struct longinus_detect_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        std::int32_t min_size{};
        float threshold{};
        bool do_attributing{};
        enum class json_serialization { snake_case };
    };
    struct longinus_detect_result {
        parser_result_status status{};
        abi::vector<face_info> facerectwithfaceinfo_list{};
        enum class json_serialization { snake_case };
    };
    struct longinus_trace_param {
        std::string instance_guid{};
        std::int32_t format{};
        std::int32_t height{};
        std::int32_t width{};
        face_info face{};
        enum class json_serialization { snake_case };
    };
    struct longinus_trace_result {
        parser_result_status status{};
        bool trace_success{};
        std::optional<face_info> facerectwithfaceinfo{};
        enum class json_serialization { snake_case };
    };
    struct longinus : protocol_object {
        struct detect : parser_inout<longinus_detect_param, longinus_detect_result> {};
        struct trace : parser_inout<longinus_trace_param, longinus_trace_result> {};
    };
} // namespace glasssix
