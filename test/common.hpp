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
#include <gx_tumble_api.hpp>
#include <gx_vehicle_api.hpp>
#include <gx_wander_api.hpp>
#include <gx_workcloth_api.hpp>
#include <opencv2/opencv.hpp>
using namespace glasssix;
bool condition_time                  = false;
bool condition                       = true;
bool is_out_json                     = true;
#if SOPHON
static const abi::string CONFIG_PATH = "config";
#else
static const abi::string CONFIG_PATH = "/root/install/glasssix-offline-sdk/config";
#endif
static std::string IMG_PATH = "/root/img/";
#define TIMES 1100
namespace fs = std::filesystem;
namespace glasssix {

    const cv::Scalar RED   = CV_RGB(250, 0, 0); // 红
    const cv::Scalar GREEN = CV_RGB(0, 250, 0); // 绿
    const cv::Scalar WHITE = CV_RGB(255, 255, 255); // 白
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
    std::vector<std::string> find_file_test(std::filesystem::path folder_path) {
        std::vector<std::string> ans_list;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
                std::string temp(entry.path());
                ans_list.emplace_back(temp);
            }
        }
        return ans_list;
    }

} // namespace glasssix


// 调试代码
namespace glasssix {
    // t0 多线程测安全帽
    void thread_function_helmet() {
        gx_helmet_api* api_temp = new gx_helmet_api(CONFIG_PATH);
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "helmet.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_helmet(img);
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
    void thread_function_head() {
        gx_head_api* api_temp = new gx_head_api(CONFIG_PATH);
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "head.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_head(img);
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
    void thread_function_flame() {
        gx_flame_api* api_temp = new gx_flame_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "flame.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_flame(img);
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
    void thread_function_smog() {
        gx_smog_api* api_temp = new gx_smog_api(CONFIG_PATH);
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "smog.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smog(img);
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
    void thread_function_refvest() {
        gx_refvest_api* api_temp = new gx_refvest_api(CONFIG_PATH);
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "refvest.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_refvest(img);
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
    void thread_function_search() {
        gx_face_api* api_temp = new gx_face_api(CONFIG_PATH);
        api_temp->user_load();
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        const gx_img_api img(abi::string(IMG_PATH) + "action_live_0.jpg", static_cast<int>(1e9));
        api_temp->user_add_records(abi::vector<abi::string>{"123"}, abi::vector<gx_img_api>{img}, false, false);
        while (T--) {
            try {
                auto val =
                    api_temp->user_search(gx_img_api{abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9)}, 1, 0.5);
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
    void thread_function_integration() {
        gx_face_api* api_temp = new gx_face_api(CONFIG_PATH);
        api_temp->user_load();
        auto start = std::chrono::high_resolution_clock::now();
        int T      = TIMES;
        while (T--) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);
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
    void thread_function_Action_live_Blur() {
        gx_face_api* api_temp = new gx_face_api(CONFIG_PATH);
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
            printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t6 多线程测睡岗
    void thread_function_sleep() {
        gx_sleep_api* api_temp = new gx_sleep_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "sleep1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_sleep(img);
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
    void thread_function_smoke() {
        gx_smoke_api* api_temp = new gx_smoke_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "smoke3.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smoke(img);
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
    void thread_function_tumble() {
        gx_tumble_api* api_temp = new gx_tumble_api(CONFIG_PATH);
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_tumble(img);
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
    void thread_function_vehicle() {
        gx_vehicle_api* api_temp = new gx_vehicle_api(CONFIG_PATH);
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "vehicle.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_vehicle(img);
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
    void thread_function_wander() {
        gx_wander_api* api_temp = new gx_wander_api(CONFIG_PATH);
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "wander.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_wander(img, i, 1,60);
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
    void thread_function_wander_limit() {
        gx_wander_api* api_temp                = new gx_wander_api(CONFIG_PATH);
        gx_pedestrian_api* api_pedestrian_temp = new gx_pedestrian_api(CONFIG_PATH);
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
    void thread_function_leavepost() {
        gx_leavepost_api* api_temp = new gx_leavepost_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "leavepost.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_leavepost(img);
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
    void thread_function_playphone() {
        gx_playphone_api* api_temp = new gx_playphone_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
#if 1 // 这里必须要有表达式,不能省略
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "wsj_13.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
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
            for (auto enter : std::filesystem::directory_iterator(abi::string(IMG_PATH) + "playphone/")) {
                if (enter.is_regular_file()) {
                    std::string exit{enter.path().string()};
                    v_img.push_back(exit);
                    std::cout << "Found " << exit << std::endl;

                    const gx_img_api img(abi::string(exit), static_cast<int>(1e9));
                    auto val = api_temp->safe_production_playphone(img);
                    std::string relative_path{};
                    size_t subPos = exit.rfind("/") + 1;
                    relative_path = exit.substr(subPos);
                    if (condition)
                        printf("image_name = %s bodyerror_list = %d norm_list = %d playphone_list = %d\n",
                            relative_path.c_str(), val.bodyerror_list.size(), val.norm_list.size(),
                            val.playphone_list.size());
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
    void thread_function_onphone() {
        gx_onphone_api* api_temp         = new gx_onphone_api(CONFIG_PATH);
        gx_head_api* api_head_temp       = new gx_head_api(CONFIG_PATH);
        gx_posture_api* api_posture_temp = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(abi::string(IMG_PATH) + "onphone.png", static_cast<int>(1e9));
        auto val_head    = api_head_temp->safe_production_head(img);
        auto val_posture = api_posture_temp->safe_production_posture(img);
        int T            = TIMES;
        auto start       = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                auto val1 = api_temp->safe_production_onphone(img, val_head);
                if (condition) {
                    printf("[onphone] : head-> onphone_list = %d norm_list = %d\n", val1.onphone_list.size(),
                        val1.norm_list.size());
                    auto val2 = api_temp->safe_production_onphone(img, val_posture);
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
    void thread_function_workcloth() {
        gx_workcloth_api* api_temp = new gx_workcloth_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "workcloth.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_workcloth(img, 0);
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
    void thread_function_pedestrian() {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api(CONFIG_PATH);
        int T                       = TIMES;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "pedestrian.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian(img);
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
    void thread_function_climb() {
        gx_climb_api* api_temp = new gx_climb_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb(img);
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
    void thread_function_crowd() {
        gx_crowd_api* api_temp = new gx_crowd_api(CONFIG_PATH);
        auto start             = std::chrono::high_resolution_clock::now();
        int T                  = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "crowd.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_crowd(img, 5, 30, 0);
                if (val.head_list.size())
                    api_temp->crowd_remove_library(0);
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
    void thread_function_batterypilferers() {
        gx_batterypilferers_api* api_temp = new gx_batterypilferers_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        abi::vector<gx_img_api> img_list;
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_5.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_6.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_7.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_8.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "batterypilferers/batterypilferers_9.jpg", static_cast<int>(1e9)));

        for (int i = 0; i < T; ++i) {
            try {
                auto val = api_temp->safe_production_batterypilferers(img_list);
                if (condition)
                    printf("[batterypilferers] : score =%f category=%d\n", val.score, val.category);

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
    void thread_function_fighting() {
        try {

            gx_fighting_api* api_temp = new gx_fighting_api(CONFIG_PATH);
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
                if (condition)
                    printf(
                        "[fighting] : fight_list =%d normal_list =%d\n", val.fight_list.size(), val.normal_list.size());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition_time)
                printf("flame time = %lld microsecond\n", duration.count());
            delete api_temp;
        } catch (const std::exception& ex) {
            printf("error =  %s\n", ex.what());
        }
    }
    // t20 多线程测姿态
    void thread_function_posture() {
        gx_posture_api* api_temp = new gx_posture_api(CONFIG_PATH);
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "posture.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_posture(img);
                if (condition)
                    printf("[posture] : score =%f category=%d\n", val[0].score, val[0].key_points.size());

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
    // t24 多线程测定制灯光
    void thread_function_pump_light() {
        gx_pump_light_api* api_temp = new gx_pump_light_api(CONFIG_PATH);
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
                    if (condition)
                        printf("[pump_light] : score =%f light_status=%d\n", val.score, val.light_status);
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "pump_light/3_on.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_pump_light(
                        img, abi::vector<pump_light_point>{pump_light_point{726, 186}, pump_light_point{798, 186},
                                 pump_light_point{798, 247}, pump_light_point{726, 247}});
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
    void thread_function_pump_vesthelmet() {
        gx_pump_vesthelmet_api* api_temp = new gx_pump_vesthelmet_api(CONFIG_PATH);
        int T                            = TIMES;
        auto start                       = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "tcg.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_vesthelmet(img);
                if (condition)
                    printf("[pump_vesthelmet] : category = %d score = %.2f  \n", val.pump_vesthelmet_list[0].category,
                        val.pump_vesthelmet_list[0].score);
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
    void thread_function_pump_gate_status() {
        gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "gate_open2.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_gate_status(img, 10);
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
    void thread_function_pump_pumptop_person() {
        gx_pump_pumptop_person_api* api_temp = new gx_pump_pumptop_person_api(CONFIG_PATH);
        int T                                = TIMES;
        auto start                           = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                // gx_img_api img(abi::string(IMG_PATH) + "pumptop_person.jpg", static_cast<int>(1e9));
                gx_img_api img(abi::string(IMG_PATH) + "pump_pumptop_person.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_pumptop_person(img);
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
    void thread_function_pump_mask() {
        gx_pump_mask_api* api_temp = new gx_pump_mask_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pump_mak.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_mask(img);
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
    void thread_function_pumptop_helmet() {
        gx_pumptop_helmet_api* api_temp = new gx_pumptop_helmet_api(CONFIG_PATH);
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pumptop_helmet.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pumptop_helmet(img);
                if (condition) {
                    if (val.person_list.size() > 0)
                        printf("[pumptop_helmet] : category = %d \n", 1);
                    else
                        printf("[pumptop_helmet] : category = %d \n", 0);
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
    void thread_function_pump_hoisting() {
        gx_pump_hoisting_api* api_temp = new gx_pump_hoisting_api(CONFIG_PATH);
        int T                          = TIMES;
        auto start                     = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img1(abi::string(IMG_PATH) + "pump_hoistring2.jpg", static_cast<int>(1e9));
                api_temp->safe_production_pump_hoisting(img1, 1);
                gx_img_api img2(abi::string(IMG_PATH) + "pump_hoistring1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_hoisting(img2, 1);
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
    void thread_function_pump_weld() {
        gx_pump_weld_api* api_temp = new gx_pump_weld_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();

        abi::vector<gx_img_api> img_list;
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/weld0.png", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/weld1.png", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(abi::string(IMG_PATH) + "pump_weld/weld2.png", static_cast<int>(1e9)));
        for (int i = 0; i < T; ++i) {
            try {
                auto val = api_temp->safe_production_pump_weld(img_list);
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
    void thread_function_face_attributes() {
        gx_face_api* api_temp = new gx_face_api(CONFIG_PATH);
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "face_attributes.jpg", static_cast<int>(1e9));
                auto val = api_temp->face_attributes(img);
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
    void thread_function_pump_work_status() {
        gx_pump_work_status_api* api_temp = new gx_pump_work_status_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        abi::vector<pump_work_status_point> polygon;
        polygon.emplace_back(pump_work_status_point{741, 412});
        polygon.emplace_back(pump_work_status_point{1035, 412});
        polygon.emplace_back(pump_work_status_point{1475, 1080});
        polygon.emplace_back(pump_work_status_point{847, 1080});
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(abi::string(IMG_PATH) + "pump_work_status.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_work_status(img, 1, polygon);
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
    void thread_function_crossing() {
        gx_crossing_api* api_temp = new gx_crossing_api(CONFIG_PATH);
        int T                     = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                {
                    gx_img_api img(abi::string(IMG_PATH) + "crossing1.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
                    if (condition)
                        printf("[crossing1] : %llu \n", val.crossing_list.size());
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "crossing2.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
                    if (condition)
                        printf("[crossing2] : %llu \n", val.crossing_list.size());
                }
                {
                    gx_img_api img(abi::string(IMG_PATH) + "crossing3.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
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
    void thread_function_pedestrian_min() {
        gx_pedestrian_min_api* api_temp = new gx_pedestrian_min_api(CONFIG_PATH);
        int T                           = TIMES;
        auto start                      = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "pedestrian_min.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian_min(img);
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


    // t37 多线程测攀爬
    void thread_function_climb_tumble_pedestrian() {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        //auto list_ = find_file("/root/img/test/aa(2)/");
        //for (int i = 0; i < list_.size(); ++i) {
        //    std::cout << list_[i] << "\n";
        //    const gx_img_api img(list_[i], static_cast<int>(1e9));
        //    api_temp->safe_production_climb_tumble_pedestrian(img, 0,{});
        //    auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 0,{});
        //}

        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img,0);
                if (condition)
                    printf("[climb_tumble_pedestrian:climb] : persion_list = %llu climb_list = %llu tumble_list = %llu disabled_list = %llu other_list = %llu \n",
                        val.persion_list.size(), val.climb_list.size(), val.tumble_list.size(), val.disabled_list.size(), val.other_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(abi::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img,0);
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
            printf("climb_tumble_pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
} // namespace glasssix

// 处理视频的
namespace glasssix {
    struct video_data {
        int be_x, be_y;
        int ed_x, ed_y;
        int fps;
    };
    void try_a_try(const std::string& name, const std::string& save_path, video_data data_) {
        cv::VideoCapture capture;
        capture.open(name);
        // 测试要求每张图片写上对应时间与帧率
        std::string image_name;

        int x = data_.be_x;
        int y = data_.be_y;
        int z = 0; // 视频从第一帧开始
        for (int i = 0; i < (data_.ed_x * 60 + data_.ed_y) * data_.fps; i++) { // 结束时间
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            if (i >= ((data_.be_x * 60 + data_.be_y) * data_.fps)) // 开始时间
            {
                // cv::imwrite(save_path + "/" + std::to_string(i) + ":" std::to_string() + ".jpg", img);
                // 默认视频不超过一个小时
                z++; // !天杀的,少了这个

                if (z > data_.fps) {
                    y++;
                    z %= data_.fps;
                    // z++;
                }
                if (y >= 60) {
                    x++;
                    y %= 60;
                }
                cv::imwrite(
                    save_path + "/" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z) + ".jpg",
                    img);
                std::cout << " " << x << " " << y << " " << z << std::endl;
            }
        }
        capture.release();
    }
    void video_test(const std::string& save_path, const std::string& ans_path, video_data data_) {
        std::vector<std::string> temp = find_file_test(save_path);
        std::vector<std::string> relative_path;
        for (auto const& file : temp) {
            relative_path.push_back(std::filesystem::relative(file, save_path).string());
            std::cout << " " << file << std::endl;
        }
        std::cout << "相对路径: " << std::endl;
        for (auto const& file : relative_path) {
            std::cout << " " << file << std::endl;
        }
        gx_pedestrian_api* api_temp = new gx_pedestrian_api(CONFIG_PATH);
        // abi::vector<tumble_point> quadrangle;
        // quadrangle.emplace_back(tumble_point{.x =765, .y =567 });
        // quadrangle.emplace_back(tumble_point{.x =1309, .y =566 });
        // quadrangle.emplace_back(tumble_point{.x =1296, .y =789 });
        // quadrangle.emplace_back(tumble_point{.x =762, .y = 742});

        std::cout << temp.size() << std::endl;
        std::cout << relative_path.size() << std::endl;
        auto begin = std::chrono::high_resolution_clock::now();
        int F      = 1;
        while (F--) {
            for (int i = 0; i < temp.size(); i++) {
                // std::cout << "for 循环 : " << i << std::endl;
                std::string relative = std::filesystem::relative(temp.at(i), save_path).string();
                auto val             = api_temp->safe_production_pedestrian(gx_img_api{abi::string{temp[i]}, 1 << 28});
                cv::Mat img          = cv::imread(abi::string{temp[i]}.c_str());
#if 1
                if (val.person_list.size() > 0) {
                    std::cout << " I am here: " << std::endl;
                    printf("-------- %s.jpg\t --------\n", temp[i].c_str());
                    for (int j = 0; j < val.person_list.size(); j++) {
                        int x1      = val.person_list[j].x1;
                        int x2      = val.person_list[j].x2;
                        int y1      = val.person_list[j].y1;
                        int y2      = val.person_list[j].y2;
                        float score = val.person_list[j].score;
                        rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                        std::string text  = std::to_string(score);
                        cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                        cv::rectangle(img, cv::Point(x1, y1),
                            cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                        putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                    }
                    // cv之前要先创建路径
                    std::filesystem::create_directories(ans_path);
                    // std::cout << "return path: " << ans_path << std::endl;
                    cv::imwrite(ans_path + relative, img);
                }
#else
                // ans_path += "2";//常量,不允许自加
                // std::string new_path = ans_path + "2/";
                // if (val.norm_list.size() > 0) {
                //     std::cout << " I am here: " << std::endl;
                //     printf("-------- %s.jpg\t --------\n", temp[i].c_str());
                //     for (int j = 0; j < val.norm_list.size(); j++) {
                //         int x1      = val.norm_list[j].x1;
                //         int x2      = val.norm_list[j].x2;
                //         int y1      = val.norm_list[j].y1;
                //         int y2      = val.norm_list[j].y2;
                //         float score = val.norm_list[j].man_score;
                //         rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                //         std::string text  = std::to_string(score);
                //         cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                //         cv::rectangle(img, cv::Point(x1, y1),
                //             cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                //         putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                //     }
                //     //cv之前要先创建路径
                //     std::filesystem::create_directories(new_path);
                //     std::cout << "return path: " << new_path << std::endl;
                //     cv::imwrite(
                //         new_path + relative, img);
                // }
#endif
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        std::cout << "all video cost time :" << duration << " milliseconds" << std::endl;
    }

    void todo_video(
        const std::string& name, const std::string& save_path, const std::string& ans_path, video_data data_) {
        // try_a_try(name, save_path, data_);//分割视频的,测试目录图片时,可以不使用
        video_test(save_path, ans_path, data_);
    }

} // namespace glasssix


// 3566
//// 多线程测搜索
// void thread_function_search() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     api_temp->user_load();
//     int T                   = TIMES;
//     auto start = std::chrono::high_resolution_clock::now();
//     while (T--) {
//         try {
//             const gx_img_api img("/sdcard/img/action_live_5.jpg", static_cast<int>(1e9));
//             auto val = api_temp->user_search(img, 1, 0.5);
//             printf("similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
//         } catch (const std::exception& ex) {
//             printf("error =  %s\n", ex.what());
//         }
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("search time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }
//// 多线程测融合搜索
// void thread_function_integration() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     api_temp->user_load();
//     auto start = std::chrono::high_resolution_clock::now();
//     int T                   = TIMES;
//     while (T--) {
//         try {
//             // gx_img_api img(abi::string(IMG_PATH) + "bbb.jpg", static_cast<int>(1e9));
//             const gx_img_api img("/sdcard/img/action_live_5.jpg", static_cast<int>(1e9));
//             auto val = api_temp->detect_integration(img, 1, 0.5);
//             printf("prob = %.3f\n", val.prob);
//
//         } catch (const std::exception& ex) {
//             printf("error =  %s\n", ex.what());
//         }
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("integration time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }
//// 多线程测 配合活体 与 质量检测
// void thread_function_Action_live_Blur() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     auto start            = std::chrono::high_resolution_clock::now();
//     abi::vector<gx_img_api> img;
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_0.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_1.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_2.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_3.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_4.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_5.jpg", IMG_2K));
//     face_info info;
//     bool action_result = 0;
//     int T                   = TIMES;
//     while (T--) {
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
//         printf("BDFACE_ACTION_LIVE_BLINK %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
//         printf("BDFACE_ACTION_LIVE_OPEN_MOUTH %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
//         printf("BDFACE_ACTION_LIVE_NOD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
//         printf("BDFACE_ACTION_LIVE_LEFT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
//         printf("BDFACE_ACTION_LIVE_RIGHT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         auto val = api_temp->face_blur(img[5]);
//         printf("blur ====== %.2f\n", val.clarity[0]);
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("pedestrian time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }


void yuv_test() {

    const gx_img_api img_new(abi::string(IMG_PATH) + "NULL.jpg", static_cast<int>(1e9));
    const gx_img_api img(abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9));
    gx_face_api* temp_api = new gx_face_api(CONFIG_PATH);
    temp_api->detect(img_new);

    printf("face_feature    ------\n");
    std::getchar();
    int T = TIMES;
    while (T--) {
        auto val_new = temp_api->face_feature(img, false);
        printf("facerectwithfaceinfo_list.size = %d\n", val_new.facerectwithfaceinfo_list.size());
    }
}

void gif_test() {
    // 读取 GIF 文件
    cv::VideoCapture capture(IMG_PATH + "111.gif");

    if (!capture.isOpened()) {
        std::cout << "无法打开 GIF 文件" << std::endl;
        return;
    }

    // 逐帧解码并保存为图像
    cv::Mat frame;
    int frameCount = 0;
    while (true) {
        // 读取帧
        if (!capture.read(frame))
            break;

        // 保存为图像
        std::string outputName = IMG_PATH + std::to_string(frameCount) + ".jpeg";
        cv::imwrite(outputName, frame);

        frameCount++;
    }

    // 释放 VideoCapture 资源
    capture.release();

    std::cout << "成功解码 GIF 文件，共生成了 " << frameCount << " 张图像" << std::endl;

    return;
}

bool onSegment(double x1, double y1, double x2, double y2, double x, double y) {
    return (x >= std::min(x1, x2) && x <= std::max(x1, x2) && y >= std::min(y1, y2) && y <= std::max(y1, y2));
}

double orientation(double x1, double y1, double x2, double y2, double x3, double y3) {
    double val = (y2 - y1) * (x3 - x2) - (x2 - x1) * (y3 - y2);
    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}

bool segmentsIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double o1 = orientation(x1, y1, x2, y2, x3, y3);
    double o2 = orientation(x1, y1, x2, y2, x4, y4);
    double o3 = orientation(x3, y3, x4, y4, x1, y1);
    double o4 = orientation(x3, y3, x4, y4, x2, y2);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(x1, y1, x2, y2, x3, y3))
        return true;
    if (o2 == 0 && onSegment(x1, y1, x2, y2, x4, y4))
        return true;
    if (o3 == 0 && onSegment(x3, y3, x4, y4, x1, y1))
        return true;
    if (o4 == 0 && onSegment(x3, y3, x4, y4, x2, y2))
        return true;

    return false;
}


void wangder_limit() {

    // 读取 视频 文件
    cv::VideoCapture capture;
    capture.open("/root/video/Trim.mp4");

    // 逐帧解码并保存为图像
    cv::Mat frame;
    int frameCount             = 0;
    gx_wander_api* api_temp    = new gx_wander_api(CONFIG_PATH);
    gx_pedestrian_api* api_ped = new gx_pedestrian_api(CONFIG_PATH);
    int cnnt                   = 0;
    while (true) {
        // 读取帧
        capture >> frame;
        if (frame.empty())
            break;

        if (frameCount % 15 == 0) {
            // 保存为图像
            std::string outputName = "/root/video/temp.jpg";
            cv::imwrite(outputName, frame);

            gx_img_api img1("/root/video/temp.jpg", static_cast<int>(1e9));
            auto val_ped             = api_ped->safe_production_pedestrian(img1);
            auto now                 = std::chrono::system_clock::now();
            auto duration            = now.time_since_epoch();
            int64_t wander_timestamp = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
            wander_info val = api_temp->safe_production_wander(img1, wander_timestamp, 1, 60, val_ped.person_list);
            int result   = 0;
            for (const auto& detected : val.person_info) {
               /* int x1 = val.person_info[i].x1;
                int x2 = val.person_info[i].x2;
                int y1 = val.person_info[i].y1;
                int y2 = val.person_info[i].y2;

                cv::putText(frame,
                    std::to_string(val.person_info[i].id)
                        + "  time:" + std::to_string(val.person_info[i].sum_time),
                    cv::Point(x1, y1),
                    cv::FONT_HERSHEY_SIMPLEX, 1,
                    WHITE, 2);
                cv::rectangle(frame, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);*/
                printf("人员ID:%d 徘徊时间:%lld 出现次数:%d 预计徘徊时间内的总帧数:%.6f \n", detected.id,
                    detected.sum_time, detected.detection_number, 8 * 60 * detected.detection_fps);

            }
            //std::string path_ = "/root/video/" + std::to_string(cnnt++) + ".jpg";
            //cv::imwrite(path_, frame);
        }
        frameCount++;
    }

    // 释放 VideoCapture 资源
    capture.release();
}

void crossing(std::string path, std::string name) {

    // 读取 视频 文件
    cv::VideoCapture capture;
    capture.open(path.c_str());
    // 逐帧解码并保存为图像
    cv::Mat frame;
    int frameCount            = 0;
    gx_crossing_api* api_temp = new gx_crossing_api(CONFIG_PATH);
    int cnnt                  = 0;
    while (true) {
        // 读取帧
        capture >> frame;
        if (frame.empty())
            break;

        // 保存为图像
        std::string outputName = "/root/video/temp.jpg";
        cv::imwrite(outputName, frame);

        gx_img_api img1("/root/video/temp.jpg", static_cast<int>(1e9));
        auto val   = api_temp->safe_production_crossing(img1);
        int result = 0;

        // for (auto& ss : val) {
        //     bool k = zser(ss);
        //     if (k) {
        //     for (int i = 0; i < ss.key_points.size(); i++)
        //         cv::circle(frame, cv::Point{ss.key_points[i].x, ss.key_points[i].y}, 10, cv::Scalar{0, 255, 0}, -1);
        //     rectangle(frame, cv::Point(ss.location.x1, ss.location.y1), cv::Point(ss.location.x2, ss.location.y2),
        //     RED, 6);
        //     }
        //     result += k;
        // }
        if (result) {
            cv::imwrite("/root/video/ans/" + name + std::to_string(cnnt) + ".jpg", frame);
            cnnt++;
            printf("-------------------------------------------------\n");
        }
    }

    // 释放 VideoCapture 资源
    capture.release();
}


void gate_status1() {

    // 读取 视频 文件
    cv::VideoCapture capture;
    capture.open("/root/video/pump_gate_status/192.168.116.240_12_20240306162533192.mp4");

    // 逐帧解码并保存为图像
    cv::Mat frame;
    int frameCount                    = 0;
    gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(CONFIG_PATH);
    int cnnt                          = 0;
    while (true) {
        // 读取帧
        capture >> frame;
        if (frame.empty())
            break;

        std::string outputName = "/root/video/temp.jpg";
        cv::imwrite(outputName, frame);

        gx_img_api img1("/root/video/temp.jpg", static_cast<int>(1e9));
        auto val = api_temp->safe_production_pump_gate_status(img1, 12);
        if (val == "dangerous")
            cv::imwrite("/root/video/gate_ans/" + std::to_string(frameCount) + "_192.jpg", frame);
        frameCount++;
    }

    // 释放 VideoCapture 资源
    capture.release();
}

void gate_status2() {

    // 读取 视频 文件
    cv::VideoCapture capture;
    capture.open("/root/video/pump_gate_status/192.168.116.240_12_20240306163128579.mp4");

    // 逐帧解码并保存为图像
    cv::Mat frame;
    int frameCount                    = 0;
    gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(CONFIG_PATH);
    int cnnt                          = 0;
    while (true) {
        // 读取帧
        capture >> frame;
        if (frame.empty())
            break;

        std::string outputName = "/root/video/temp.jpg";
        cv::imwrite(outputName, frame);

        gx_img_api img1("/root/video/temp.jpg", static_cast<int>(1e9));
        auto val = api_temp->safe_production_pump_gate_status(img1, 12);
        if (val == "dangerous")
            cv::imwrite("/root/video/gate_ans/" + std::to_string(frameCount) + "_579.jpg", frame);
        frameCount++;
    }

    // 释放 VideoCapture 资源
    capture.release();
}

void face_test() {
    gx_face_api* api_temp = new gx_face_api(CONFIG_PATH);
    api_temp->user_load();
    int T = 5;
    const gx_img_api img(abi::string(IMG_PATH) + "action_live_0.jpg", static_cast<int>(1e9));
    for (int i = 0; i < 100000; i++) {
        abi::string name(std::to_string(i));
        api_temp->user_add_records(abi::vector<abi::string>{name}, abi::vector<gx_img_api>{img}, false, false);
        if (i % 1000 == 0)
            std::cout << api_temp->user_record_count() << "-------\n";
    }
    auto start = std::chrono::high_resolution_clock::now();
    while (T--) {
        try {
            auto val = api_temp->user_search(gx_img_api{abi::string(IMG_PATH) + "action_live_5.jpg", static_cast<int>(1e9)}, 1, 0.5);
            if (condition)
                printf("[search] : similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
        } catch (const std::exception& ex) {
            printf("error =  %s\n", ex.what());
        }
    }
    auto end      = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    if (condition_time)
        printf("search time = %lld microsecond\n", duration.count() / 5);
    delete api_temp;
}


    // 多线程测人头(读取文件夹内容并写入json文件）
void thread_function_head_from() {
    gx_head_api* api_temp = new gx_head_api(CONFIG_PATH);
    int T                 = 1;
    const char* path                           = R"(/root/img/images/)";
    std::vector<std::string> folder_file = find_file_test(path);
    std::cout << " folder_file " << folder_file.size() << ";" << std::endl;
    auto start            = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < T; ++i) {
        try {
            for (int i = 0; i < folder_file.size(); i++)
            {
                fs::path filePath(folder_file[i]);
                std::string fileName = filePath.filename().string();//拿到图片名字(含后缀名)
                std::string fileNamePre;
                std::cout << "fileName : " << fileName << std::endl;
                size_t lastDotPos = fileName.find_last_of(".");
                //如果找到 点 ,则截取前面的部分作为文件名
                if(lastDotPos != std::string::npos)
                {
                    fileNamePre = fileName.substr(0, lastDotPos);
                    std::cout << "fileNamePre : " << fileNamePre << std::endl;
                }
                const gx_img_api img(abi::string(path + fileName), static_cast<int>(1e9));
                auto val = api_temp->safe_production_head(img);
                if (condition)
                    printf("[head] : head_list = %d\n", val.size());
                if (is_out_json)
                {
                    //std::cout << glasssix::json::parse(val).dump() << "+++++++++\n";
                    for (int i = 0; i < val.size(); i++) {
                        std::cout << "x1 : " << val[i].x1 << std::endl;
                        std::cout << "x2 : " << val[i].x2 << std::endl;
                        std::cout << "y1 : " << val[i].y1 << std::endl;
                        std::cout << "y2 : " << val[i].y2 << std::endl;
                        std::cout << "score : " << val[i].score << std::endl << std::endl;

                        //写入json文件
                        
                        std::ofstream outputFile("./json/" + fileNamePre + ".json");
                        if (outputFile.is_open()) {
                            outputFile << "{\n";
                            outputFile << "  \"head_info\": [\n";
                            for (size_t i = 0; i < val.size(); ++i) {
                                outputFile << "    {\n";
                                outputFile << "      \"x1\": " << val[i].x1 << ",\n";
                                outputFile << "      \"x2\": " << val[i].x2 << ",\n";
                                outputFile << "      \"y1\": " << val[i].y1 << ",\n";
                                outputFile << "      \"y2\": " << val[i].y2 << ",\n";
                                outputFile << "      \"score\": " << val[i].score << "\n";
                                if (i == val.size() - 1) {
                                    outputFile << "    }\n";
                                } else {
                                    outputFile << "    },\n";
                                }
                            }
                            outputFile << "  ]\n";
                            outputFile << "}\n";
                            outputFile.close();
                            std::cout << "JSON output successfully written to file." << std::endl;
                        } else {
                            std::cerr << "Unable to open file for writing." << std::endl;
                        }
                    }
                    std::cout << "*********\n";
                }
            }

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