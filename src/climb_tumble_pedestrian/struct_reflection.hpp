#include <info_pedestrian.hpp>
#include <info_climb_tumble_pedestrian.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../pedestrian/struct_reflection.hpp"

//配置文件
struct climb_tumble_pedestrian_config {
    int device;
    int format;
    float conf_thres;
    float nms_thres;
    float person_conf;
};
DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), 
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(person_conf, "person_conf"));


DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_info, 
    DEFINE_STRUCT_FIELD(persion_list, "persion_list"), 
    DEFINE_STRUCT_FIELD(climb_list, "climb_list"),
    DEFINE_STRUCT_FIELD(tumble_list, "tumble_list"),
    DEFINE_STRUCT_FIELD(disabled_list, "disabled_list"),
    DEFINE_STRUCT_FIELD(other_list, "other_list")
    );

DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_info::boxes,
    DEFINE_STRUCT_FIELD(score, "score"),
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));

struct climb_tumble_pedestrian_detect_info_result {
    climb_tumble_pedestrian_info detect_info;
};

DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct climb_tumble_pedestrian_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct climb_tumble_pedestrian_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<pedestrian_info::boxes> pedestrian_info_list;
            int device_id;
            float conf_thres;
            float nms_thres;
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
DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(pedestrian_info_list, "pedestrian_info_list"),
    DEFINE_STRUCT_FIELD(device_id, "device_id"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));

DEFINE_STRUCT_SCHEMA(climb_tumble_pedestrian_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));