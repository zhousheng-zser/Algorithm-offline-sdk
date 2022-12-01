#pragma once

#include "../common_protocols.hpp"
#include "../protocol_object.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix::face {
    struct valklyrs_new_param {
        GX_BEGIN_FIELDS(valklyrs_new_param);
        GX_FIELD(std::int32_t, device);
        GX_FIELD(std::string, models_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct valklyrs_detect_param {
        GX_BEGIN_FIELDS(valklyrs_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct valklyrs_detect_result {
        struct coordinate_info {
            GX_BEGIN_FIELDS(coordinate_info);
            GX_FIELD(std::int32_t, x);
            GX_FIELD(std::int32_t, y);
            GX_FIELD(std::int32_t, width);
            GX_FIELD(std::int32_t, height);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct attribute_info {
            GX_BEGIN_FIELDS(attribute_info);
            GX_FIELD(std::string, gender);
            GX_FIELD(std::string, age);
            GX_FIELD(std::string, ori);
            GX_FIELD(std::string, hat);
            GX_FIELD(std::string, glass);
            GX_FIELD(std::string, handbag);
            GX_FIELD(std::string, shoulderbag);
            GX_FIELD(std::string, backpack);
            GX_FIELD(std::string, sleeve);
            GX_FIELD(std::string, texture);
            GX_FIELD(std::string, lower_type);
            GX_FIELD(std::string, color);
            GX_FIELD(std::string, orientation);
            GX_FIELD(std::string, car_type);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct coordinate_attribute_pair {
            GX_BEGIN_FIELDS(coordinate_attribute_pair);
            GX_FIELD(coordinate_info, coordinates);
            GX_FIELD(attribute_info, attributes);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        struct result_info {
            GX_BEGIN_FIELDS(result_info);
            GX_FIELD(std::vector<coordinate_attribute_pair>, person_list);
            GX_FIELD(std::vector<coordinate_attribute_pair>, vehicle_list);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(valklyrs_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(result_info, results);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct valklyrs : protocol_object {
        struct detect : parser_inout<valklyrs_detect_param, valklyrs_detect_result> {};
    };
} // namespace glasssix::face
