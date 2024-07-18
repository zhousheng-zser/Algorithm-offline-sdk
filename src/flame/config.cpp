#include "config.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace nlohmann;
namespace glasssix {

    config::config() {
        _path = "./config";
        set_configure_directory(_path);
        set_flame(_path);
        set_thread_pool_num(_path);
    }
    config::config(const std::string& path) {
        _path = path;
        set_configure_directory(_path);
        set_flame(_path);
        set_thread_pool_num(_path);
    }
    void config::set_configure_directory(std::string& path) {
        json temp;
        std::ifstream(path + "/configure_directory.json") >> temp;
        _configure_directory = temp.get<configure_directory>();
        std::ifstream lic_dir(_configure_directory.license_directory.c_str());
        if (!lic_dir.is_open())
            throw std::runtime_error(
                std::string("Error: configure_directory.json:license_directory =") + _configure_directory.license_directory);

        _configure_directory.models_directory = path + "/../" + _configure_directory.models_directory;
        std::ifstream mod_dir(_configure_directory.models_directory.c_str());
        if (!mod_dir.is_open())
            throw std::runtime_error(std::string("Error: configure_directory.json:models_directory =")
                                     + _configure_directory.models_directory);

        _configure_directory.directory = path + "/../" + _configure_directory.directory;
        std::ifstream dir(_configure_directory.directory.c_str());
        if (!dir.is_open())
            throw std::runtime_error(
                std::string("Error: configure_directory.json:directory =") + _configure_directory.directory);

        _configure_directory.dump_img_directory = path + "/../" + _configure_directory.dump_img_directory;
        std::ifstream dump_dir(_configure_directory.dump_img_directory.c_str());
        if (!dump_dir.is_open())
            throw std::runtime_error(std::string("Error: configure_directory.json:dump_img_directory =")
                                     + _configure_directory.dump_img_directory);
    }

    void config::set_flame(const std::string& path) {
        std::ifstream lic_dir(path + "/flame.json");
        if (!lic_dir.is_open())
            throw std::runtime_error(std::string("Error: flame.json:directory =") + path + std::string("/flame.json"));

        json temp;
        std::ifstream(path + "/flame.json") >> temp;
        _flame_config = temp.get<flame_config>();
        flame_is_load = true;
    }
    void config::set_thread_pool_num(const std::string& path) {
        std::ifstream lic_dir(path + "/thread_pool_num.json");
        if (!lic_dir.is_open())
            throw std::runtime_error(
                std::string("Error: thread_pool_num.json:directory =") + path + std::string("/thread_pool_num.json"));
        thread_pool_val = 1;
        try {
            json temp;
            lic_dir >> temp;
            thread_pool_num list_ = temp.get<thread_pool_num>();
            for (thread_pool_num::algo& val : list_.algo_list) {
                if (val.protocols == "flame")
                    thread_pool_val = val.num;
            }
        } catch (...) {
            printf("Warning:flame:thread pool num is set to 1\n");
        }
    }

}