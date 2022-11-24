#pragma once
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>


namespace glasssix::face {
    struct detect_config {
        GX_BEGIN_FIELDS(detect_config);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(int, device);
        GX_FIELD(int, min_size);
        GX_FIELD(float, threshold);
        GX_FIELD(int, format);
        GX_FIELD(bool, do_attributing);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct track_config {
        GX_BEGIN_FIELDS(track_config);
        GX_FIELD(int, detect_intv_before_track);
        GX_FIELD(int, detect_intv_during_track);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct blur_config {
        GX_BEGIN_FIELDS(blur_config);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct action_live_config {
        GX_BEGIN_FIELDS(action_live_config);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(int, device);
        GX_FIELD(bool, use_int8);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct feature_config {
        GX_BEGIN_FIELDS(feature_config);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(int, device);
        GX_FIELD(bool, use_int8);
        GX_FIELD(int, format);
        GX_FIELD(int, model_type);
        GX_FIELD(int, dimension);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct face_user_config {
        GX_BEGIN_FIELDS(face_user_config);
        GX_FIELD(abi::string, working_directory);
        GX_FIELD(abi::string, working_directory_mask);
        GX_FIELD(int, dimension);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    class config {
    public:
        config();
        detect_config _detect_config;
        track_config _track_config;
        blur_config _blur_config;
        action_live_config _action_live_config;
        feature_config _feature_config;
        face_user_config _face_user_config;

    private:
        glasssix::json read_json_file(abi::string path);
        void set_detect();
        void set_track();
        void set_blur();
        void set_action_live();
        void set_feature();
        void set_face_user();
    };
} // namespace glasssix::face