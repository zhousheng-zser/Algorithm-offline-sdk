#pragma once
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>


namespace glasssix {
    struct configure_directory {
        GX_BEGIN_FIELDS(configure_directory);
        GX_FIELD(std::string, models_directory);
        GX_FIELD(std::string, directory);
        GX_FIELD(std::string, license_directory);
        GX_FIELD(int, thread_pool_num);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct detect_config {
        GX_BEGIN_FIELDS(detect_config);
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
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct action_live_config {
        GX_BEGIN_FIELDS(action_live_config);
        GX_FIELD(int, device);
        GX_FIELD(int, model_type);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct feature_config {
        GX_BEGIN_FIELDS(feature_config);
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
        GX_FIELD(std::string, working_directory);
        GX_FIELD(int, dimension);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct flame_config {
        GX_BEGIN_FIELDS(flame_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, iou_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct helmet_config {
        GX_BEGIN_FIELDS(helmet_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, iou_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct refvest_config {
        GX_BEGIN_FIELDS(refvest_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(int, channels);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, iou_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };


    class config {
    public:
        config();
        config(const abi::string& path);
        abi::string _path;
        nlohmann::json protocols_list;
        configure_directory _configure_directory;
        detect_config _detect_config;
        track_config _track_config;
        blur_config _blur_config;
        action_live_config _action_live_config;
        feature_config _feature_config;
        face_user_config _face_user_config;
        flame_config _flame_config;
        helmet_config _helmet_config;
        refvest_config _refvest_config;
        void set_configure_directory(const abi::string& path);
        void set_detect(const abi::string& path);
        void set_track(const abi::string& path);
        void set_blur(const abi::string& path);
        void set_action_live(const abi::string& path);
        void set_feature(const abi::string& path);
        void set_face_user(const abi::string& path);
        void set_flame(const abi::string& path);
        void set_helmet(const abi::string& path);
        void set_refvest(const abi::string& path);

    private:
        glasssix::json read_json_file(const abi::string& path);
    };
} // namespace glasssix