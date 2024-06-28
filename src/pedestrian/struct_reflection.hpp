#include <info_pedestrian.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pedestrian_config {
    int device;
    int format;
    float conf_thres;
    float nms_thres;
};
DEFINE_STRUCT_SCHEMA(pedestrian_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), 
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));


  //行人框体
DEFINE_STRUCT_SCHEMA(pedestrian_info::boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(y2, "y2"),
    DEFINE_STRUCT_FIELD(score, "score")
    );

DEFINE_STRUCT_SCHEMA(pedestrian_info, 
    DEFINE_STRUCT_FIELD(person_list, "person_list")
    );

struct pedestrian_detect_info_result {
    pedestrian_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pedestrian_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pedestrian_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pedestrian_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pedestrian_detect_param {

    struct optional_params {
        struct dyparams_params {
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
DEFINE_STRUCT_SCHEMA(pedestrian_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pedestrian_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pedestrian_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres") ,
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));

DEFINE_STRUCT_SCHEMA(pedestrian_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));