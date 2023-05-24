#pragma once

#include "../common_protocols.hpp"
#include "../protocol_object.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct selene_new_param {
        GX_BEGIN_FIELDS(selene_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_FIELD(std::int32_t, model_type);
        GX_FIELD(bool, use_int8);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct selene_forward_param {
        GX_BEGIN_FIELDS(selene_forward_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(abi::vector<std::string>, aligned_images);
        GX_FIELD(std::int32_t, format);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct selene_forward_result {
        GX_BEGIN_FIELDS(selene_forward_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::vector<feature_info>, features);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };


    struct selene : protocol_object {
        struct forward : parser_inout<selene_forward_param, selene_forward_result> {};
    };
} // namespace glasssix::face
