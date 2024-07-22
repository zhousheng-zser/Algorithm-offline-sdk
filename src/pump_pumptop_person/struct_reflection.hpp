#include <info_pedestrian.hpp>
#include <info_pump_pumptop_person.hpp>
#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"
#include "../pedestrian/struct_reflection.hpp"

//配置文件
struct pump_pumptop_person_config {
    int device;
    int format;
    float person_conf;
    float person_area_ratio_thres;
};
DEFINE_STRUCT_SCHEMA(pump_pumptop_person_config, 
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(format, "format"),
    DEFINE_STRUCT_FIELD(person_conf, "person_conf"), 
    DEFINE_STRUCT_FIELD(person_area_ratio_thres, "person_area_ratio_thres"));


DEFINE_STRUCT_SCHEMA(pump_pumptop_person_info, 
    DEFINE_STRUCT_FIELD(persons_in_pumptop, "persons_in_pumptop"), 
    DEFINE_STRUCT_FIELD(persons_out_pumptop, "persons_out_pumptop")
    );

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_info::boxes,
    DEFINE_STRUCT_FIELD(pump, "pump"),
    DEFINE_STRUCT_FIELD(category, "category"),
    DEFINE_STRUCT_FIELD(score, "score"),
    DEFINE_STRUCT_FIELD(x1, "x1"),
    DEFINE_STRUCT_FIELD(y1, "y1"), 
    DEFINE_STRUCT_FIELD(x2, "x2"), 
    DEFINE_STRUCT_FIELD(y2, "y2"));

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_info::boxes::pump_point,
    DEFINE_STRUCT_FIELD(x, "x"), 
    DEFINE_STRUCT_FIELD(y, "y"));

struct pump_pumptop_person_detect_info_result {
    pump_pumptop_person_info detect_info;
};

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_detect_info_result, 
    DEFINE_STRUCT_FIELD(detect_info, "detect_info"));


// new 
struct pump_pumptop_person_new_param {
    int device;
    std::string models_directory;
};


DEFINE_STRUCT_SCHEMA(pump_pumptop_person_new_param,
    DEFINE_STRUCT_FIELD(device, "device"), 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory")
);

// detect
struct pump_pumptop_person_detect_param {

    struct optional_params {
        struct dyparams_params {
            std::vector<pedestrian_info::boxes> pedestrian_info_list;
            float person_area_ratio_thres;
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
DEFINE_STRUCT_SCHEMA(pump_pumptop_person_detect_param, 
    DEFINE_STRUCT_FIELD(algo_params, "algo_params"),
    DEFINE_STRUCT_FIELD(data_params, "data_params"));

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_detect_param::optional_params, 
    DEFINE_STRUCT_FIELD(dyparams, "dyparams"));

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_detect_param::optional_params::dyparams_params, 
    DEFINE_STRUCT_FIELD(pedestrian_info_list, "pedestrian_info_list"),
    DEFINE_STRUCT_FIELD(person_area_ratio_thres, "person_area_ratio_thres")
);

DEFINE_STRUCT_SCHEMA(pump_pumptop_person_detect_param::basic_params, 
    DEFINE_STRUCT_FIELD(height, "height"), 
    DEFINE_STRUCT_FIELD(width, "width"));