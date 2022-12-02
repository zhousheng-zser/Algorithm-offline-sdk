#include "config.h"

#include "config_validation.hpp"

#include <proxy/proxy.h>

namespace glasssix::face {
    config::config() {
        set_detect();
        set_track();
        set_blur();
        set_action_live();
        set_feature();
        set_face_user();
    }

    glasssix::json config::read_json_file(abi::string path) {
        glasssix::json temp;
        std::ifstream(path.c_str()) >> temp;
        return temp;
    }
    void config::set_detect() {
        glasssix::json temp;
        temp = read_json_file("./config/detect.json");
        temp.get_to(_detect_config);
    }
    void config::set_track() {
        glasssix::json temp;
        temp = read_json_file("./config/track.json");
        temp.get_to(_track_config);
    }
    void config::set_blur() {
        glasssix::json temp;
        temp = read_json_file("./config/blur.json");
        temp.get_to(_blur_config);
    }
    void config::set_action_live() {
        glasssix::json temp;
        temp = read_json_file("./config/action_live.json");
        temp.get_to(_action_live_config);
    }
    void config::set_feature() {
        glasssix::json temp;
        temp = read_json_file("./config/feature.json");
        temp.get_to(_feature_config);
    }
    void config::set_face_user() {
        glasssix::json temp;
        temp = read_json_file("./config/face_user.json");
        temp.get_to(_face_user_config);
    }


} // namespace glasssix::face