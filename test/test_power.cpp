#include "head_require.h"
#include "config.hpp"
static const std::string CONFIG_PATH   = "/root/install/glasssix-offline-sdk/config";// 编译识别不了 abi
static std::string OUTPUT_DIR          = "results/";
static glasssix::abi::string IMG_PATH  = "/root/img/"; 
static int TIMES                       = 1;
bool condition_time                    = false;
bool condition                         = false;
bool is_out_json                       = false;
namespace fs = std::filesystem;
#include<vector>
#include<string>
#include<fstream>
using namespace glasssix;
namespace glasssix {
    //主要一些重要的函数
    //写入json文件，并进行比较
    void write_json(std::string instance, glasssix::json data, bool is_multi = false, bool is_video = false,
        std::string multi_file = "")
    {
        //return;
        std::string path          = CONFIG_PATH + "/../" + OUTPUT_DIR + "correct/" + instance + "/";
        std::string path_fault    = CONFIG_PATH + "/../" + OUTPUT_DIR + "fault/" + instance + "/";
        std::string path_warning  = CONFIG_PATH + "/../" + OUTPUT_DIR + "warning/" + instance + "/";
        std::string filename= path + instance + ".json";//绝对路径名
        std::string instance_name = (!is_multi) ? instance : instance + "_" + multi_file;
        if (is_multi) {
            filename = path + instance_name + ".json";
        }

        std::string out_path{};
        //if (std::filesystem::exists(filename)) // 先读取,用来比较
        if (1)//鉴于存在,某个算法本身无结果,所以就不判断旧有的数据是否存在了
        {
            //// 创建一个字符串流
            //std::ostringstream oss;
            //// 将文件内容读取到字符串流中
            //oss << inputFile.rdbuf(); // 读取整个文件的内容
            //// 获取字符串
            //std::string fileContent = oss.str();
            //auto old_data           = glasssix::json(fileContent);
            glasssix::json old_data;
            try {
                std::ifstream inputFile(filename);
                if (!inputFile.is_open())
                    ;
                // return;
                // 使用 peek() 检查文件的第一个字符是否到达文件结尾
                if (!(inputFile.peek() == std::ifstream::traits_type::eof()))
                    inputFile >> old_data;
                // 比较结果
                std::cout << "file image: " << instance_name << std::endl;
                if (instance == "wander") {
                    std::string index{"person_info"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "flame") {
                    std::string index{"fire_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "refvest") {
                    std::string index{"with_refvest_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "leavepost") {
                    std::string index{"hat_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "sleep") {
                    std::string index{"lying_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "smoke") {
                    std::string index{"smoke_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "playphone") {
                    std::string index{"playphone_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "onphone_head") {
                    std::string index{"onphone_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "onphone_posture") {
                    std::string index{"onphone_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "workcloth") {
                    std::string index{"cloth_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "vehicle") {
                    std::string index{"vehicle_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "smog") {
                    std::string index{"smog_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "helmet") {
                    std::string index{"with_helmet_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "fighting") {
                    std::string index{"fight_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "crowd") {
                    std::string index{"head_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "wander_limit") {
                    std::string index{"segment_info"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "crossing") {
                    std::string index{"crossing_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "batterypilferers") {
                    std::string index{"steal_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pedestrian_min") {
                    std::string index{"person_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "climb_tumble_pedestrian_climb") {
                    std::string index{"climb_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "climb_tumble_pedestrian_tumble") {
                    std::string index{"tumble_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "policeuniform") {
                    std::string index{"without_policeuniform_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pump_vesthelmet") { //& 粗略比较//TODO
                    std::string index{"pump_vesthelmet_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pump_pumptop_person") {
                    std::string index{"persons_in_pumptop"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pump_mask") {
                    std::string index{"pump_head_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pumptop_helmet") {
                    std::string index{"person_list"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pump_hoisting") {
                    std::string index{"dangerous_region"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pump_weld") {
                    std::string index{"persons_weld"};
                    int old_number = old_data[index].size();
                    int new_number = data[index].size();
                    std::cout << "instance: " << instance << " old_data: " << old_number << " ";
                    std::cout << "instance: " << instance << " new_data: " << new_number << " ";
                    if (new_number < old_number) {
                        std::cout << "\nwarning : " << instance << "'s size == " << new_number << std::endl;
                        path = path_warning;
                    }
                    if (new_number == 0) {
                        std::cout << "\nfault : " << instance << "'s size == " << new_number << std::endl;
                        path = path_fault;
                    }
                }
                if (std::filesystem::exists(filename)) // 先读取,用来比较,以下算法比较特殊
                {

                    std::ifstream inputFile(filename);
                    if (!inputFile.is_open())
                        return;
                    if (instance == "subway_anomaly_yf" || instance == "subway_anomaly_nzx") {
                        std::string index{"anomaly_status"};
                        std::cout << "old_data: " << old_data[index] << " ";
                        std::cout << "new_data: " << data[index] << " ";
                        if (data != old_data) {
                            std::cout << "fault : " << instance << "'s old_data == " << old_data
                                    << ";'s new_data == " << data << std::endl;
                            path = path_fault;
                        }
                    }
                    if (instance == "pump_light") {
                        std::string index{"light_status"};
                        std::cout << "old_data: " << old_data[index] << " ";
                        std::cout << "new_data: " << data[index] << " ";
                        if (old_data[index] != data[index]) {
                            std::cout << "fault : " << instance << "'s old_data == " << old_data
                                    << ";'s new_data == " << data << std::endl;
                            path = path_fault;
                        }
                    }
                    if (instance == "pump_gate_status") {
                        std::cout << "old_data: " << old_data << " ";
                        std::cout << "new_data: " << data << " ";
                        if (data != old_data) {
                            std::cout << "fault : " << instance << "'s old_data == " << old_data << ";'s new_data == " << data << std::endl;
                            path = path_fault;
                        }
                    }
                    if (instance == "pump_work_status") {
                        std::cout << "old_data: " << old_data << " ";
                        std::cout << "new_data: " << data << " ";
                        if (data != old_data) {
                            std::cout << "fault : " << instance << "'s old_data == " << old_data << ";'s new_data == " << data << std::endl;
                            path = path_fault;
                        }
                    }
                }

            } catch (const glasssix::json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
                return;
            }

        }
        filename = path + instance_name + ".json";

        // 检查目录是否存在,文件是否存在
        // 创建目录（包括父目录）
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
        }
        std::ofstream outFile(filename);
        // 检查文件是否成功打开
        if (!outFile) {
            std::cerr << "Error opening file for writing!" << std::endl;
            return;
        }
        outFile << data;
        // 关闭文件
        outFile.close();
    }
    // 返回的绝对路径
    std::vector<abi::string> find_file(std::filesystem::path folder_path) {
        std::vector<abi::string> ans_list;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
                std::string temp(entry.path());
                ans_list.emplace_back(temp);
            }
        }
        return ans_list;
    }
}

//  调试代码
namespace glasssix {
    // t0 多线程测安全帽
    void thread_function_helmet(const std::string& instance) {
        gx_helmet_api* api_temp = new gx_helmet_api(glasssix::abi::string(CONFIG_PATH));
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "helmet.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_helmet(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[helmet] : with_helmet_list = %d with_hat_list = %d head_list = %d\n",
                        val.with_helmet_list.size(), val.with_hat_list.size(), val.head_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("helmet time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t22 多线程测人头
    void thread_function_head(const std::string& instance) {
        gx_head_api* api_temp = new gx_head_api(glasssix::abi::string(CONFIG_PATH));
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "head.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_head(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[head] : head_list = %d\n", val.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("head time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t1 多线程测火焰
    void thread_function_flame(const std::string& instance) {
        gx_flame_api* api_temp = new gx_flame_api(glasssix::abi::string(CONFIG_PATH));
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "flame.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_flame(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[flame] : fire_list = %d\n", val.fire_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t14 多线程测烟雾
    void thread_function_smog(const std::string& instance) {
        gx_smog_api* api_temp = new gx_smog_api(glasssix::abi::string(CONFIG_PATH));
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "smog.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smog(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[smog] : smog_list = %d\n", val.smog_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("smog time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t2 多线程测反光衣
    void thread_function_refvest(const std::string& instance) {
        gx_refvest_api* api_temp = new gx_refvest_api(glasssix::abi::string(CONFIG_PATH));
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "refvest.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_refvest(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[refvest] : with_refvest_list = %d without_refvest_list = %d\n",
                        val.with_refvest_list.size(), val.without_refvest_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("refvest time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t3 多线程测搜索
    void thread_function_search(const std::string& instance) {
        gx_face_api* api_temp = new gx_face_api(glasssix::abi::string(CONFIG_PATH));
        api_temp->user_load();
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        const gx_img_api img(abi::string(IMG_PATH) + "action_live_0.jpg", static_cast<int>(1e9));
        api_temp->user_add_records(abi::vector<abi::string>{"123"}, abi::vector<gx_img_api>{img}, false, false);
        while (T--) {
            try {
                auto val = api_temp->user_search(
                    gx_img_api{abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9)}, 1, 0.5);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[search] : similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("search time = %lld microsecond\n", duration.count());
        api_temp->user_remove_all();
        delete api_temp;
    }
    // t4 多线程测融合搜索
    void thread_function_integration(const std::string& instance) {
        gx_face_api* api_temp = new gx_face_api(glasssix::abi::string(CONFIG_PATH));
        api_temp->user_load();
        auto start = std::chrono::high_resolution_clock::now();
        int T      = TIMES;
        while (T--) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[integration] : prob = %.3f\n", val.prob);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        api_temp->user_remove_all();
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("integration time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t5 多线程测 配合活体 与 质量检测
    void thread_function_Action_live_Blur(const std::string& instance) {
        gx_face_api* api_temp = new gx_face_api(glasssix::abi::string(CONFIG_PATH));
        auto start            = std::chrono::high_resolution_clock::now();

        abi::vector<gx_img_api> img;
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_0.jpg", IMG_2K));
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_1.jpg", IMG_2K));
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_2.jpg", IMG_2K));
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_3.jpg", IMG_2K));
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_4.jpg", IMG_2K));
        img.emplace_back(gx_img_api(abi::string(IMG_PATH) + "action_live_5.jpg", IMG_2K));
        face_info info;
        bool action_result = 0;
        int T              = TIMES;
        while (T--) {
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
            if (condition)
                printf("[action_live] : BDFACE_ACTION_LIVE_BLINK %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
            if (condition)
                printf("[action_live] : BDFACE_ACTION_LIVE_OPEN_MOUTH %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
            if (condition)
                printf("[action_live] : BDFACE_ACTION_LIVE_NOD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
            if (condition)
                printf("[action_live] : BDFACE_ACTION_LIVE_LEFT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
            if (condition)
                printf("[action_live] : BDFACE_ACTION_LIVE_RIGHT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            auto val = api_temp->face_blur(img[5]);
            if (condition)
                printf("[action_live] : blur ====== %.2f\n", val.clarity[0]);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("Action_live_Blur time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t6 多线程测睡岗
    void thread_function_sleep(const std::string& instance) {
        gx_sleep_api* api_temp = new gx_sleep_api(glasssix::abi::string(CONFIG_PATH));
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "sleep1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_sleep(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[sleep] : lying_list = %d work_list = %d\n", val.lying_list.size(), val.work_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("sleep time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t7 多线程测抽烟
    void thread_function_smoke(const std::string& instance) {
        gx_smoke_api* api_temp = new gx_smoke_api(glasssix::abi::string(CONFIG_PATH));
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "smoke3.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smoke(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[smoke] : smoke_list = %d norm_list = %d\n", val.smoke_list.size(), val.norm_list.size());
                auto end      = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                // printf("smoke only  time = %lld microsecond\n", duration);
            } catch (const std::exception& ex) {
                auto end      = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                // printf("smoke error time = %lld microsecond\n", duration);
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        if (condition_time)
            printf("smoke time = %lld microsecond\n", duration);
        delete api_temp;
    }
    // t15 多线程测跌倒
    void thread_function_tumble(const std::string& instance) {
        gx_tumble_api* api_temp = new gx_tumble_api(glasssix::abi::string(CONFIG_PATH));
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_tumble(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf(
                        "[tumble] : tumble_list = %d stand_list = %d\n", val.tumble_list.size(), val.stand_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("tumble time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t11 多线程测车辆
    void thread_function_vehicle(const std::string& instance) {
        gx_vehicle_api* api_temp = new gx_vehicle_api(glasssix::abi::string(CONFIG_PATH));
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "vehicle.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_vehicle(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[vehicle] : vehicle_list = %d\n", val.vehicle_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("vehicle time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t18 多线程测徘徊
    void thread_function_wander(const std::string& instance) {
        gx_wander_api* api_temp = new gx_wander_api(glasssix::abi::string(CONFIG_PATH));
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "wander.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_wander(img, i, 1, 60);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition) {
                    printf("[wander] : wander_list = %d device =%d\n", val.person_info.size(), 1);
                    // printf("[wander] : wander_remove_id ans =%d\n",
                    // api_temp->wander_remove_id(val.person_info[0].id));
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        api_temp->wander_remove_library();
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("wander time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t21 多线程测越界
    void thread_function_wander_limit(const std::string& instance) {
        gx_wander_api* api_temp                = new gx_wander_api(glasssix::abi::string(CONFIG_PATH));
        gx_pedestrian_api* api_pedestrian_temp = new gx_pedestrian_api(glasssix::abi::string(CONFIG_PATH));
        int T                                  = TIMES;
        auto start                             = std::chrono::high_resolution_clock::now();
        const gx_img_api img1(abi::string(IMG_PATH) + "wander_limit1.png", static_cast<int>(1e9));
        const gx_img_api img2(abi::string(IMG_PATH) + "wander_limit2.png", static_cast<int>(1e9));
        auto post1 = api_pedestrian_temp->safe_production_pedestrian(img1);
        auto post2 = api_pedestrian_temp->safe_production_pedestrian(img2);
        for (int i = 0; i < T; i += 2) {
            try {
                auto val_1 = api_temp->safe_production_wander_limit(img1, i, 2, post1.person_list);
                auto val_2 = api_temp->safe_production_wander_limit(img2, i + 1, 2, post2.person_list);
                for (int j = 0; j < val_2.person_info.size(); ++j) {
                    if (condition) {
                        printf("[wander_limit] : segment: %d %d %d %d\n", val_2.segment_info[j].x1,
                            val_2.segment_info[j].x2, val_2.segment_info[j].y1, val_2.segment_info[j].y2);
                        printf("[wander_limit] : boxes:   %d %d %d %d\n", val_2.person_info[j].x1,
                            val_2.person_info[j].x2, val_2.person_info[j].y1, val_2.person_info[j].y2);
                    }
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition) {
            printf("[wander_limit] : %d\n", api_temp->wander_remove_library());
        }
        if (condition_time) {
            printf("wander_limit time = %lld microsecond\n", duration.count());
        }
        delete api_temp;
    }
    // t13 多线程测离岗
    void thread_function_leavepost(const std::string& instance) {
        gx_leavepost_api* api_temp = new gx_leavepost_api(glasssix::abi::string(CONFIG_PATH));
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "leavepost.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_leavepost(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[leavepost] : hat_list = %d\n", val.hat_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("leavepost time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t8 多线程测玩手机
    void thread_function_playphone(const std::string& instance) {
        gx_playphone_api* api_temp = new gx_playphone_api(glasssix::abi::string(CONFIG_PATH));
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
#if 0 // 这里必须要有表达式,不能省略
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "playphone.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[playphone] : playphone_list = %d norm_list = %d bodyerror_list = %d\n",
                        val.playphone_list.size(), val.norm_list.size(), val.bodyerror_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
#else // 测试要求进行多图片检测
        try {
            std::vector<std::string> v_img;
            for (auto enter : std::filesystem::directory_iterator(abi::string(IMG_PATH) + "playphone/trace/")) {
                if (enter.is_regular_file()) {
                    std::string exit{enter.path().string()};
                    v_img.push_back(exit);
                    std::cout << "Found " << exit << std::endl;

                    const gx_img_api img(abi::string(exit), static_cast<int>(1e9));
                    auto val             = api_temp->safe_production_playphone(img);
                    std::string fileName = enter.path().filename().string(); // 拿到图片名字(含后缀名) //也可以使用 fs::path(exit).filename().string()
                    std::string fileNamePre;
                    size_t lastDotPos = fileName.find_last_of(".");
                    // 如果找到 点 ,则截取前面的部分作为文件名
                    if (lastDotPos != std::string::npos) {
                        fileNamePre = fileName.substr(0, lastDotPos);
                        std::cout << "fileNamePre : " << fileNamePre << std::endl;
                    }
                    glasssix::write_json(instance, glasssix::json(val), true, false, fileNamePre);
                    if (1)
                        printf("[playphone] : image_name = %s playphone_list = %d norm_list = %d bodyerror_list = %d\n",
                            fileName.c_str(), val.playphone_list.size(), val.norm_list.size(),
                            val.bodyerror_list.size());
                }
            }
            for (auto exit : v_img) {
            }
        } catch (const std::exception& ex) {
            printf("error =  %s\n", ex.what());
        }
#endif
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("playphone time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t9 多线程测打电话
    void thread_function_onphone(const std::string& instance) {
        gx_onphone_api* api_temp         = new gx_onphone_api(glasssix::abi::string(CONFIG_PATH));
        gx_head_api* api_head_temp       = new gx_head_api(glasssix::abi::string(CONFIG_PATH));
        gx_posture_api* api_posture_temp = new gx_posture_api(glasssix::abi::string(CONFIG_PATH));
        const gx_img_api img(abi::string(IMG_PATH) + "onphone.png", static_cast<int>(1e9));
        auto val_head    = api_head_temp->safe_production_head(img);
        auto val_posture = api_posture_temp->safe_production_posture(img);
        int T            = TIMES;
        auto start       = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                auto val1 = api_temp->safe_production_onphone(img, val_head);
                auto val2 = api_temp->safe_production_onphone(img, val_posture);
                glasssix::write_json(instance + "_head", glasssix::json(val1));
                glasssix::write_json(instance + "_posture", glasssix::json(val2));
                if (condition) {
                    printf("[onphone] : head-> onphone_list = %d norm_list = %d\n", val1.onphone_list.size(),
                        val1.norm_list.size());
                    printf("[onphone] : post-> onphone_list = %d norm_list = %d\n", val2.onphone_list.size(),
                        val2.norm_list.size());
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("onphone time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t10 多线程测工服检测
    void thread_function_workcloth(const std::string& instance) {
        gx_workcloth_api* api_temp = new gx_workcloth_api(glasssix::abi::string(CONFIG_PATH));
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "workcloth.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_workcloth(img, 0);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[workcloth] : workcloth_list = %d\n", val.cloth_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("workcloth time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t12 多线程测行人检测
    void thread_function_pedestrian(const std::string& instance) {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api(glasssix::abi::string(CONFIG_PATH));
        int T                       = TIMES;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "pedestrian.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[pedestrian] : person_list = %d\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t16 多线程测攀爬
    void thread_function_climb(const std::string& instance) {
        gx_climb_api* api_temp = new gx_climb_api(glasssix::abi::string(CONFIG_PATH));
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf(
                        "[climb] : climb_list = %d normal_list = %d\n", val.climb_list.size(), val.normal_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("climb time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t17 多线程测聚众
    void thread_function_crowd(const std::string& instance) {
        gx_crowd_api* api_temp = new gx_crowd_api(glasssix::abi::string(CONFIG_PATH));
        auto start             = std::chrono::high_resolution_clock::now();
        int T                  = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "crowd.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_crowd(img, 5, 30, 0);
                if (val.head_list.size())
                    api_temp->crowd_remove_library(0);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[crowd] : head_list = %d\n", val.head_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition_time)
                printf("crowd time = %lld microsecond\n", duration.count());
        }
        delete api_temp;
    }
    // t23 多线程测偷电瓶
    void thread_function_batterypilferers(const std::string& instance) {
        gx_batterypilferers_api* api_temp = new gx_batterypilferers_api(glasssix::abi::string(CONFIG_PATH));
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        abi::vector<gx_img_api> img_list;
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_5.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_6.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_7.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_8.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_9.jpg", static_cast<int>(1e9)));

        for (int i = 0; i < T; ++i) {
            try {
                auto val = api_temp->safe_production_batterypilferers(img_list);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[batterypilferers] : steal_list =%d normal_list =%d\n", val.steal_list.size(),
                        val.normal_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("batterypilferers time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t19 多线程测打架斗殴
    void thread_function_fighting(const std::string& instance) {
        try {

            gx_fighting_api* api_temp = new gx_fighting_api(glasssix::abi::string(CONFIG_PATH));
            int T                     = TIMES;
            auto start                = std::chrono::high_resolution_clock::now();
            abi::vector<gx_img_api> img_list;
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_0th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_5th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_10th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_15th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_20th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_25th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_30th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_35th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_40th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "fighting/fight_45th.jpg", static_cast<int>(1e9)));
            for (int i = 0; i < T; ++i) {
                auto val = api_temp->safe_production_fighting(img_list, {0, 0, 1920, 1080});
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf(
                        "[fighting] : fight_list =%d normal_list =%d\n", val.fight_list.size(), val.normal_list.size());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition_time)
                printf("fighting time = %lld microsecond\n", duration.count());
            delete api_temp;
        } catch (const std::exception& ex) {
            printf("error =  %s\n", ex.what());
        }
    }
    // t20 多线程测姿态
    void thread_function_posture(const std::string& instance) {
        gx_posture_api* api_temp = new gx_posture_api(glasssix::abi::string(CONFIG_PATH));
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "posture.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_posture(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[posture] : score =%f category=%d\n", val[0].score, val[0].key_points.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("posture time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t24 多线程测定制灯光
    void thread_function_pump_light(const std::string& instance) {
        gx_pump_light_api* api_temp = new gx_pump_light_api(glasssix::abi::string(CONFIG_PATH));
        int T                       = TIMES;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/1.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{1269, 154}, pump_light_point{1385, 154},
                                 pump_light_point{1385, 225}, pump_light_point{1269, 225}});
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/3.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{726, 186}, pump_light_point{798, 186},
                                 pump_light_point{798, 247}, pump_light_point{726, 247}});
                    glasssix::write_json(instance, glasssix::json(val));
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/3_on.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{726, 186}, pump_light_point{798, 186},
                                 pump_light_point{798, 247}, pump_light_point{726, 247}});
                    glasssix::write_json(instance, glasssix::json(val));
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/7.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{639, 188}, pump_light_point{680, 188},
                                 pump_light_point{680, 230}, pump_light_point{639, 230}});
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/7.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{418, 258}, pump_light_point{418, 258},
                                 pump_light_point{466, 297}, pump_light_point{466, 297}});
                    glasssix::write_json(instance, glasssix::json(val));
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/7_on.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{639, 188}, pump_light_point{680, 188},
                                 pump_light_point{680, 230}, pump_light_point{639, 230}});
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/7_on.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{418, 258}, pump_light_point{418, 258},
                                 pump_light_point{466, 297}, pump_light_point{466, 297}});
                    glasssix::write_json(instance, glasssix::json(val));
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_light time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t25 多线程测定制天车工（反光衣安全帽）
    void thread_function_pump_vesthelmet(const std::string& instance) {
        gx_pump_vesthelmet_api* api_temp = new gx_pump_vesthelmet_api(glasssix::abi::string(CONFIG_PATH));
        int T                            = TIMES;
        auto start                       = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "tcg.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_vesthelmet(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    for (int i = 0; i < val.pump_vesthelmet_list.size(); i++)
                        printf("[pump_vesthelmet] : category = %d score = %.2f  \n",
                            val.pump_vesthelmet_list[i].category, val.pump_vesthelmet_list[i].score);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_vesthelmet time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t26 多线程测定制大门状态
    void thread_function_pump_gate_status(const std::string& instance) {
        gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(glasssix::abi::string(CONFIG_PATH));
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pump_gate_status.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_gate_status(img, 15);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[pump_gate_status] : %s  \n", val.c_str());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        //{
        //    auto list = find_file(abi::string(IMG_PATH) + "10/");
        //    for (int i = 0; i < list.size(); i++) {
        //        gx_img_api img(list[i], static_cast<int>(1e9));
        //        auto val = api_temp->safe_production_pump_gate_status(img,10);
        //        std::cout << list[i] << "\n";
        //        if (condition)
        //            printf("[pump_gate_status] : %s  \n", val.c_str());
        //    }
        //}
        //{
        //    auto list = find_file(abi::string(IMG_PATH) + "12/");
        //    for (int i = 0; i < list.size(); i++) {
        //        gx_img_api img(list[i], static_cast<int>(1e9));
        //        auto val = api_temp->safe_production_pump_gate_status(img, 12);
        //        std::cout << list[i] << "\n";
        //        if (condition)
        //            printf("[pump_gate_status] : %s  \n", val.c_str());
        //    }
        //}
        //{
        //    auto list = find_file(abi::string(IMG_PATH) + "15/");
        //    for (int i = 0; i < list.size(); i++) {
        //        gx_img_api img(list[i], static_cast<int>(1e9));
        //        auto val = api_temp->safe_production_pump_gate_status(img, 15);
        //        std::cout << list[i] << "\n";
        //        if (condition)
        //            printf("[pump_gate_status] : %s  \n", val.c_str());
        //    }
        //}
        //{
        //    auto list = find_file(abi::string(IMG_PATH) + "16/");
        //    for (int i = 0; i < list.size(); i++) {
        //        gx_img_api img(list[i], static_cast<int>(1e9));
        //        auto val = api_temp->safe_production_pump_gate_status(img, 16);
        //        std::cout << list[i] << "\n";
        //        if (condition)
        //            printf("[pump_gate_status] : %s  \n", val.c_str());
        //    }
        //}

        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_gate_status time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t27 多线程测定制泵顶行人
    void thread_function_pump_pumptop_person(const std::string& instance) {
        gx_pump_pumptop_person_api* api_temp = new gx_pump_pumptop_person_api(glasssix::abi::string(CONFIG_PATH));
        int T                                = TIMES;
        auto start                           = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                // gx_img_api img(abi::string(IMG_PATH) + "pumptop_person.jpg", static_cast<int>(1e9));
                gx_img_api img(abi::string(IMG_PATH) + "pump_pumptop_person.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_pumptop_person(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    if (val.persons_in_pumptop.size() > 0) {
                        printf("[pump_pumptop_person] : category = %d score = %.2f  \n",
                            val.persons_in_pumptop[0].category, val.persons_in_pumptop[0].score);
                    } else {
                        printf("[pump_pumptop_person] : category = %d score = %.2f  \n", 10, 10);
                    }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_pumptop_person time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t28 多线程测定制防护面罩
    void thread_function_pump_mask(const std::string& instance) {
        gx_pump_mask_api* api_temp = new gx_pump_mask_api(glasssix::abi::string(CONFIG_PATH));
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pump_mask.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_mask(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition) {
                    if (val.pump_head_list.size() > 0)
                        printf("[pump_mask] : category=%d\n", val.pump_head_list[0].category);
                    else
                        printf("[pump_mask] : category=%d\n", 10);
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_mask time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t29 多线程测定制泵顶安全帽
    void thread_function_pumptop_helmet(const std::string& instance) {
        glasssix::gx_pumptop_helmet_api* api_temp =
            new glasssix::gx_pumptop_helmet_api(glasssix::abi::string(CONFIG_PATH));
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(glasssix::abi::string(IMG_PATH) + "pumptop_helmet.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pumptop_helmet(img);
                glasssix::write_json(instance, glasssix::json(val));
                 //std::cout << glasssix::json::parse(val).dump() << "+++++++++\n";/这个有问题
                //std::cout << glasssix::json(val).dump() << "+++++++++\n";//这个正常
                //std::cout << glasssix::json(val) << "+++++++++\n";//正常
                //std::cout << " pumptop_helmet : " << val << std::endl;
                if (condition) {
                    if (val.person_list.size() > 0)
                        printf("[pumptop_helmet] : size = %d \n", 1);
                    else
                        printf("[pumptop_helmet] : size = %d \n", 0);
                }

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pumptop_helmet time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t30 多线程测定制泵业狭小空间（天车工吊装）
    void thread_function_pump_hoisting(const std::string& instance) {
        gx_pump_hoisting_api* api_temp = new gx_pump_hoisting_api(glasssix::abi::string(CONFIG_PATH));
        int T                          = TIMES;
        auto start                     = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img1(abi::string(IMG_PATH) + "pump_hoistring2.jpg", static_cast<int>(1e9));
                api_temp->safe_production_pump_hoisting(img1, 1);
                gx_img_api img2(abi::string(IMG_PATH) + "pump_hoistring1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_hoisting(img2, 1);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[pump_hoisting] : dangerous_region = %llu \n", val.dangerous_region.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_hoisting time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t31 多线程测定制泵业焊接
    void thread_function_pump_weld(const std::string& instance) {
        gx_pump_weld_api* api_temp = new gx_pump_weld_api(glasssix::abi::string(CONFIG_PATH));
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        abi::vector<gx_img_api> img_list;
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/0.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/1.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/5.jpg", static_cast<int>(1e9)));
        for (int i = 0; i < T; ++i) {
            try {
                auto val = api_temp->safe_production_pump_weld(img_list);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition) {
                    if (val.persons_weld.size() > 0)
                        printf("[pump_weld] : category=%d\n", val.persons_weld[0].category);
                    else
                        printf("[pump_weld] : category=%d\n", 10);
                }
#if 0
                for (int i = 0; i < val.persons_weld[0].weld_list.size(); ++i) {
                    std::cout << val.persons_weld[0].weld_list[i].x1 << std::endl;
                    std::cout << val.persons_weld[0].weld_list[i].y1 << std::endl;
                    std::cout << val.persons_weld[0].weld_list[i].x2 << std::endl;
                    std::cout << val.persons_weld[0].weld_list[i].y2 << std::endl;
                }
#endif
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_weld time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t32 多线程测人脸属性
    void thread_function_face_attributes(const std::string& instance) {
        gx_face_api* api_temp = new gx_face_api(glasssix::abi::string(CONFIG_PATH));
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "face_attributes.jpg", static_cast<int>(1e9));
                auto val = api_temp->face_attributes(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition && val.size())
                    printf("[faceattributes] : age=%d gender=%d glass=%d mask=%d\n", val[0].age, val[0].gender,
                        val[0].glass, val[0].mask);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("face_attributes time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

    // t33 多线程测定制工作状态
    void thread_function_pump_work_status(const std::string& instance) {
        gx_pump_work_status_api* api_temp = new gx_pump_work_status_api(glasssix::abi::string(CONFIG_PATH));
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        abi::vector<pump_work_status_point> polygon;
        polygon.emplace_back(pump_work_status_point{773, 407});
        polygon.emplace_back(pump_work_status_point{1072, 407});
        polygon.emplace_back(pump_work_status_point{1526, 1080});
        polygon.emplace_back(pump_work_status_point{895, 1080});
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pump_work_status.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_work_status(img, 1, polygon);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[pump_work_status] : %s \n", val.c_str());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }

        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_work_status time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

    // t34 多线程测翻越
    void thread_function_crossing(const std::string& instance) {
        gx_crossing_api* api_temp = new gx_crossing_api(glasssix::abi::string(CONFIG_PATH));
        int T                     = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                {
                    gx_img_api img(abi::string(IMG_PATH) + "crossing3.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
                    glasssix::write_json(instance, glasssix::json(val));
                    if (condition)
                        printf("[crossing3] : %llu \n", val.crossing_list.size());
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }

        delete api_temp;
    }

    // t35 多线程测行人min检测
    void thread_function_pedestrian_min(const std::string& instance) {
        gx_pedestrian_min_api* api_temp = new gx_pedestrian_min_api(glasssix::abi::string(CONFIG_PATH));
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "pedestrian_min.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian_min(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[pedestrian_min] : pedestrian_min_list = %d\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pedestrian_min time = %lld microsecond\n", duration.count());
        delete api_temp;
    }


    // t37 多线程测攀爬跌倒的攀爬
    void thread_function_climb_tumble_pedestrian_climb(const std::string& instance) {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(glasssix::abi::string(CONFIG_PATH));
        int T                                    = TIMES;
        auto start                               = std::chrono::high_resolution_clock::now();
        // auto list_ = find_file("/root/img/test/aa(2)/");
        // for (int i = 0; i < list_.size(); ++i) {
        //     std::cout << list_[i] << "\n";
        //     const gx_img_api img(list_[i], static_cast<int>(1e9));
        //     api_temp->safe_production_climb_tumble_pedestrian(img, 0,{});
        //     auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 0,{});
        // }

        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 0);
                glasssix::write_json(instance + "_climb", glasssix::json(val));
                if (condition)
                    printf("[climb_tumble_pedestrian:climb] : persion_list = %llu climb_list = %llu tumble_list = %llu "
                           "disabled_list = %llu other_list = %llu \n",
                        val.persion_list.size(), val.climb_list.size(), val.tumble_list.size(),
                        val.disabled_list.size(), val.other_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("climb_tumble_pedestrian_climb time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

    // t38 多线程测攀爬跌倒的跌倒
    void thread_function_climb_tumble_pedestrian_tumble(const std::string& instance) {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(glasssix::abi::string(CONFIG_PATH));
        int T                                    = TIMES;
        auto start                               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 1);
                glasssix::write_json(instance + "_tumble", glasssix::json(val));
                if (condition)
                    printf(
                        "[climb_tumble_pedestrian:tumble] : persion_list = %llu climb_list = %llu tumble_list = %llu "
                        "disabled_list = %llu other_list = %llu \n",
                        val.persion_list.size(), val.climb_list.size(), val.tumble_list.size(),
                        val.disabled_list.size(), val.other_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("climb_tumble_pedestrian_tumble time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t39 多线程测地铁异常宁梓骁的
    void thread_function_subway_anomaly_nzx(const std::string& instance) {
        gx_subway_anomaly_api* api_temp = new gx_subway_anomaly_api(glasssix::abi::string(CONFIG_PATH));
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();
        auto list_                      = find_file("/root/img/subway_anomaly_nzx/");
        for (int i = 0; i < list_.size(); ++i) {
            try {
                // std ::cout << list_[i] << "\n";
                const gx_img_api img(list_[i], static_cast<int>(1e9));
                auto val = api_temp->safe_production_subway_anomaly(img,
                    {subway_anomaly_roi{955, 560, 75, 175}, subway_anomaly_roi{750, 500, 535, 30}},
                    0); // x, y, width, height
                glasssix::write_json(instance + "_nzx", glasssix::json(val));
                if (condition)
                    printf("[subway_anomaly_nzx] : anomaly_status = %d\n", val.anomaly_status);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("subway_anomaly_nzx time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t40 多线程测地铁异常杨凡的
    void thread_function_subway_anomaly_yf(const std::string& instance) {
        gx_subway_anomaly_api* api_temp = new gx_subway_anomaly_api(glasssix::abi::string(CONFIG_PATH));
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();

        auto list_ = find_file("/root/img/subway_anomaly_nzx/");
        for (int i = 0; i < list_.size(); ++i) {
            // std::cout << list_[i] << "\n";
            const gx_img_api img(list_[i], static_cast<int>(1e9));
            auto val = api_temp->safe_production_subway_anomaly(
                img, {subway_anomaly_roi{697, 265, 74, 401}}, 1); // x, y, width, height
            glasssix::write_json(instance + "_yf", glasssix::json(val));
            if (condition)
                printf("[subway_anomaly_yf] : anomaly_status = %d\n", val.anomaly_status);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("subway_anomaly_yf time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

        // t41 多线程测警服
    void thread_function_policeuniform(const std::string& instance) {
        gx_policeuniform_api* api_temp = new gx_policeuniform_api(glasssix::abi::string(CONFIG_PATH));
        int T                          = TIMES;
        auto start                     = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "policeuniform.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_policeuniform(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (condition)
                    printf("[policeuniform] : policeuniform_list = %d\n", val.without_policeuniform_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("policeuniform time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
} // namespace glasssix

namespace glasssix {
    config* _config = nullptr;
    //std::vector<std::string> find_file(fs::path folder_path) {
    //    std::vector<std::string> ans_list;
    //    for (const auto& entry : fs::directory_iterator(folder_path)) {
    //        if (entry.is_regular_file()) {
    //            std::string temp(entry.path().filename());
    //            ans_list.emplace_back(temp);
    //        }
    //    }
    //    return ans_list;
    //}
    void init()//初始化 _config
    {
        if (_config == nullptr)
        {
            _config = new config(glasssix::abi::string(CONFIG_PATH));
        }
    }
}
int main(int argc, char** argv) {
    /* C++ 接口测试*/
    std::jthread t[100];
    std::vector<std::string> plugins{"plugin_register", "vision_service", "selene", "longinus", "romancia", "damocles",
        "irisviel", "face_attributes", "head", "posture", "pedestrian"};
    try {
        printf("result result result ~~~~ \n");
        glasssix::init();
        TIMES        = glasssix::_config->_configure_directory.cycle_num;
        bool iscycle = (TIMES) <= 1 ? 0 : 1;
        if (!TIMES++)
            ;
        std::cout << " config : " << glasssix::_config->_configure_directory.license_directory << " ; TIMES = " << TIMES
                  << std::endl;
        std::cout << "plugin_configure.json : " << glasssix::_config->protocols_list << std::endl;
        //开始读取插件表并运行相关算法
        auto plugin = glasssix::_config->protocols_list["plugin_list"];
        for (int i = 0; i < plugin.size(); ++i)
        {
            std::string temp_str = plugin[i];
            if (std::find(plugins.begin(), plugins.end(), temp_str) != plugins.end())
                continue;
            if (temp_str == "wander")
                if (iscycle == 0)
                    glasssix::thread_function_wander(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_wander, temp_str));
            if (temp_str == "flame")
                if (iscycle == 0)
                    glasssix::thread_function_flame(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_flame, temp_str));
            if (temp_str == "refvest")
                if (iscycle == 0)
                    glasssix::thread_function_refvest(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_refvest, temp_str));
            if (temp_str == "leavepost")
                if (iscycle == 0)
                    glasssix::thread_function_leavepost(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_leavepost, temp_str));
            if (temp_str == "sleep")
                if (iscycle == 0)
                    glasssix::thread_function_sleep(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_sleep, temp_str));
            if (temp_str == "smoke")
                if (iscycle == 0)
                    glasssix::thread_function_smoke(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_smoke, temp_str));
            if (temp_str == "playphone")
                if (iscycle == 0)
                    glasssix::thread_function_playphone(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_playphone, temp_str));
            if (temp_str == "onphone")
                if (iscycle == 0)
                    glasssix::thread_function_onphone(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_onphone, temp_str));
            if (temp_str == "workcloth")
                if (iscycle == 0)
                    glasssix::thread_function_workcloth(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_workcloth, temp_str));
            if (temp_str == "vehicle")
                if (iscycle == 0)
                    glasssix::thread_function_vehicle(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_vehicle, temp_str));
            if (temp_str == "smog")
                if (iscycle == 0)
                    glasssix::thread_function_smog(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_smog, temp_str));
            if (temp_str == "helmet")
                if (iscycle == 0)
                    glasssix::thread_function_helmet(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_helmet, temp_str));
            if (temp_str == "fighting")
                if (iscycle == 0)
                    glasssix::thread_function_fighting(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_fighting, temp_str));
            if (temp_str == "crowd")
                if (iscycle == 0)
                    glasssix::thread_function_crowd(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_crowd, temp_str));
            if (temp_str == "crossing")
                if (iscycle == 0)
                    glasssix::thread_function_crossing(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_crossing, temp_str));
            if (temp_str == "batterypilferers")
                if (iscycle == 0)
                    glasssix::thread_function_batterypilferers(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_batterypilferers, temp_str));
            if (temp_str == "pedestrian_min")
                if (iscycle == 0)
                    glasssix::thread_function_pedestrian_min(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pedestrian_min, temp_str));
            if (temp_str == "climb_tumble_pedestrian")
                if (iscycle == 0)
                {
                    glasssix::thread_function_climb_tumble_pedestrian_climb(temp_str);
                    glasssix::thread_function_climb_tumble_pedestrian_tumble(temp_str);
                }
                else
                {
                    (t[i] = std::jthread(glasssix::thread_function_climb_tumble_pedestrian_climb, temp_str));
                    (t[99] = std::jthread(glasssix::thread_function_climb_tumble_pedestrian_tumble, temp_str));
                }
            if (temp_str == "subway_anomaly")
                if (iscycle == 0) {
                    glasssix::thread_function_subway_anomaly_nzx(temp_str);
                    glasssix::thread_function_subway_anomaly_yf(temp_str);
                }
                else
                {
                    (t[i] = std::jthread(glasssix::thread_function_subway_anomaly_nzx, temp_str));
                    (t[98] = std::jthread(glasssix::thread_function_subway_anomaly_yf, temp_str));
                }
            if (temp_str == "policeuniform")
                if (iscycle == 0) {
                    glasssix::thread_function_policeuniform(temp_str);
                } else {
                    (t[i] = std::jthread(glasssix::thread_function_policeuniform, temp_str));
                }
            if (temp_str == "pump_light")
                if (iscycle == 0)
                    glasssix::thread_function_pump_light(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_light, temp_str));
            if (temp_str == "pump_vesthelmet")
                if (iscycle == 0)
                    glasssix::thread_function_pump_vesthelmet(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_vesthelmet, temp_str));
            if (temp_str == "pump_gate_status")
                if (iscycle == 0)
                    glasssix::thread_function_pump_gate_status(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_gate_status, temp_str));
            if (temp_str == "pump_pumptop_person")
                if (iscycle == 0)
                    glasssix::thread_function_pump_pumptop_person(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_pumptop_person, temp_str));
            if (temp_str == "pump_mask")
                if (iscycle == 0)
                    glasssix::thread_function_pump_mask(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_mask, temp_str));
            if (temp_str == "pumptop_helmet")
                if (iscycle == 0)
                    glasssix::thread_function_pumptop_helmet(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pumptop_helmet, temp_str));
            if (temp_str == "pump_hoisting")
                if (iscycle == 0)
                    glasssix::thread_function_pump_hoisting(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_hoisting, temp_str));
            if (temp_str == "pump_weld")
                if (iscycle == 0)
                    glasssix::thread_function_pump_weld(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_weld, temp_str));
            if (temp_str == "pump_work_status")
                if (iscycle == 0)
                    glasssix::thread_function_pump_work_status(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pump_work_status, temp_str));

        }

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::cout << "\nthe test is over ......." << std::endl;
    std::getchar();
    return 0;
}