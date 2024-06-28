#include <info_head.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

////配置文件
//struct head_config {
//    int device;
//    int model_type;
//    float conf_thres;
//    float nms_thres;
//};
//DEFINE_STRUCT_SCHEMA(head_config, 
//    DEFINE_STRUCT_FIELD(device, "device"), 
//    DEFINE_STRUCT_FIELD(model_type, "model_type"),
//    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), 
//    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));



  //人物框体
DEFINE_STRUCT_SCHEMA(head_info, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(y2, "y2"),
    DEFINE_STRUCT_FIELD(score, "score")
    );


struct head_detect_info_result {
    std::vector<head_info> info_list;
};

DEFINE_STRUCT_SCHEMA(head_detect_info_result, 
    DEFINE_STRUCT_FIELD(info_list, "info_list"));


// new 
struct head_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(head_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct head_detect_param {

    struct optional_params {
        struct dyparams_params {
            float conf_thres;
            float nms_thres;
        };
        std::unique_ptr<dyparams_params> dyparams;
    };

    struct basic_params {
        int height;
        int width;
    };
    optional_params algo_params;
    basic_params data_params;
};

// 检测入参
DEFINE_STRUCT_SCHEMA(head_detect_param, DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(head_detect_param::optional_params, DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(head_detect_param::optional_params::dyparams_params,
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));

DEFINE_STRUCT_SCHEMA(
    head_detect_param::basic_params, DEFINE_STRUCT_FIELD(height, "height"), DEFINE_STRUCT_FIELD(width, "width"));