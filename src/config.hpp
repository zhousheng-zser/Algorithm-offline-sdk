#pragma once
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>

#include <g6/logger.hpp>


namespace glasssix {
    struct configure_directory {

        abi::string  models_directory{};
        abi::string  directory{};
        abi::string  license_directory{};
        abi::string  empower_serial_number{};
        int  thread_pool_num{};
        abi::string  dump_img_directory{};


        enum class json_serialization { snake_case };
    };

    struct detect_config {

        int  device{};
        int  model_type{};
        int  algo_type{};
        int  library_algo_type{};
        int  min_size{};
        int  min_face{};
        float  threshold{};
        int  format{};
        bool  do_attributing{};


        enum class json_serialization { snake_case };
    };
    struct track_config {

        int  detect_intv_before_track{};
        int  detect_intv_during_track{};

        enum class json_serialization { snake_case };
    };
    struct blur_config {

        int  device{};
        int  format{};

        enum class json_serialization { snake_case };
    };
    struct attributes_config {

        int  device{};
        int  format{};

        enum class json_serialization { snake_case };
    };
    struct action_live_config {

        int  device{};
        int  model_type{};
        int  format{};

        enum class json_serialization { snake_case };
    };
    struct feature_config {

        int  device{};
        bool  use_int8{};
        int  format{};
        int  model_type{};
        int  dimension{};

        enum class json_serialization { snake_case };
    };
    struct face_user_config {

        abi::string  working_directory{};
        int  dimension{};

        enum class json_serialization { snake_case };
    };
    struct climb_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        float  little_target_conf_thres{};

        enum class json_serialization { snake_case };
    };
    struct crowd_config {

        int  device{};
        int  format{};
        float  area_threshold{};

        enum class json_serialization { snake_case };
    };
    struct batterypilferers_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        int  batch{};

        enum class json_serialization { snake_case };
    };
    struct fighting_config {

        int  device{};
        int  format{};
        int  batch{};

        enum class json_serialization { snake_case };
    };
    struct flame_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct pump_mask_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct pump_weld_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        float  wmachine_conf_thres{};
        float  wlight_conf_thres{};
        int  batch{};

        enum class json_serialization { snake_case };
    };
    struct pump_hoisting_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        float  move_threshold{};

        enum class json_serialization { snake_case };
    };
    struct pump_vesthelmet_config {

        int  device{};
        int  format{};
        float  posture_conf_thres{};
        float  head_min_h_thres{};
        float  head_min_w_thres{};

        enum class json_serialization { snake_case };
    };
    struct pumptop_helmet_config {

        int  device{};
        int  format{};
        float  pump_conf_thres{};
        float  people_conf_thres{};
        float  head_conf_thres{};
        float  head_score_conf_thres{};

        enum class json_serialization { snake_case };
    };
    struct pump_gate_status_config {

        int  device{};
        int  format{};

        enum class json_serialization { snake_case };
    };
    struct pump_light_config {

        int  device{};
        int  format{};
        float  conf_thres{};

        enum class json_serialization { snake_case };
    };
    struct pump_work_status_config {

        int  format{};

        enum class json_serialization { snake_case };
    };
    struct smog_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct helmet_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        int  min_size{};

        enum class json_serialization { snake_case };
    };
    struct refvest_config {

        int  device{};
        int  format{};
        float posture_conf_thres{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct sleep_config {

        int  device{};
        int  format{};
        int  frame_count_thres{};
        // GX_FIELD(int, device_id);
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct smoke_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        float  little_target_conf_thres{};
        float smoke_conf_thres{};
        float posture_conf_thres{};

        enum class json_serialization { snake_case };
    };
    struct tumble_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct vehicle_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct pump_pumptop_person_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  person_area_ratio_thres{};

        enum class json_serialization { snake_case };
    };
    struct wander_config {

        int  device{};
        int  format{};
        int  feature_table_size{};
        double  feature_match_threshold{};
        double  person_conf{};
        std::int64_t  interval{};

        enum class json_serialization { snake_case };
    };
    struct wander_limit_config {

        int  device{};
        int  format{};
        int  feature_table_size{};
        double  feature_match_threshold{};
        double  person_conf{};
        std::int64_t  interval{};

        enum class json_serialization { snake_case };
    };
    struct leavepost_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct playphone_config {

        int  device{};
        int  format{};
        float posture_conf_thres{};
        float  head_conf_thres{};
        float  head_nms_thres{};
        float  phone_conf_thres{};
        float  phone_nms_thres{};

        enum class json_serialization { snake_case };
    };
    struct onphone_config {

        int  device{};
        int  format{};
        float head_conf_thres{};
        float posture_conf_thres{};
        float  conf_thres{};
        float  nms_thres{};
        float  phone_distance_thres{};

        enum class json_serialization { snake_case };
    };
    struct workcloth_config {

        struct confidence_color_hsv_cfg {

            std::vector<int>  black{};
            std::vector<int>  grey{};
            std::vector<int>  white{};
            std::vector<int>  red{};
            std::vector<int>  orange{};
            std::vector<int>  yellow{};
            std::vector<int>  green{};
            std::vector<int>  cyan{};
            std::vector<int>  blue{};
            std::vector<int>  purple{};


            enum class json_serialization { snake_case };
        };

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};
        float posture_conf_thres{};
        std::vector<confidence_color_hsv_cfg>  color_hsv_list{};


        enum class json_serialization { snake_case };
    };
    struct pedestrian_config {

        int  device{};
        int  format{};
        float  conf_thres{};
        float  nms_thres{};

        enum class json_serialization { snake_case };
    };

    class config {
    public:
        config();
        config(const abi::string& path);
        abi::string _path;
        json protocols_list;
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

    private:
        glasssix::json read_json_file(const abi::string& path);
    };
} // namespace glasssix