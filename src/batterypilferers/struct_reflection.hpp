#include <info_batterypilferers.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//配置文件
struct batterypilferers_config {
    int device;
    int format;
    int conf_thres;
    int nms_thres;
    int batch;
};
DEFINE_STRUCT_SCHEMA(batterypilferers_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"),
    DEFINE_STRUCT_FIELD(batch, "batch"));


DEFINE_STRUCT_SCHEMA(batterypilferers_info, 
    DEFINE_STRUCT_FIELD(score, "score"), 
    DEFINE_STRUCT_FIELD(category, "category")
    );

struct batterypilferers_detect_info_result {
    batterypilferers_info detect_info;
};

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct batterypilferers_new_param {
    int device;
    std::string models_directory;
    int batch;
};


DEFINE_STRUCT_SCHEMA(batterypilferers_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"));

// detect
struct batterypilferers_detect_param {

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
        int channels;
        int num;
    };
    optional_params algo_params;
    basic_params data_params;
};

// 检测入参
DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param, DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::optional_params, DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::optional_params::dyparams_params,
    DEFINE_STRUCT_FIELD(conf_thres, "conf_thres"),
    DEFINE_STRUCT_FIELD(nms_thres, "nms_thres"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::basic_params, DEFINE_STRUCT_FIELD(height, "height"),
    DEFINE_STRUCT_FIELD(width, "width"), DEFINE_STRUCT_FIELD(channels, "channels"), DEFINE_STRUCT_FIELD(num, "num"));