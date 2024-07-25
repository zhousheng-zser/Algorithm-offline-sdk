#include <info_pump_light.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pump_light_config {
    int device;
    int format;
    float conf_thres;
};
DEFINE_STRUCT_SCHEMA(pump_light_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(pump_light_info, 
    DEFINE_STRUCT_FIELD(score, "score"), 
    DEFINE_STRUCT_FIELD(light_status, "light_status")
    );

struct pump_light_detect_info_result {
    pump_light_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_light_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_light_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_light_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pump_light_detect_param {

    struct optional_params {
        struct dyparams_params {
            float conf_thres;
            int x1;
            int y1;
            int x2;
            int y2;
            int x3;
            int y3;
            int x4;
            int y4;
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
DEFINE_STRUCT_SCHEMA(pump_light_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_light_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pump_light_detect_param::optional_params::dyparams_params,
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), DEFINE_STRUCT_FIELD(x1, "x1"), DEFINE_STRUCT_FIELD(y1, "y1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), DEFINE_STRUCT_FIELD(y2, "y2"), DEFINE_STRUCT_FIELD(x3, "x3"),
    DEFINE_STRUCT_FIELD(y3, "y3"), DEFINE_STRUCT_FIELD(x4, "x4"), DEFINE_STRUCT_FIELD(y4, "y4")

);

DEFINE_STRUCT_SCHEMA(pump_light_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));