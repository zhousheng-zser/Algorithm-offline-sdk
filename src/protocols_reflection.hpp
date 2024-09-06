#pragma once
#include <struct_json.hpp> 
#include <parser_c.hpp>
// 
struct basic_result {
    int code;
    std::string message;
};


// 加载插件文件
struct parser_init_result {
    basic_result status;
};

//加载模型结果
struct parser_create_instance_result {
    std::string instance_id;
    basic_result status;
};

// 检测结果
struct parser_execute_result {
    std::unique_ptr<std::string> result;
    basic_result status;
};


DEFINE_STRUCT_SCHEMA(basic_result, 
    DEFINE_STRUCT_FIELD(code, "code"), 
    DEFINE_STRUCT_FIELD(message, "message"));

DEFINE_STRUCT_SCHEMA(parser_init_result, 
    DEFINE_STRUCT_FIELD(status, "status"));
    
DEFINE_STRUCT_SCHEMA(parser_create_instance_result, 
    DEFINE_STRUCT_FIELD(instance_id, "instance_id"),
    DEFINE_STRUCT_FIELD(status, "status"));


DEFINE_STRUCT_SCHEMA(parser_execute_result, 
    DEFINE_STRUCT_FIELD(result, "result"), 
    DEFINE_STRUCT_FIELD(status, "status"));
    
// 公共配置文件
struct configure_directory {
    std::string models_directory;
    std::string directory;
    std::string license_directory;
    std::string empower_serial_number;
    std::string dump_img_directory;
};
DEFINE_STRUCT_SCHEMA(configure_directory, 
    DEFINE_STRUCT_FIELD(models_directory, "models_directory"), 
    DEFINE_STRUCT_FIELD(directory, "directory"), 
    DEFINE_STRUCT_FIELD(license_directory, "license_directory"), 
    DEFINE_STRUCT_FIELD(empower_serial_number, "empower_serial_number"),
    DEFINE_STRUCT_FIELD(dump_img_directory, "dump_img_directory"));


// 算法线程池数量配置文件
struct thread_pool_num {
    struct algo {
        std::string protocols;
        int num;
    };
    std::vector<algo> algo_list;

};

DEFINE_STRUCT_SCHEMA(thread_pool_num, 
    DEFINE_STRUCT_FIELD(algo_list, "algo_list"));


DEFINE_STRUCT_SCHEMA(thread_pool_num::algo, 
    DEFINE_STRUCT_FIELD(protocols, "protocols"), 
    DEFINE_STRUCT_FIELD(num, "num"));