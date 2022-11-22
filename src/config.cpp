#include <config.h>

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
        printf("临时打印 看看效果  :%s\n", temp.dump().c_str());
        return temp;
    }
    void config::set_detect() {
        glasssix::json temp;
        temp= read_json_file("./config/detect.json");
        temp.get_to(_detect_config);
        //_detect_config.models_directory = temp["models_directory"].get<abi::string>();
        //_detect_config.device           = temp["device"].get<int>();
        //_detect_config.min_size         = temp["min_size"].get<int>();
        //_detect_config.threshold        = temp["threshold"].get<float>();
        //_detect_config.format           = temp["format"].get<int>();
        //_detect_config.do_attributing   = temp["do_attributing"].get<bool>();
    }
    void config::set_track() {
        glasssix::json temp;
        temp= read_json_file("./config/track.json");
        temp.get_to(_track_config);
        //_track_config.detect_intv_before_track = temp["detect_intv_before_track"].get<int>();
        //_track_config.detect_intv_during_track = temp["detect_intv_during_track"].get<int>();
    }
    void config::set_blur() {
        glasssix::json temp;
        temp = read_json_file("./config/blur.json");
        temp.get_to(_blur_config);
        //_blur_config.models_directory = temp["models_directory"].get<abi::string>();
        //_blur_config.device           = temp["device"].get<int>();
        //_blur_config.format           = temp["format"].get<int>();
    }
    void config::set_action_live() {
        glasssix::json temp;
        temp = read_json_file("./config/action_live.json");
        temp.get_to(_action_live_config);
        //_action_live_config.models_directory = temp["models_directory"].get<abi::string>();
        //_action_live_config.device           = temp["device"].get<int>();
        //_action_live_config.use_int8         = temp["use_int8"].get<bool>();
        //_action_live_config.format           = temp["format"].get<int>();
    }
    void config::set_feature() {
        glasssix::json temp;
        temp = read_json_file("./config/feature.json");
        temp.get_to(_feature_config);
        //_feature_config.models_directory = temp["models_directory"].get<abi::string>();
        //_feature_config.device           = temp["device"].get<int>();
        //_feature_config.use_int8         = temp["use_int8"].get<bool>();
        //_feature_config.format           = temp["format"].get<int>();
        //_feature_config.model_type       = temp["model_type"].get<int>();
        //_feature_config.dimension        = temp["dimension"].get<int>();
    }
    void config::set_face_user() {
        glasssix::json temp;
        temp = read_json_file("./config/face_user.json");
        temp.get_to(_face_user_config);
        //_face_user_config.working_directory      = temp["working_directory"].get<abi::string>();
        //_face_user_config.working_directory_mask = temp["working_directory_mask"].get<abi::string>();
        //_face_user_config.dimension              = temp["dimension"].get<int>();
    }


} // namespace glasssix::face