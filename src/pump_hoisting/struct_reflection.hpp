#include <info_pump_hoisting.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pump_hoisting_config {
    int device;
    int format;
    float conf_thres;
    float nms_thres;
    float move_threshold;
};
DEFINE_STRUCT_SCHEMA(pump_hoisting_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(move_threshold, "move_threshold"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(pump_hoisting_info::boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"),
    DEFINE_STRUCT_FIELD(x1, "x3"),
    DEFINE_STRUCT_FIELD(y1, "y3"), 
    DEFINE_STRUCT_FIELD(x2, "x4"), 
    DEFINE_STRUCT_FIELD(y2, "y4")
    );

DEFINE_STRUCT_SCHEMA(pump_hoisting_info, 
    DEFINE_STRUCT_FIELD(dangerous_region, "dangerous_region")
    );

struct pump_hoisting_detect_info_result {
    pump_hoisting_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_hoisting_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_hoisting_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_hoisting_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pump_hoisting_detect_param {

    struct optional_params {
        struct dyparams_params {
            float conf_thres;
            float nms_thres;
            float move_threshold;
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
DEFINE_STRUCT_SCHEMA(pump_hoisting_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_hoisting_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pump_hoisting_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres") ,
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(move_threshold, "move_threshold"),
    DEFINE_STRUCT_FIELD(device_id, "device_id"));

DEFINE_STRUCT_SCHEMA(pump_hoisting_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));