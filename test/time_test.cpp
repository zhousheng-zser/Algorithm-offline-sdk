#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <thread>

#include <g6/json_extensions.hpp>

#include <gx_api.hpp>
#include <gx_batterypilferers_api.hpp>
#include <gx_climb_api.hpp>
#include <gx_climb_tumble_pedestrian_api.hpp>
#include <gx_crossing_api.hpp>
#include <gx_crowd_api.hpp>
#include <gx_face_api.hpp>
#include <gx_fighting_api.hpp>
#include <gx_flame_api.hpp>
#include <gx_head_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_leavepost_api.hpp>
#include <gx_onphone_api.hpp>
#include <gx_pedestrian_api.hpp>
#include <gx_pedestrian_min_api.hpp>
#include <gx_playphone_api.hpp>
#include <gx_posture_api.hpp>
#include <gx_pump_gate_status_api.hpp>
#include <gx_pump_hoisting_api.hpp>
#include <gx_pump_light_api.hpp>
#include <gx_pump_mask_api.hpp>
#include <gx_pump_pumptop_person_api.hpp>
#include <gx_pump_vesthelmet_api.hpp>
#include <gx_pump_weld_api.hpp>
#include <gx_pump_work_status_api.hpp>
#include <gx_pumptop_helmet_api.hpp>
#include <gx_refvest_api.hpp>
#include <gx_sleep_api.hpp>
#include <gx_smog_api.hpp>
#include <gx_smoke_api.hpp>
#include <gx_subway_anomaly_api.hpp>
#include <gx_tumble_api.hpp>
#include <gx_vehicle_api.hpp>
#include <gx_wander_api.hpp>
#include <gx_workcloth_api.hpp>
#include <opencv2/opencv.hpp>
using namespace glasssix;
#if SOPHON
static const abi::string CONFIG_PATH = "config";
#else
static const abi::string CONFIG_PATH = "/root/install/glasssix-offline-sdk/config";
#endif
static std::string IMG_PATH = "/root/img/";
#define TIMES 10
namespace fs = std::filesystem;
namespace glasssix {
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
} // namespace glasssix

std::string log_path = "runtime_" + [] {
    auto now        = std::chrono::high_resolution_clock::now();
    auto time_point = std::chrono::system_clock::now();
    auto time_t     = std::chrono::system_clock::to_time_t(time_point);
    std::string buffer;
    buffer.resize(80); // 分配足够的空间
    std::strftime(&buffer[0], buffer.size(), "%Y_%m_%d_%H_%M_%S.log", std::localtime(&time_t));
    return buffer;
    // 输出日期和时间
}();

// 调试代码
namespace glasssix {
    void time_test_helmet() {
        gx_helmet_api* api_temp = new gx_helmet_api(CONFIG_PATH);
        gx_head_api* api_head   = new gx_head_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "helmet.jpg", static_cast<int>(1e9));
        auto head_info_list = api_head->safe_production_head(img);
        api_temp->safe_production_helmet(img, head_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            auto val = api_temp->safe_production_helmet(img, head_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "helmet time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_head;
    }
    void time_test_head() {
        gx_head_api* api_temp = new gx_head_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "head.jpg", static_cast<int>(1e9));
        api_temp->safe_production_head(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_head(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "head time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_flame() {
        gx_flame_api* api_temp = new gx_flame_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "flame.jpg", static_cast<int>(1e9));
        api_temp->safe_production_flame(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_flame(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "flame time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_smog() {
        gx_smog_api* api_temp = new gx_smog_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "smog.jpg", static_cast<int>(1e9));
        api_temp->safe_production_smog(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_smog(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "smog time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_refvest() {
        gx_refvest_api* api_temp    = new gx_refvest_api(CONFIG_PATH);
        gx_posture_api* api_posture = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "refvest.jpeg", static_cast<int>(1e9));
        auto posture_info_list = api_posture->safe_production_posture(img);
        api_temp->safe_production_refvest(img, posture_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_refvest(img, posture_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "refvest time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_posture;
    }
    void time_test_sleep() {
        gx_sleep_api* api_temp = new gx_sleep_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "sleep1.jpg", static_cast<int>(1e9));
        api_temp->safe_production_sleep(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_sleep(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "sleep time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_smoke() {
        gx_smoke_api* api_temp      = new gx_smoke_api(CONFIG_PATH);
        gx_posture_api* api_posture = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "smoke3.jpg", static_cast<int>(1e9));
        auto posture_info_list = api_posture->safe_production_posture(img);
        api_temp->safe_production_smoke(img, posture_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_smoke(img, posture_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "smoke time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_posture;
    }
    void time_test_vehicle() {
        gx_vehicle_api* api_temp = new gx_vehicle_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "vehicle.jpg", static_cast<int>(1e9));
        api_temp->safe_production_vehicle(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_vehicle(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "vehicle time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_wander() {
        gx_wander_api* api_temp           = new gx_wander_api(CONFIG_PATH);
        gx_pedestrian_api* api_pedestrian = new gx_pedestrian_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "wander.jpg", static_cast<int>(1e9));
        auto person_list = api_pedestrian->safe_production_pedestrian(img);
        api_temp->safe_production_wander(img, 0, 1, 60, person_list.person_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_wander(img, i, 1, 60, person_list.person_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "wander time = " << duration.count() / T << " milliseconds\n";
        api_temp->wander_remove_library();
        delete api_temp;
        delete api_pedestrian;
    }
    void time_test_playphone() {
        gx_playphone_api* api_temp  = new gx_playphone_api(CONFIG_PATH);
        gx_posture_api* api_posture = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "playphone.jpg", static_cast<int>(1e9));
        auto posture_info_list = api_posture->safe_production_posture(img);
        api_temp->safe_production_playphone(img, posture_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_playphone(img, posture_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "playphone time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_posture;
    }
    void time_test_onphone_posture() {
        gx_onphone_api* api_temp    = new gx_onphone_api(CONFIG_PATH);
        gx_posture_api* api_posture = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "onphone.png", static_cast<int>(1e9));
        auto posture_info_list = api_posture->safe_production_posture(img);
        api_temp->safe_production_onphone(img, posture_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_onphone(img, posture_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "onphone_posture time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_posture;
    }
    void time_test_onphone_head() {
        gx_onphone_api* api_temp = new gx_onphone_api(CONFIG_PATH);
        gx_head_api* api_head    = new gx_head_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "onphone.png", static_cast<int>(1e9));
        auto head_info_list = api_head->safe_production_head(img);
        api_temp->safe_production_onphone(img, head_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_onphone(img, head_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "onphone_head time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_head;
    }
    void time_test_workcloth() {
        gx_workcloth_api* api_temp  = new gx_workcloth_api(CONFIG_PATH);
        gx_posture_api* api_posture = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "workcloth.jpg", static_cast<int>(1e9));
        auto posture_info_list = api_posture->safe_production_posture(img);
        api_temp->safe_production_workcloth(img, 0, posture_info_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_workcloth(img, 0, posture_info_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "workcloth time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_posture;
    }
    void time_test_pedestrian() {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "pedestrian.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pedestrian(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pedestrian(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pedestrian time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_crowd() {
        gx_crowd_api* api_temp = new gx_crowd_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "crowd.png", static_cast<int>(1e9));
        api_temp->safe_production_crowd(img, 5, 30, 0);
        auto start = std::chrono::high_resolution_clock::now();
        int T      = TIMES;
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_crowd(img, 5, 30, 0);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app) << "crowd time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_batterypilferers() {
        gx_batterypilferers_api* api_temp = new gx_batterypilferers_api(CONFIG_PATH);
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
        api_temp->safe_production_batterypilferers(img_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_batterypilferers(img_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "batterypilferers time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_fighting() {
        gx_fighting_api* api_temp = new gx_fighting_api(CONFIG_PATH);
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
        api_temp->safe_production_fighting(img_list, {0, 0, 1920, 1080});
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_fighting(img_list, {0, 0, 1920, 1080});
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "fighting time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_posture() {
        gx_posture_api* api_temp = new gx_posture_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "posture.jpg", static_cast<int>(1e9));
        api_temp->safe_production_posture(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_posture(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "posture time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_light() {
        gx_pump_light_api* api_temp = new gx_pump_light_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "pump_light/3_on.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_light(
            img, abi::vector<pump_light_point>{pump_light_point{726, 186}, pump_light_point{798, 186},
                     pump_light_point{798, 247}, pump_light_point{726, 247}});
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_light(
                img, abi::vector<pump_light_point>{pump_light_point{726, 186}, pump_light_point{798, 186},
                         pump_light_point{798, 247}, pump_light_point{726, 247}});
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_light time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_vesthelmet() {
        gx_pump_vesthelmet_api* api_temp = new gx_pump_vesthelmet_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "tcg.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_vesthelmet(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_vesthelmet(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_vesthelmet time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_gate_status() {
        gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "gate_open2.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_gate_status(img, 10);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_gate_status(img, 10);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_gate_status time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_pumptop_person() {
        gx_pump_pumptop_person_api* api_temp = new gx_pump_pumptop_person_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "pump_pumptop_person.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_pumptop_person(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_pumptop_person(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_pumptop_person time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_mask() {
        gx_pump_mask_api* api_temp = new gx_pump_mask_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "pump_mak.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_mask(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_mask(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_mask time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pumptop_helmet() {
        gx_pumptop_helmet_api* api_temp = new gx_pumptop_helmet_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "pumptop_helmet.png", static_cast<int>(1e9));
        api_temp->safe_production_pumptop_helmet(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pumptop_helmet(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pumptop_helmet time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_hoisting() {
        gx_pump_hoisting_api* api_temp = new gx_pump_hoisting_api(CONFIG_PATH);
        gx_img_api img1(abi::string(IMG_PATH) + "pump_hoistring2.jpg", static_cast<int>(1e9));
        gx_img_api img2(abi::string(IMG_PATH) + "pump_hoistring1.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_hoisting(img1, 1);
        api_temp->safe_production_pump_hoisting(img2, 1);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_hoisting(img1, 1);
            api_temp->safe_production_pump_hoisting(img2, 1);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_hoisting time = " << duration.count() / (T * 2) << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_weld() {
        gx_pump_weld_api* api_temp = new gx_pump_weld_api(CONFIG_PATH);
        abi::vector<gx_img_api> img_list;
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/0.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/1.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/5.jpg", static_cast<int>(1e9)));
        api_temp->safe_production_pump_weld(img_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_weld(img_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_weld time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pump_work_status() {
        gx_pump_work_status_api* api_temp = new gx_pump_work_status_api(CONFIG_PATH);
        abi::vector<pump_work_status_point> polygon;
        polygon.emplace_back(pump_work_status_point{741, 412});
        polygon.emplace_back(pump_work_status_point{1035, 412});
        polygon.emplace_back(pump_work_status_point{1475, 1080});
        polygon.emplace_back(pump_work_status_point{847, 1080});
        gx_img_api img(abi::string(IMG_PATH) + "pump_work_status.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pump_work_status(img, 1, polygon);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pump_work_status(img, 1, polygon);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pump_work_status time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_crossing() {
        gx_crossing_api* api_temp = new gx_crossing_api(CONFIG_PATH);
        gx_img_api img(abi::string(IMG_PATH) + "crossing1.jpg", static_cast<int>(1e9));
        api_temp->safe_production_crossing(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_crossing(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "crossing time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_pedestrian_min() {
        gx_pedestrian_min_api* api_temp = new gx_pedestrian_min_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "pedestrian_min.jpg", static_cast<int>(1e9));
        api_temp->safe_production_pedestrian_min(img);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_pedestrian_min(img);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "pedestrian_min time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_climb_tumble_pedestrian_climb() {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(CONFIG_PATH);
        gx_pedestrian_api* api_pedestrian        = new gx_pedestrian_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
        auto person_list = api_pedestrian->safe_production_pedestrian(img);
        api_temp->safe_production_climb_tumble_pedestrian(img, 0, person_list.person_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_climb_tumble_pedestrian(img, 0, person_list.person_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "climb_tumble_pedestrian_climb time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_pedestrian;
    }
    void time_test_climb_tumble_pedestrian_tumble() {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(CONFIG_PATH);
        gx_pedestrian_api* api_pedestrian        = new gx_pedestrian_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
        auto person_list = api_pedestrian->safe_production_pedestrian(img);
        api_temp->safe_production_climb_tumble_pedestrian(img, 1, person_list.person_list);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_climb_tumble_pedestrian(img, 1, person_list.person_list);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "climb_tumble_pedestrian_tumble time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
        delete api_pedestrian;
    }
    void time_test_subway_anomaly_nzx() {
        gx_subway_anomaly_api* api_temp = new gx_subway_anomaly_api(CONFIG_PATH);
        const gx_img_api img(
            abi::string(IMG_PATH) + "subway_anomaly_nzx/a.mp4_20240715_155251.095.png", static_cast<int>(1e9));
        api_temp->safe_production_subway_anomaly(
            img, {subway_anomaly_roi{955, 560, 75, 175}, subway_anomaly_roi{750, 500, 535, 30}}, 0);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_subway_anomaly(
                img, {subway_anomaly_roi{955, 560, 75, 175}, subway_anomaly_roi{750, 500, 535, 30}}, 0);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "subway_anomaly_nzx time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
    void time_test_subway_anomaly_yf() {
        gx_subway_anomaly_api* api_temp = new gx_subway_anomaly_api(CONFIG_PATH);
        const gx_img_api img(
            abi::string(IMG_PATH) + "subway_anomaly_yf/WeChat_20240529103018.mp4_20240530_110837.048.jpg",
            static_cast<int>(1e9));
        api_temp->safe_production_subway_anomaly(img, {subway_anomaly_roi{697, 265, 74, 401}}, 1);
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            api_temp->safe_production_subway_anomaly(img, {subway_anomaly_roi{697, 265, 74, 401}}, 1);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::ofstream(log_path.c_str(), std::ios::app)
            << "subway_anomaly_yf time = " << duration.count() / T << " milliseconds\n";
        delete api_temp;
    }
} // namespace glasssix

// 没有人脸的   线程池全都要配1
int main(int argc, char** argv) {
    time_test_helmet();
    time_test_head();
    time_test_flame();
    time_test_smog();
    time_test_refvest();
    time_test_sleep();
    time_test_smoke();
    time_test_vehicle();
    time_test_wander();
    time_test_playphone();
    time_test_onphone_posture();
    time_test_onphone_head();
    time_test_workcloth();
    time_test_pedestrian();
    time_test_crowd();
    time_test_batterypilferers();
    time_test_fighting();
    time_test_posture();
    time_test_pump_light();
    time_test_pump_vesthelmet();
    time_test_pump_gate_status();
    time_test_pump_pumptop_person();
    time_test_pump_mask();
    time_test_pumptop_helmet();
    time_test_pump_hoisting();
    time_test_pump_weld();
    time_test_pump_work_status();
    time_test_crossing();
    time_test_pedestrian_min();
    time_test_climb_tumble_pedestrian_climb();
    time_test_climb_tumble_pedestrian_tumble();
    time_test_subway_anomaly_nzx();
    time_test_subway_anomaly_yf();
    return 0;
}