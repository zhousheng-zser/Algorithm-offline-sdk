#include <info_posture.hpp>
#include <info_workcloth.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../posture/struct_reflection.hpp"

//配置文件
struct workcloth_config {
    struct color_hsv {
        std::vector<int>black;
        std::vector<int>grey;
        std::vector<int>white;
        std::vector<int>red;
        std::vector<int>orange;
        std::vector<int>yellow;
        std::vector<int>green;
        std::vector<int>cyan;
        std::vector<int>blue;
        std::vector<int>purple;
    };
    int device;
    int format;
    float conf_thres;
    float nms_thres;
    float posture_conf_thres;
    std::vector<color_hsv> color_hsv_list;
};

DEFINE_STRUCT_SCHEMA(workcloth_config::color_hsv, 
    DEFINE_STRUCT_FIELD(black, "black"), 
    DEFINE_STRUCT_FIELD(grey, "grey"),
    DEFINE_STRUCT_FIELD(white, "white"), 
    DEFINE_STRUCT_FIELD(red, "red"), 
    DEFINE_STRUCT_FIELD(orange, "orange"),
    DEFINE_STRUCT_FIELD(yellow, "yellow"), 
    DEFINE_STRUCT_FIELD(green, "green"), 
    DEFINE_STRUCT_FIELD(cyan, "cyan"),
    DEFINE_STRUCT_FIELD(blue, "blue"), 
    DEFINE_STRUCT_FIELD(purple, "purple")
);

DEFINE_STRUCT_SCHEMA(workcloth_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"), 
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"), 
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(posture_conf_thres, "posture_conf_thres"),
    DEFINE_STRUCT_FIELD(color_hsv_list, "color_hsv_list"));


DEFINE_STRUCT_SCHEMA(workcloth_info, 
    DEFINE_STRUCT_FIELD(cloth_list, "cloth_list")
    );

DEFINE_STRUCT_SCHEMA(workcloth_info::boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"),
    DEFINE_STRUCT_FIELD(is_sleeve, "is_sleeve"), 
    DEFINE_STRUCT_FIELD(color_ratios, "color_ratios")
);


struct workcloth_detect_info_result {
    workcloth_info detect_info;
};

DEFINE_STRUCT_SCHEMA(workcloth_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct workcloth_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(workcloth_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct workcloth_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<posture_info> posture_info_list;
            float conf_thres;
            float nms_thres;
            workcloth_config::color_hsv color_hsv_cfg;
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
DEFINE_STRUCT_SCHEMA(workcloth_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(workcloth_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(workcloth_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(posture_info_list, "posture_info_list"),
    DEFINE_STRUCT_FIELD(color_hsv_cfg, "color_hsv_cfg"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));

DEFINE_STRUCT_SCHEMA(workcloth_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));