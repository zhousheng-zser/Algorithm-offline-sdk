#include <info_posture.hpp>
#include <info_head.hpp>
#include <info_onphone.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../posture/struct_reflection.hpp"
#include "../head/struct_reflection.hpp"

//配置文件
struct onphone_config {
    int device;
    int format;
    float posture_conf_thres;
    float head_conf_thres;
    float conf_thres;
    float nms_thres;
    float phone_distance_thres;
};
DEFINE_STRUCT_SCHEMA(onphone_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(posture_conf_thres, "posture_conf_thres"), 
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"), 
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"), 
    DEFINE_STRUCT_FIELD(phone_distance_thres, "phone_distance_thres"));


DEFINE_STRUCT_SCHEMA(onphone_info, 
    DEFINE_STRUCT_FIELD(norm_list, "norm_list"),
    DEFINE_STRUCT_FIELD(onphone_list, "onphone_list")
    );


//没打电话的
DEFINE_STRUCT_SCHEMA(onphone_info::norm_boxes, 
    DEFINE_STRUCT_FIELD(head_score, "head_score"),
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));

//打电话的
DEFINE_STRUCT_SCHEMA(onphone_info::onphone_boxes, 
    DEFINE_STRUCT_FIELD(head_score, "head_score"),
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(phone_list, "phone_list"));

//手机
DEFINE_STRUCT_SCHEMA(onphone_info::onphone_boxes::phone_boxes, 
    DEFINE_STRUCT_FIELD(phone_score, "phone_score"),
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));


struct onphone_detect_info_result {
    onphone_info detect_info;
};

DEFINE_STRUCT_SCHEMA(onphone_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct onphone_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(onphone_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct onphone_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::unique_ptr<std::vector<posture_info>> posture_info_list;
            std::unique_ptr<std::vector<head_info>> head_info_list;
            float conf_thres;
            float nms_thres;
            float phone_distance_thres;
        };
        dyparams_params dyparams;
        int command;
    };

    struct basic_params {
        int height;
        int width;
    };
    optional_params algo_params;
    basic_params data_params;
};

  //检测入参
DEFINE_STRUCT_SCHEMA(onphone_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(onphone_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"),
    DEFINE_STRUCT_FIELD(command, "command"));

DEFINE_STRUCT_SCHEMA(onphone_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(posture_info_list, "posture_info_list"),
    DEFINE_STRUCT_FIELD(head_info_list, "head_info_list"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(phone_distance_thres, "phone_distance_thres"));

DEFINE_STRUCT_SCHEMA(onphone_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));