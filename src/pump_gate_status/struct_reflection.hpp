#include <info_pump_gate_status.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pump_gate_status_config {
    int device;
    int format;
};
DEFINE_STRUCT_SCHEMA(pump_gate_status_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(pump_gate_status_info, 
    DEFINE_STRUCT_FIELD(security_status, "security_status")
    );

struct pump_gate_status_detect_info_result {
    pump_gate_status_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_gate_status_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_gate_status_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pump_gate_status_detect_param {

    struct optional_params {
        struct dyparams_params {
            float door_close_ratio;
            float door_open_ratio;
            float floor_ratio;
            int device_id;
        };
        struct gate_roi {
            struct gate_door_roi {
                int x1;
                int y1;
                int x2;
                int y2;
            };
            struct gate_floor_roi {
                int x1;
                int y1;
                int x2;
                int y2;
            };
            gate_door_roi door;
            gate_floor_roi floor;
        };
        dyparams_params dyparams;
        gate_roi rois;
        int yellow_hsv_lower;
        int yellow_hsv_upper;
        int gray_hsv_lower;
        int gray_hsv_upper;
    };

    struct basic_params {
        int height;
        int width;
    };
    optional_params algo_params;
    basic_params data_params;
};

  //检测入参
DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"),
    DEFINE_STRUCT_FIELD(rois, "rois"),
    DEFINE_STRUCT_FIELD(yellow_hsv_lower, "yellow_hsv_lower"),
    DEFINE_STRUCT_FIELD(yellow_hsv_upper, "yellow_hsv_upper"),
    DEFINE_STRUCT_FIELD(gray_hsv_lower, "gray_hsv_lower"),
    DEFINE_STRUCT_FIELD(gray_hsv_upper, "gray_hsv_upper"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(door_close_ratio, "door_close_ratio"),
    DEFINE_STRUCT_FIELD(door_open_ratio, "door_open_ratio"), 
    DEFINE_STRUCT_FIELD(floor_ratio, "floor_ratio"),
    DEFINE_STRUCT_FIELD(device_id, "device_id"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::optional_params::gate_roi, 
    DEFINE_STRUCT_FIELD(door, "door"),
    DEFINE_STRUCT_FIELD(floor, "floor"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::optional_params::gate_roi::gate_door_roi,
    DEFINE_STRUCT_FIELD(x1, "x1"), 
    DEFINE_STRUCT_FIELD(y1, "y1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::optional_params::gate_roi::gate_floor_roi,
    DEFINE_STRUCT_FIELD(x1, "x1"), 
    DEFINE_STRUCT_FIELD(y1, "y1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));

DEFINE_STRUCT_SCHEMA(pump_gate_status_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));