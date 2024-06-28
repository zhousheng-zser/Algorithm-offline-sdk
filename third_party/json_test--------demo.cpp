// clang++ reflection_json.cc -std=c++14 -Wall -o ref_json && ./ref_json

#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <optional>
#include "struct_json.hpp"


struct SimpleStruct {
    bool aaa;
    int int_;
    double double_;
    std::string string_;
    std::unique_ptr<bool> optional_;
};

struct NestedStruct {
    SimpleStruct nested_;
    std::vector<SimpleStruct> vector_;
};

DEFINE_STRUCT_SCHEMA(SimpleStruct,
    DEFINE_STRUCT_FIELD(aaa, "aaa"),
    DEFINE_STRUCT_FIELD(int_, "_int"),
    DEFINE_STRUCT_FIELD(double_, "_double"),
    DEFINE_STRUCT_FIELD(string_, "_string"),
    DEFINE_STRUCT_FIELD(optional_, "_optional")
);

DEFINE_STRUCT_SCHEMA(NestedStruct,
    DEFINE_STRUCT_FIELD(nested_, "_nested"),
    DEFINE_STRUCT_FIELD(vector_, "_vector"));

//int main() {
//
//    SimpleStruct temp = { .aaa = false , .int_ = 9 , .double_ = 55.55,.string_ = "asdsads", .optional_ = nullptr };
//    nlohmann::json ss(temp);
//    std:: cout << "++++++"<< ss.dump()<< "------\n";
//
//
//
//    std::cout << json(json::parse(R"(
//    {
//    	"_nested":{
//    		"aaa":false,
//    		"_int":1,
//    		"_double":2.2,
//    		"_string":"wwwwss",
//            "_optional": true 
//    	},
//    	"_vector":[{
//    		"aaa":false,
//    		"_int":2,
//    		"_double":3.2,
//    		"_string":"wwswwss",
//            "_optional": false
//    	},{
//    		"aaa":false,
//    		"_int":3,
//    		"_double":5.2,
//    		"_string":"ww2wwss"
//    	}
//    	]
//    }
//        )")
//            .get<NestedStruct>())
//            .dump(2)
//            << std::endl;
//        std::getchar(); 
//    return 0;
//}