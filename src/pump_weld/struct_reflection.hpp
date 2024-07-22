#include <info_pump_weld.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pump_weld_config {
    int device;
    int format;
    float nms_thres;
    float wmachine_conf_thres;
    float wlight_conf_thres;
    int batch;
};
DEFINE_STRUCT_SCHEMA(pump_weld_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(wmachine_conf_thres, "wmachine_conf_thres"),
    DEFINE_STRUCT_FIELD(wlight_conf_thres, "wlight_conf_thres"),
    DEFINE_STRUCT_FIELD(batch, "batch"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(pump_weld_info::boxes::weld_box, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"),
    DEFINE_STRUCT_FIELD(x2, "x2"),
    DEFINE_STRUCT_FIELD(y2, "y2")
    );

DEFINE_STRUCT_SCHEMA(pump_weld_info::boxes, 
    DEFINE_STRUCT_FIELD(category, "category"), 
    DEFINE_STRUCT_FIELD(can_x1, "can_x1"),
    DEFINE_STRUCT_FIELD(can_y1, "can_y1"),
    DEFINE_STRUCT_FIELD(can_x2, "can_x2"),
    DEFINE_STRUCT_FIELD(can_y2, "can_y2"),
    DEFINE_STRUCT_FIELD(weld_list, "weld_list")
    );

DEFINE_STRUCT_SCHEMA(pump_weld_info, 
    DEFINE_STRUCT_FIELD(persons_weld, "persons_weld")
    );

struct pump_weld_detect_info_result {
    pump_weld_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_weld_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_weld_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_weld_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pump_weld_detect_param {

    struct optional_params {
        struct dyparams_params {
            float wmachine_conf_thres;
            float wlight_conf_thres;
            float nms_thres;
            int candidate_box_width;
            int candidate_box_height;
            int batch;
        };
        dyparams_params dyparams;
    };

    struct basic_params {
        int height;
        int width;
        int num;
    };
    optional_params algo_params;
    basic_params data_params;
};

  //检测入参
DEFINE_STRUCT_SCHEMA(pump_weld_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_weld_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pump_weld_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(wmachine_conf_thres, "wmachine_conf_thres"),
    DEFINE_STRUCT_FIELD(wlight_conf_thres, "wlight_conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(candidate_box_width, "candidate_box_width"),
    DEFINE_STRUCT_FIELD(candidate_box_height, "candidate_box_height"),
    DEFINE_STRUCT_FIELD(batch, "batch"));

DEFINE_STRUCT_SCHEMA(pump_weld_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"), 
    DEFINE_STRUCT_FIELD(num, "num"));