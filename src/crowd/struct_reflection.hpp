#include <info_crowd.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct crowd_config {
    int device;
    int format;
    int area_threshold;
    int max_area_list;
    float nms_thres;
};
DEFINE_STRUCT_SCHEMA(crowd_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(area_threshold, "area_threshold"), 
    DEFINE_STRUCT_FIELD(max_area_list, "max_area_list"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(crowd_info::boxes, 
    DEFINE_STRUCT_FIELD(category, "category"), 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(y2, "y2")
    );

DEFINE_STRUCT_SCHEMA(crowd_info, 
    DEFINE_STRUCT_FIELD(head_list, "head_list"),
    DEFINE_STRUCT_FIELD(cluster_list, "cluster_list")
    );

struct crowd_detect_info_result {
    crowd_info detect_info;
};

DEFINE_STRUCT_SCHEMA(crowd_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct crowd_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(crowd_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct crowd_detect_param {

    struct optional_params {
        struct dyparams_params {
            int min_cluster_size;
            int area_threshold;
            float nms_thres;
            int max_area_list;
            int trigger_delay;
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
DEFINE_STRUCT_SCHEMA(crowd_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(crowd_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(crowd_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(min_cluster_size, "min_cluster_size"),
    DEFINE_STRUCT_FIELD(area_threshold, "area_threshold"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(max_area_list, "max_area_list"),
    DEFINE_STRUCT_FIELD(trigger_delay, "trigger_delay"), 
    DEFINE_STRUCT_FIELD(device_id, "device_id"));

DEFINE_STRUCT_SCHEMA(crowd_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));