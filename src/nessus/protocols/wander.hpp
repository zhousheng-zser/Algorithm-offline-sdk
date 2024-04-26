#pragma once

#include "../../../include/g6/info_wander.hpp"
#include "../../../include/g6/info_pedestrian.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct wander_new_param {
        GX_BEGIN_FIELDS(wander_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(abi::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct wander_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::int64_t, current_time);
            GX_FIELD(std::int32_t, feature_table_size);
            GX_FIELD(double, feature_match_threshold);
            GX_FIELD(std::int32_t, device_id);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(wander_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(std::int32_t, roi_x);
        GX_FIELD(std::int32_t, roi_y);
        GX_FIELD(std::int32_t, roi_width);
        GX_FIELD(std::int32_t, roi_height);
        GX_FIELD(abi::vector<pedestrian_info::boxes>, person_list);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct wander_remove_library_param {
        GX_BEGIN_FIELDS(wander_remove_library_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, id);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct wander_remove_person_by_index_param {
        GX_BEGIN_FIELDS(wander_remove_person_by_index_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, id);
        GX_FIELD(std::int32_t, device_id);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct wander_detect_result {
        GX_BEGIN_FIELDS(wander_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(wander_info, detect_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct wander_remove_library_result {
        GX_BEGIN_FIELDS(wander_remove_library_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::string, delete_info);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    using wander_remove_person_by_index_result = wander_remove_library_result;

    struct wander : protocol_object {
        struct detect : parser_inout<wander_detect_param, wander_detect_result> {};
        struct remove_library : parser_inout<wander_remove_library_param, wander_remove_library_result> {};
        struct remove_person_by_index
            : parser_inout<wander_remove_person_by_index_param, wander_remove_person_by_index_result> {};
    };
} // namespace glasssix
