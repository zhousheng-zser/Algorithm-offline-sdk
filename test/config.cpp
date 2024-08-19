#include "config.hpp"
namespace glasssix {
    config::config() {
        _path = "./config";
        set_configure_directory(_path);
    }
    config::config(const abi::string& path) {
        _path = path;
        set_configure_directory(_path);
    }

    glasssix::json config::read_json_file(const abi::string& path) {
        glasssix::json temp;
        std::ifstream(path.c_str()) >> temp;
        return temp;
    }
    void config::set_configure_directory(abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/configure_directory.json");
        temp.get_to(_configure_directory);
        std::ifstream lic_dir(_configure_directory.license_directory.c_str());
        if (!lic_dir.is_open())
            throw source_code_aware_runtime_error(
                U8("Error: configure_directory.json:license_directory =") + _configure_directory.license_directory);

        _configure_directory.models_directory = path + "/../" + _configure_directory.models_directory;
        std::ifstream mod_dir(_configure_directory.models_directory.c_str());
        if (!mod_dir.is_open())
            throw source_code_aware_runtime_error(
                U8("Error: configure_directory.json:models_directory =") + _configure_directory.models_directory);

        _configure_directory.directory = path + "/../" + _configure_directory.directory;
        std::ifstream dir(_configure_directory.directory.c_str());
        if (!dir.is_open())
            throw source_code_aware_runtime_error(
                U8("Error: configure_directory.json:directory =") + _configure_directory.directory);
        protocols_list = nlohmann::json::parse(dir);

        _configure_directory.dump_img_directory = path + "/../" + _configure_directory.dump_img_directory;
        std::ifstream dump_dir(_configure_directory.dump_img_directory.c_str());
        if (!dump_dir.is_open())
            throw source_code_aware_runtime_error(
                U8("Error: configure_directory.json:dump_img_directory =") + _configure_directory.dump_img_directory);

        configure_directory_is_load = true;
    }
}