#pragma once

#include "../../../include/g6/info_fighting.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct fighting_new_param {
        GX_BEGIN_FIELDS(fighting_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_FIELD(std::int32_t, batch);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct fighting_detect_param {
        GX_BEGIN_FIELDS(fighting_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct fighting_detect_result {
        GX_BEGIN_FIELDS(fighting_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(fighting_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct fighting : protocol_object {
        struct detect : parser_inout<fighting_detect_param, fighting_detect_result> {};
    };
} // namespace glasssix
