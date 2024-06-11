#pragma once
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>


namespace glasssix {
    struct configure_directory {
        GX_BEGIN_FIELDS(configure_directory);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(abi::string, directory);
        GX_FIELD(abi::string, license_directory);
        GX_FIELD(abi::string, empower_serial_number);
        GX_FIELD(int, thread_pool_num);
        GX_FIELD(abi::string, dump_img_directory);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    struct detect_config {
        GX_BEGIN_FIELDS(detect_config);
        GX_FIELD(int, device);
        GX_FIELD(int, model_type);
        GX_FIELD(int, algo_type);
        GX_FIELD(int, library_algo_type);
        GX_FIELD(int, min_size);
        GX_FIELD(int, min_face);
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
    struct attributes_config {
        GX_BEGIN_FIELDS(attributes_config);
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
        GX_FIELD(abi::string, working_directory);
        GX_FIELD(int, dimension);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct climb_config {
        GX_BEGIN_FIELDS(climb_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, little_target_conf_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct crowd_config {
        GX_BEGIN_FIELDS(crowd_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, area_threshold);
        GX_FIELD(int, max_area_list);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct crossing_config {
        GX_BEGIN_FIELDS(crossing_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct batterypilferers_config {
        GX_BEGIN_FIELDS(batterypilferers_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(int, batch);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct fighting_config {
        GX_BEGIN_FIELDS(fighting_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(int, batch);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct flame_config {
        GX_BEGIN_FIELDS(flame_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_mask_config {
        GX_BEGIN_FIELDS(pump_mask_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_weld_config {
        GX_BEGIN_FIELDS(pump_weld_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, wmachine_conf_thres);
        GX_FIELD(float, wlight_conf_thres);
        GX_FIELD(int, batch);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_hoisting_config {
        GX_BEGIN_FIELDS(pump_hoisting_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, move_threshold);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_vesthelmet_config {
        GX_BEGIN_FIELDS(pump_vesthelmet_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, posture_conf_thres);
        GX_FIELD(float, head_min_h_thres);
        GX_FIELD(float, head_min_w_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pumptop_helmet_config {
        GX_BEGIN_FIELDS(pumptop_helmet_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, pump_conf_thres);
        GX_FIELD(float, people_conf_thres);
        GX_FIELD(float, head_conf_thres);
        GX_FIELD(float, head_score_conf_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_gate_status_config {
        GX_BEGIN_FIELDS(pump_gate_status_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_light_config {
        GX_BEGIN_FIELDS(pump_light_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_work_status_config {
        GX_BEGIN_FIELDS(pump_work_status_config);
        GX_FIELD(int, format);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct smog_config {
        GX_BEGIN_FIELDS(smog_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct helmet_config {
        GX_BEGIN_FIELDS(helmet_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(int, min_size);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct refvest_config {
        GX_BEGIN_FIELDS(refvest_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, posture_conf_thres);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct sleep_config {
        GX_BEGIN_FIELDS(sleep_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(int, frame_count_thres);
        // GX_FIELD(int, device_id);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct smoke_config {
        GX_BEGIN_FIELDS(smoke_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, little_target_conf_thres);
        GX_FIELD(float, smoke_conf_thres);
        GX_FIELD(float, posture_conf_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct tumble_config {
        GX_BEGIN_FIELDS(tumble_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct vehicle_config {
        GX_BEGIN_FIELDS(vehicle_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pump_pumptop_person_config {
        GX_BEGIN_FIELDS(pump_pumptop_person_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, person_area_ratio_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct wander_config {
        GX_BEGIN_FIELDS(wander_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(int, feature_table_size);
        GX_FIELD(double, feature_match_threshold);
        GX_FIELD(double, person_conf);
        GX_FIELD(std::int64_t, interval);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct wander_limit_config {
        GX_BEGIN_FIELDS(wander_limit_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(int, feature_table_size);
        GX_FIELD(double, feature_match_threshold);
        GX_FIELD(double, person_conf);
        GX_FIELD(std::int64_t, interval);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct leavepost_config {
        GX_BEGIN_FIELDS(leavepost_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct playphone_config {
        GX_BEGIN_FIELDS(playphone_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, posture_conf_thres);
        GX_FIELD(float, head_conf_thres);
        GX_FIELD(float, head_nms_thres);
        GX_FIELD(float, phone_conf_thres);
        GX_FIELD(float, phone_nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct onphone_config {
        GX_BEGIN_FIELDS(onphone_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, head_conf_thres);
        GX_FIELD(float, posture_conf_thres);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, phone_distance_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct workcloth_config {

        struct confidence_color_hsv_cfg {
            GX_BEGIN_FIELDS(confidence_color_hsv_cfg);
            GX_FIELD(std::vector<int>, black);
            GX_FIELD(std::vector<int>, grey);
            GX_FIELD(std::vector<int>, white);
            GX_FIELD(std::vector<int>, red);
            GX_FIELD(std::vector<int>, orange);
            GX_FIELD(std::vector<int>, yellow);
            GX_FIELD(std::vector<int>, green);
            GX_FIELD(std::vector<int>, cyan);
            GX_FIELD(std::vector<int>, blue);
            GX_FIELD(std::vector<int>, purple);
            GX_END_FIELDS;

            GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
        };
        GX_BEGIN_FIELDS(workcloth_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_FIELD(float, posture_conf_thres);
        GX_FIELD(std::vector<confidence_color_hsv_cfg>, color_hsv_list);

        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pedestrian_config {
        GX_BEGIN_FIELDS(pedestrian_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
        GX_END_FIELDS;
        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };
    struct pedestrian_min_config {
        GX_BEGIN_FIELDS(pedestrian_min_config);
        GX_FIELD(int, device);
        GX_FIELD(int, format);
        GX_FIELD(float, conf_thres);
        GX_FIELD(float, nms_thres);
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
        attributes_config _attributes_config;
        action_live_config _action_live_config;
        feature_config _feature_config;
        face_user_config _face_user_config;
        climb_config _climb_config;
        crowd_config _crowd_config;
        crossing_config _crossing_config;
        batterypilferers_config _batterypilferers_config;
        fighting_config _fighting_config;
        flame_config _flame_config;
        pump_mask_config _pump_mask_config;
        pump_weld_config _pump_weld_config;
        pump_hoisting_config _pump_hoisting_config;
        pump_vesthelmet_config _pump_vesthelmet_config;
        pumptop_helmet_config _pumptop_helmet_config;
        pump_gate_status_config _pump_gate_status_config;
        pump_light_config _pump_light_config;
        pump_work_status_config _pump_work_status_config;
        smog_config _smog_config;
        helmet_config _helmet_config;
        refvest_config _refvest_config;
        sleep_config _sleep_config;
        smoke_config _smoke_config;
        tumble_config _tumble_config;
        vehicle_config _vehicle_config;
        wander_config _wander_config;
        wander_limit_config _wander_limit_config;
        pump_pumptop_person_config _pump_pumptop_person_config;
        leavepost_config _leavepost_config;
        playphone_config _playphone_config;
        onphone_config _onphone_config;
        workcloth_config _workcloth_config;
        pedestrian_config _pedestrian_config;
        pedestrian_min_config _pedestrian_min_config;
        void set_configure_directory(abi::string& path);
        void set_detect(const abi::string& path);
        void set_track(const abi::string& path);
        void set_blur(const abi::string& path);
        void set_attributes(const abi::string& path);
        void set_action_live(const abi::string& path);
        void set_feature(const abi::string& path);
        void set_face_user(const abi::string& path);
        void set_climb(const abi::string& path);
        void set_crowd(const abi::string& path);
        void set_crossing(const abi::string& path);
        void set_batterypilferers(const abi::string& path);
        void set_fighting(const abi::string& path);
        void set_flame(const abi::string& path);
        void set_pump_mask(const abi::string& path);
        void set_pump_weld(const abi::string& path);
        void set_pump_hoisting(const abi::string& path);
        void set_pump_vesthelmet(const abi::string& path);
        void set_pumptop_helmet(const abi::string& path);
        void set_pump_gate_status(const abi::string& path);
        void set_pump_light(const abi::string& path);
        void set_pump_work_status(const abi::string& path);
        void set_smog(const abi::string& path);
        void set_helmet(const abi::string& path);
        void set_refvest(const abi::string& path);
        void set_sleep(const abi::string& path);
        void set_smoke(const abi::string& path);
        void set_tumble(const abi::string& path);
        void set_vehicle(const abi::string& path);
        void set_wander(const abi::string& path);
        void set_wander_limit(const abi::string& path);
        void set_pump_pumptop_person(const abi::string& path);
        void set_leavepost(const abi::string& path);
        void set_playphone(const abi::string& path);
        void set_onphone(const abi::string& path);
        void set_workcloth(const abi::string& path);
        void set_pedestrian(const abi::string& path);
        void set_pedestrian_min(const abi::string& path);

        bool configure_directory_is_load = false;
        bool detect_is_load              = false;
        bool track_is_load               = false;
        bool blur_is_load                = false;
        bool attributes_is_load          = false;
        bool action_live_is_load         = false;
        bool feature_is_load             = false;
        bool face_user_is_load           = false;
        bool climb_is_load               = false;
        bool crowd_is_load               = false;
        bool crossing_is_load            = false;
        bool batterypilferers_is_load    = false;
        bool fighting_is_load            = false;
        bool flame_is_load               = false;
        bool pump_mask_is_load           = false;
        bool pump_weld_is_load           = false;
        bool pump_hoisting_is_load       = false;
        bool pump_pumptop_person_is_load = false;
        bool pump_vesthelmet_is_load     = false;
        bool pumptop_helmet_is_load      = false;
        bool pump_gate_status_is_load    = false;
        bool pump_light_is_load          = false;
        bool pump_work_status_is_load    = false;
        bool smog_is_load                = false;
        bool helmet_is_load              = false;
        bool refvest_is_load             = false;
        bool sleep_is_load               = false;
        bool smoke_is_load               = false;
        bool tumble_is_load              = false;
        bool vehicle_is_load             = false;
        bool wander_is_load              = false;
        bool wander_limit_is_load        = false;
        bool leavepost_is_load           = false;
        bool playphone_is_load           = false;
        bool onphone_is_load             = false;
        bool workcloth_is_load           = false;
        bool pedestrian_is_load          = false;
        bool pedestrian_min_is_load      = false;

    private:
        glasssix::json read_json_file(const abi::string& path);
    };
} // namespace glasssix