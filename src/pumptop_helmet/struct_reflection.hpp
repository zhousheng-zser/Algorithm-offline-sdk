#include <info_pumptop_helmet.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct pumptop_helmet_config {
    int device;
    int format;
    float pump_conf_thres;
    float people_conf_thres;
    float head_conf_thres;
    float head_score_conf_thres;
};
DEFINE_STRUCT_SCHEMA(pumptop_helmet_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(pump_conf_thres, "pump_conf_thres"),
    DEFINE_STRUCT_FIELD(people_conf_thres, "people_conf_thres"), 
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"),
    DEFINE_STRUCT_FIELD(head_score_conf_thres, "head_score_conf_thres"));


  //对外结构体参数 解析parser_execute_result中的result串
DEFINE_STRUCT_SCHEMA(pumptop_helmet_info::boxes, 
    DEFINE_STRUCT_FIELD(score, "score"), 
    DEFINE_STRUCT_FIELD(helmet_score, "helmet_score"),
    DEFINE_STRUCT_FIELD(category, "category"), 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2")
    );

DEFINE_STRUCT_SCHEMA(pumptop_helmet_info, 
    DEFINE_STRUCT_FIELD(person_list, "person_list")
    );

struct pumptop_helmet_detect_info_result {
    pumptop_helmet_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pumptop_helmet_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pumptop_helmet_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pumptop_helmet_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct pumptop_helmet_detect_param {

    struct optional_params {
        struct dyparams_params {
            float head_conf_thres;
            float pump_conf_thres;
            float people_conf_thres;
            float head_score_conf_thres;
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
DEFINE_STRUCT_SCHEMA(pumptop_helmet_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pumptop_helmet_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pumptop_helmet_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"),
    DEFINE_STRUCT_FIELD(pump_conf_thres, "pump_conf_thres") ,
    DEFINE_STRUCT_FIELD(people_conf_thres, "people_conf_thres"),
    DEFINE_STRUCT_FIELD(head_score_conf_thres, "head_score_conf_thres"));

DEFINE_STRUCT_SCHEMA(pumptop_helmet_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));