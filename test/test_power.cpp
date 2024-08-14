#include "head_require.h"
#include "config.hpp"
// static const abi::string CONFIG_PATH = "/root/install/glasssix-offline-sdk/config";// 编译识别不了 abi
static const std::string CONFIG_PATH_  = "/root/install/glasssix-offline-sdk_zj/config";// 编译识别不了 abi
static std::string OUTPUT_DIR    = "results/";
static glasssix::abi::string IMG_PATH_ = "/root/img/";
static int cycle            = 1;
namespace fs = std::filesystem;
#include<vector>
#include<string>
#include<fstream>
namespace glasssix {
    //主要一些重要的函数
    //写入json文件
    void write_json(std::string instance, glasssix::json data, bool is_multi = false, bool is_video = false,
        std::string multi_file = "")
    {
        std::string path          = CONFIG_PATH_ + "/../" + OUTPUT_DIR + "correct/" + instance + "/";
        std::string path_fault    = CONFIG_PATH_ + "/../" + OUTPUT_DIR + "fault/" + instance + "/";
        std::string path_warning  = CONFIG_PATH_ + "/../" + OUTPUT_DIR + "warning/" + instance + "/";
        std::string filename= path + instance + ".json";//绝对路径名
        std::string instance_name = instance + "_" + multi_file;
        if (is_multi) {
            filename = path + instance_name + ".json";
        }

        // 检查目录是否存在,文件是否存在
        // 创建目录（包括父目录）
        if (!std::filesystem::exists(path)) {
            std::filesystem::create_directories(path);
        }
        if (!std::filesystem::exists(path_fault)) {
            std::filesystem::create_directories(path_fault);
        }
        if (!std::filesystem::exists(path_warning)) {
            std::filesystem::create_directories(path_warning);
        }
        std::string out_path{};
        if (std::filesystem::exists(filename)) // 先读取,用来比较
        {
            std::ifstream inputFile(filename);
            if(!inputFile.is_open())
                return;
            //// 创建一个字符串流
            //std::ostringstream oss;
            //// 将文件内容读取到字符串流中
            //oss << inputFile.rdbuf(); // 读取整个文件的内容
            //// 获取字符串
            //std::string fileContent = oss.str();
            //auto old_data           = glasssix::json(fileContent);
            glasssix::json old_data;
            try {
                // 使用 peek() 检查文件的第一个字符是否到达文件结尾
                if (!(inputFile.peek() == std::ifstream::traits_type::eof()))
                inputFile >> old_data;
                //比较结果
                std::cout << "file image: " << instance_name << std::endl;
                if (instance == "playphone") {
                    std::cout << "old_data: " << old_data["playphone_list"].size() << " ";
                    std::cout << "new_data: " << data["playphone_list"].size() << " ";
                    if (data["playphone_list"].size() <= old_data["playphone_list"].size()) {
                        std::cout << "warning : " << instance << std::endl;
                        path = path_warning;
                    }
                    if (data["playphone_list"].size() == 0) {
                        std::cout << "fault : " << instance << std::endl;
                        path = path_fault;
                    }
                }
                if (instance == "pumptop_helmet") {
                    std::cout << "old_data: " << old_data["person_list"].size() << " ";
                    std::cout << "new_data: " << data["person_list"].size() << " ";
                }

            } catch (const glasssix::json::parse_error& e) {
                std::cerr << "JSON parse error: " << e.what() << std::endl;
                return;
            }

        }
        filename = path + instance_name + ".json";
        ;
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
}

namespace glasssix {
    // t8 多线程测玩手机
    void thread_function_playphone(std::string instance) {
        gx_playphone_api* api_temp = new gx_playphone_api(glasssix::abi::string(CONFIG_PATH_));
        int T                      = cycle;
        auto start                 = std::chrono::high_resolution_clock::now();
#if 0 // 这里必须要有表达式,不能省略
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH_) + "playphone.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
                glasssix::write_json(instance, glasssix::json(val));
                if (1)
                    printf("[playphone] : playphone_list = %d norm_list = %d bodyerror_list = %d\n",
                        val.playphone_list.size(), val.norm_list.size(), val.bodyerror_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
#else // 测试要求进行多图片检测
        try {
            std::vector<std::string> v_img;
            for (auto enter : std::filesystem::directory_iterator(abi::string(IMG_PATH_) + "playphone/trace/")) {
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

        delete api_temp;
    }
    // t29 多线程测定制泵顶安全帽
    void thread_function_pumptop_helmet(std::string instance) {
        glasssix::gx_pumptop_helmet_api* api_temp =
            new glasssix::gx_pumptop_helmet_api(glasssix::abi::string(CONFIG_PATH_));
        int T                           = cycle;
        auto start                      = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(glasssix::abi::string(IMG_PATH_) + "pumptop_helmet.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pumptop_helmet(img);
                glasssix::write_json(instance, glasssix::json(val));
                 //std::cout << glasssix::json::parse(val).dump() << "+++++++++\n";/这个有问题
                //std::cout << glasssix::json(val).dump() << "+++++++++\n";//这个正常
                std::cout << glasssix::json(val) << "+++++++++\n";//正常
                //std::cout << " pumptop_helmet : " << val << std::endl;
                if (1) {
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
        if (1)
            printf("pumptop_helmet time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

}

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
            _config = new config(glasssix::abi::string(CONFIG_PATH_));
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
        cycle        = glasssix::_config->_configure_directory.cycle_num;
        bool iscycle = (cycle) <= 1 ? 0 : 1;
        std::cout << " config : " << glasssix::_config->_configure_directory.license_directory << std::endl;
        std::cout << "plugin_configure.json : " << glasssix::_config->protocols_list << std::endl;
        //开始读取插件表并运行相关算法
        auto plugin = glasssix::_config->protocols_list["plugin_list"];
        for (int i = 0; i < plugin.size(); ++i)
        {
            std::string temp_str = plugin[i];
            if (std::find(plugins.begin(), plugins.end(), temp_str) != plugins.end())
                continue;
            if (temp_str == "playphone")
                if (iscycle == 0)
                    glasssix::thread_function_playphone(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_playphone, temp_str));
            if (temp_str == "pumptop_helmet")
                if (iscycle == 0)
                    glasssix::thread_function_pumptop_helmet(temp_str);
                else
                    (t[i] = std::jthread(glasssix::thread_function_pumptop_helmet, temp_str));


        }
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}