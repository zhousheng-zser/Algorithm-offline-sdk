#include <info_pedestrian.hpp>
#include <info_wander.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../pedestrian/struct_reflection.hpp"

//配置文件
struct wander_config {
    int device;
    int format;
    int feature_table_size;
    float feature_match_threshold;
    float person_conf;
    int interval;
};
DEFINE_STRUCT_SCHEMA(wander_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(feature_table_size, "feature_table_size"), 
    DEFINE_STRUCT_FIELD(feature_match_threshold, "feature_match_threshold"), 
    DEFINE_STRUCT_FIELD(person_conf, "person_conf"),
    DEFINE_STRUCT_FIELD(interval, "interval")
);

using wander_limit_config   = wander_config;

DEFINE_STRUCT_SCHEMA(wander_info, 
    DEFINE_STRUCT_FIELD(person_info, "person_info")
    );

  //徘徊信息
DEFINE_STRUCT_SCHEMA(wander_info::boxes, 
    DEFINE_STRUCT_FIELD(cosine_similarity, "cosine_similarity"),
    DEFINE_STRUCT_FIELD(id, "id"), 
    DEFINE_STRUCT_FIELD(last_show_time, "last_show_time"), 
    DEFINE_STRUCT_FIELD(first_show_time, "first_show_time"), 
    DEFINE_STRUCT_FIELD(detection_number, "detection_number"), 
    DEFINE_STRUCT_FIELD(score, "score"), 
    DEFINE_STRUCT_FIELD(x1, "x1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(y2, "y2")
);

struct wander_detect_info_result {
    wander_info detect_info;
};

DEFINE_STRUCT_SCHEMA(wander_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct wander_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(wander_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct wander_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<pedestrian_info::boxes> pedestrian_info_list;
            long long current_time;
            int feature_table_size;
            float feature_match_threshold;
            int device_id;
        };
        dyparams_params dyparams;
    };

    struct basic_params {
        int height;
        int width;
    };
    optional_params algo_params;
    basic_params data_params;
};

  //检测入参
DEFINE_STRUCT_SCHEMA(wander_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(wander_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(wander_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(pedestrian_info_list, "pedestrian_info_list"),
    DEFINE_STRUCT_FIELD(current_time, "current_time"),
    DEFINE_STRUCT_FIELD(feature_table_size, "feature_table_size"),
    DEFINE_STRUCT_FIELD(feature_match_threshold, "feature_match_threshold"),
    DEFINE_STRUCT_FIELD(device_id, "device_id"));

DEFINE_STRUCT_SCHEMA(wander_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));