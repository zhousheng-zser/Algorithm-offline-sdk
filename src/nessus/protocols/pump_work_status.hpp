#pragma once

#include "../../../include/g6/info_pump_work_status.hpp"
#include "../common_protocols.hpp"

#include <cstdint>
#include <string>
#include <vector>

#include <g6/json_extensions.hpp>

namespace glasssix {
    struct pump_work_status_new_param {
        GX_BEGIN_FIELDS(pump_work_status_new_param);
        GX_END_FIELDS;
        GX_FIELD(std::int32_t, device);

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_work_status_detect_param {

        struct confidence_params {
            GX_BEGIN_FIELDS(confidence_params);
            GX_FIELD(std::int32_t, big_paint_room);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };

        GX_BEGIN_FIELDS(pump_work_status_detect_param);
        GX_FIELD(std::string, instance_guid);
        GX_FIELD(std::int32_t, format);
        GX_FIELD(std::int32_t, height);
        GX_FIELD(std::int32_t, width);
        GX_FIELD(abi::vector<std::int32_t>, mask_roi);
        GX_FIELD(confidence_params, params);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_work_status_detect_result {
        GX_BEGIN_FIELDS(pump_work_status_detect_result);
        GX_FIELD(parser_result_status, status);
        GX_FIELD(abi::string, security_status);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct pump_work_status : protocol_object {
        struct detect : parser_inout<pump_work_status_detect_param, pump_work_status_detect_result> {};
    };
} // namespace glasssix
