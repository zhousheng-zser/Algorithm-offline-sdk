#include <info_head.hpp>
#include <info_helmet.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../head/struct_reflection.hpp"

//配置文件
struct helmet_config {
    int device;
    int format;
    float head_conf_thres;
    float conf_thres;
    float nms_thres;
    float min_size;
};
DEFINE_STRUCT_SCHEMA(helmet_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"), 
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), 
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(min_size, "min_size")
);


DEFINE_STRUCT_SCHEMA(helmet_info, 
    DEFINE_STRUCT_FIELD(with_helmet_list, "with_helmet_list"),
    DEFINE_STRUCT_FIELD(with_hat_list, "with_hat_list"), 
    DEFINE_STRUCT_FIELD(head_list, "head_list")
    );

DEFINE_STRUCT_SCHEMA(helmet_info::boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(score, "score"));

struct helmet_detect_info_result {
    helmet_info detect_info;
};

DEFINE_STRUCT_SCHEMA(helmet_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct helmet_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(helmet_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct helmet_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<head_info> head_info_list;
            float conf_thres;
            float nms_thres;
            float min_size;
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
DEFINE_STRUCT_SCHEMA(helmet_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(helmet_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(helmet_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(head_info_list, "head_info_list"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(min_size, "min_size")
);

DEFINE_STRUCT_SCHEMA(helmet_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));