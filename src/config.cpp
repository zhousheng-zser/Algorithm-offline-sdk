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
    void config::set_detect(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/detect.json");
        temp.get_to(_detect_config);
        detect_is_load = true;
    }
    void config::set_track(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/track.json");
        temp.get_to(_track_config);
        track_is_load = true;
    }
    void config::set_blur(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/blur.json");
        temp.get_to(_blur_config);
        blur_is_load = true;
    }
    void config::set_attributes(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/attributes.json");
        temp.get_to(_attributes_config);
        attributes_is_load = true;
    }
    void config::set_action_live(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/action_live.json");
        temp.get_to(_action_live_config);
        action_live_is_load = true;
    }
    void config::set_feature(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/feature.json");
        temp.get_to(_feature_config);
        feature_is_load = true;
    }
    void config::set_face_user(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/face_user.json");
        temp.get_to(_face_user_config);
        _face_user_config.working_directory = path + "/../" + _face_user_config.working_directory;
        face_user_is_load = true;
    }
    void config::set_climb(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/climb.json");
        temp.get_to(_climb_config);
        climb_is_load = true;
    }
    void config::set_climb_tumble_pedestrian(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/climb_tumble_pedestrian.json");
        temp.get_to(_climb_tumble_pedestrian_config);
        climb_tumble_pedestrian_is_load = true;
    }
    void config::set_crowd(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/crowd.json");
        temp.get_to(_crowd_config);
        crowd_is_load = true;
    }
    void config::set_crossing(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/crossing.json");
        temp.get_to(_crossing_config);
        crossing_is_load = true;
    }
    void config::set_batterypilferers(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/batterypilferers.json");
        temp.get_to(_batterypilferers_config);
        batterypilferers_is_load = true;
    }
    void config::set_pump_weld(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_weld.json");
        temp.get_to(_pump_weld_config);
        pump_weld_is_load = true;
    }
    void config::set_fighting(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/fighting.json");
        temp.get_to(_fighting_config);
        fighting_is_load = true;
    }
    void config::set_flame(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/flame.json");
        temp.get_to(_flame_config);
        flame_is_load = true;
    }
    void config::set_pump_vesthelmet(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_vesthelmet.json");
        temp.get_to(_pump_vesthelmet_config);
        pump_vesthelmet_is_load = true;
    }
    void config::set_pumptop_helmet(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pumptop_helmet.json");
        temp.get_to(_pumptop_helmet_config);
        pumptop_helmet_is_load = true;
    }
    void config::set_pump_mask(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_mask.json");
        temp.get_to(_pump_mask_config);
        pump_mask_is_load = true;
    }
    void config::set_pump_hoisting(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_hoisting.json");
        temp.get_to(_pump_hoisting_config);
        pump_hoisting_is_load = true;
    }
    void config::set_pump_gate_status(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_gate_status.json");
        temp.get_to(_pump_gate_status_config);
        pump_gate_status_is_load = true;
    }
    void config::set_pump_light(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_light.json");
        temp.get_to(_pump_light_config);
        pump_light_is_load = true;
    }
    void config::set_pump_work_status(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_work_status.json");
        temp.get_to(_pump_work_status_config);
        pump_work_status_is_load = true;
    }
    void config::set_smog(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/smog.json");
        temp.get_to(_smog_config);
        smog_is_load = true;
    }
    void config::set_helmet(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/helmet.json");
        temp.get_to(_helmet_config);
        helmet_is_load = true;
    }
    void config::set_refvest(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/refvest.json");
        temp.get_to(_refvest_config);
        refvest_is_load = true;
    }
    void config::set_sleep(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/sleep.json");
        temp.get_to(_sleep_config);
        sleep_is_load = true;
    }
    void config::set_smoke(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/smoke.json");
        temp.get_to(_smoke_config);
        smoke_is_load = true;
    }
    void config::set_tumble(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/tumble.json");
        temp.get_to(_tumble_config);
        tumble_is_load = true;
    }
    void config::set_vehicle(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/vehicle.json");
        temp.get_to(_vehicle_config);
        vehicle_is_load = true;
    }
    void config::set_wander(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/wander.json");
        temp.get_to(_wander_config);
        wander_is_load = true;
    }
    void config::set_wander_limit(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/wander_limit.json");
        temp.get_to(_wander_limit_config);
        wander_limit_is_load = true;
    }
    void config::set_pump_pumptop_person(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pump_pumptop_person.json");
        temp.get_to(_pump_pumptop_person_config);
        pump_pumptop_person_is_load = true; 
    }
    void config::set_policeuniform(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/policeuniform.json");
        temp.get_to(_policeuniform_config);
        policeuniform_is_load = true;
    }
    void config::set_leavepost(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/leavepost.json");
        temp.get_to(_leavepost_config);
        leavepost_is_load = true;
    }
    void config::set_onphone(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/onphone.json");
        temp.get_to(_onphone_config);
        onphone_is_load = true;
    }
    void config::set_playphone(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/playphone.json");
        temp.get_to(_playphone_config);
        playphone_is_load = true;
    }
    void config::set_workcloth(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/workcloth.json");
        temp.get_to(_workcloth_config);
        workcloth_is_load = true;
    }
    void config::set_pedestrian(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pedestrian.json");
        temp.get_to(_pedestrian_config);
        pedestrian_is_load = true;
    }
    void config::set_pedestrian_min(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/pedestrian_min.json");
        temp.get_to(_pedestrian_min_config);
        pedestrian_min_is_load = true;
    }
    void config::set_subway_anomaly(const abi::string& path) {
        glasssix::json temp;
        temp = read_json_file(path + "/subway_anomaly.json");
        temp.get_to(_subway_anomaly_config);
        subway_anomaly_is_load = true;
    }
} // namespace glasssix