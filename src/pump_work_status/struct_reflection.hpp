#include <info_pump_work_status.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pump_work_status_config {
    int device;
    int format;
};
DEFINE_STRUCT_SCHEMA(pump_work_status_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"));


  //对外结构体参数 解析parser_execute_result中的result串

DEFINE_STRUCT_SCHEMA(pump_work_status_info, 
    DEFINE_STRUCT_FIELD(security_status, "security_status")
    );

struct pump_work_status_detect_info_result {
    pump_work_status_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_work_status_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_work_status_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_work_status_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pump_work_status_detect_param {

    struct optional_params {
        struct dyparams_params {
            int big_paint_room;
            std::vector<int> mask_roi;
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
DEFINE_STRUCT_SCHEMA(pump_work_status_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_work_status_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pump_work_status_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(big_paint_room, "big_paint_room"), 
    DEFINE_STRUCT_FIELD(mask_roi, "mask_roi"));

DEFINE_STRUCT_SCHEMA(pump_work_status_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));