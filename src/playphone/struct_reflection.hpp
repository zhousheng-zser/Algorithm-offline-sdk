#include <info_posture.hpp>
#include <info_playphone.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../posture/struct_reflection.hpp"

//配置文件
struct playphone_config {
    int device;
    int format;
    float posture_conf_thres;
    float head_conf_thres;
    float head_nms_thres;
    float phone_conf_thres;
    float phone_nms_thres;
};
DEFINE_STRUCT_SCHEMA(playphone_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(posture_conf_thres, "posture_conf_thres"), 
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"), 
    DEFINE_STRUCT_FIELD(head_nms_thres, "head_nms_thres"),
    DEFINE_STRUCT_FIELD(phone_conf_thres, "phone_conf_thres"), 
    DEFINE_STRUCT_FIELD(phone_nms_thres, "phone_nms_thres")
);


DEFINE_STRUCT_SCHEMA(playphone_info, 
    DEFINE_STRUCT_FIELD(bodyerror_list, "bodyerror_list"),
    DEFINE_STRUCT_FIELD(norm_list, "norm_list"), 
    DEFINE_STRUCT_FIELD(playphone_list, "playphone_list")
    );


//错误列表
DEFINE_STRUCT_SCHEMA(playphone_info::bodyerror_boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(man_score, "man_score"),
    DEFINE_STRUCT_FIELD(frequency, "frequency"),
    DEFINE_STRUCT_FIELD(id, "id"),
    DEFINE_STRUCT_FIELD(error_keypoints, "error_keypoints"));

//关键点置信度
DEFINE_STRUCT_SCHEMA(playphone_info::error_list, 
    DEFINE_STRUCT_FIELD(nose, "nose"),
    DEFINE_STRUCT_FIELD(r_eye, "r_eye"), 
    DEFINE_STRUCT_FIELD(l_eye, "l_eye"), 
    DEFINE_STRUCT_FIELD(r_hand, "r_hand"), 
    DEFINE_STRUCT_FIELD(l_hand, "l_hand")
);

  //没在玩手机
DEFINE_STRUCT_SCHEMA(playphone_info::boxes, 
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(man_score, "man_score"),
    DEFINE_STRUCT_FIELD(frequency, "frequency"),
    DEFINE_STRUCT_FIELD(id, "id"));

// 在玩手机
DEFINE_STRUCT_SCHEMA(playphone_info::playphone_boxes,
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(man_score, "man_score"),
    DEFINE_STRUCT_FIELD(frequency, "frequency"),
    DEFINE_STRUCT_FIELD(id, "id"),
    DEFINE_STRUCT_FIELD(phone_list, "phone_list")
);

// 手机列表
DEFINE_STRUCT_SCHEMA(playphone_info::playphone,
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"), 
    DEFINE_STRUCT_FIELD(phone_score, "phone_score")
);

struct playphone_detect_info_result {
    playphone_info detect_info;
};

DEFINE_STRUCT_SCHEMA(playphone_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct playphone_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(playphone_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct playphone_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<posture_info> posture_info_list;
            float head_conf_thres;
            float head_nms_thres;
            float phone_conf_thres;
            float phone_nms_thres;
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
DEFINE_STRUCT_SCHEMA(playphone_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(playphone_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(playphone_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(posture_info_list, "posture_info_list"),
    DEFINE_STRUCT_FIELD(head_conf_thres, "head_conf_thres"),
    DEFINE_STRUCT_FIELD(head_nms_thres, "head_nms_thres"),
    DEFINE_STRUCT_FIELD(phone_conf_thres, "phone_conf_thres"),
    DEFINE_STRUCT_FIELD(phone_nms_thres, "phone_nms_thres")
);

DEFINE_STRUCT_SCHEMA(playphone_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));