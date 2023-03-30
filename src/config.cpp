#include "config.hpp"

#include "config_validation.hpp"

namespace glasssix::face {
    config::config() {
        set_configure_directory();
        set_detect();
        set_track();
        set_blur();
        set_action_live();
        set_feature();
        set_face_user();
    }
    config::config(const abi::string &config ) {
        set_configure_directory(config);
        set_detect(config);
        set_track(config);
        set_blur(config);
        set_action_live(config);
        set_feature(config);
        set_face_user(config);
    }

    glasssix::json config::read_json_file(const abi::string& path) {
        glasssix::json temp;
        std::ifstream(path.c_str()) >> temp;
        return temp;
    }
    void config::set_configure_directory(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path +"/configure_directory.json");
        temp.get_to(_configure_directory);
    }
    void config::set_detect(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/detect.json");
        temp.get_to(_detect_config);
    }
    void config::set_track(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/track.json");
        temp.get_to(_track_config);
    }
    void config::set_blur(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/blur.json");
        temp.get_to(_blur_config);
    }
    void config::set_action_live(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/action_live.json");
        temp.get_to(_action_live_config);
    }
    void config::set_feature(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/feature.json");
        temp.get_to(_feature_config);
    }
    void config::set_face_user(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path  + "/face_user.json");
        temp.get_to(_face_user_config);
    }
} // namespace glasssix::face