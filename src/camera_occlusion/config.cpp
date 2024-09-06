#include "config.hpp"
#include "nlohmann/json.hpp"
#include <fstream>

using namespace nlohmann;
namespace glasssix {

    config::config() {
        _path = "./config";
        set_configure_directory(_path);
        set_camera_occlusion(_path);
    }
    config::config(const std::string& path) {
        _path = path;
        set_configure_directory(_path);
        set_camera_occlusion(_path);
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

    void config::set_camera_occlusion(const std::string& path) {
        std::ifstream lic_dir(path + "/camera_occlusion.json");
        if (!lic_dir.is_open())
            throw std::runtime_error(std::string("Error: camera_occlusion.json:directory =") + path + std::string("/camera_occlusion.json"));

        json temp;
        std::ifstream(path + "/camera_occlusion.json") >> temp;
        _camera_occlusion_config = temp.get<camera_occlusion_config>();
        camera_occlusion_is_load = true;
    }

}