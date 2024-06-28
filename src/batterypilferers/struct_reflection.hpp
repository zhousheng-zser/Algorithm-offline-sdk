#include <info_batterypilferers.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//�����ļ�
struct batterypilferers_config {
    int device;
    int format;
    int batch;
};
DEFINE_STRUCT_SCHEMA(batterypilferers_config, 
    DEFINE_STRUCT_FIELD(device, "device"),
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(batch, "batch"));


  //����ṹ����� ����parser_execute_result�е�result��
DEFINE_STRUCT_SCHEMA(batterypilferers_info::boxes, 
    DEFINE_STRUCT_FIELD(score, "score"), 
    DEFINE_STRUCT_FIELD(category, "category"), 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(y2, "y2")
    );

DEFINE_STRUCT_SCHEMA(batterypilferers_info, 
    DEFINE_STRUCT_FIELD(fight_list, "fight_list"),
    DEFINE_STRUCT_FIELD(normal_list, "normal_list")
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
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"),
    DEFINE_STRUCT_FIELD(batch, "batch"));

// detect
struct batterypilferers_detect_param {

    struct optional_params {
        struct dyparams_params {
            int roi_x;
            int roi_y;
            int roi_width;
            int roi_height;
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

  //������
DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(roi_x, "roi_x"),
    DEFINE_STRUCT_FIELD(roi_y, "roi_y"),
    DEFINE_STRUCT_FIELD(roi_width, "roi_width"),
    DEFINE_STRUCT_FIELD(roi_height, "roi_height"));

DEFINE_STRUCT_SCHEMA(batterypilferers_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));