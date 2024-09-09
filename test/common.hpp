#include <algorithm>
#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <thread>

#include <gx_api.hpp>
#include <gx_batterypilferers_api.hpp>
#include <gx_climb_api.hpp>
#include <gx_climb_tumble_pedestrian_api.hpp>
#include <gx_crossing_api.hpp>
#include <gx_crowd_api.hpp>
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
#include <gx_refvest_api.hpp>
#include <gx_workcloth_api.hpp>
#include <gx_sleep_api.hpp>
#include <gx_smog_api.hpp>
#include <gx_smoke_api.hpp>
#include <gx_tumble_api.hpp>
#include <gx_vehicle_api.hpp>
#include <gx_wander_api.hpp>
#include <gx_pump_hoisting_api.hpp>
#include <gx_pump_work_status_api.hpp>
#include <gx_pump_weld_api.hpp>
#include <gx_pump_pumptop_person_api.hpp>
#include <gx_pump_gate_status_api.hpp> 
#include <gx_pump_mask_api.hpp>
// #include <gx_pump_protect_face_api.hpp>
// #include <gx_pump_cover_plate_api.hpp>
// #include <gx_policeuniform_api.hpp>
#include <opencv2/opencv.hpp>
using namespace glasssix;
bool condition_time                  = false;
bool condition                       = true;
bool is_out_json                     = true;
static const std::string CONFIG_PATH = "/root/install/restruct/config";
static std::string IMG_PATH          = "/root/img/";

#define TIMES 1
namespace fs = std::filesystem;
namespace glasssix {

    const cv::Scalar RED   = CV_RGB(250, 0, 0); // 红
    const cv::Scalar GREEN = CV_RGB(0, 250, 0); // 绿
    const cv::Scalar WHITE = CV_RGB(255, 255, 255); // 白
    // 返回的绝对路径
    std::vector<std::string> find_file(std::filesystem::path folder_path) {
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
                const gx_img_api img(std::string(IMG_PATH) + "helmet.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_helmet(img);
                if (condition)
                    printf("[helmet] : with_helmet_list = %zu with_hat_list = %zu head_list = %zu\n",
                        val.with_helmet_list.size(), val.with_hat_list.size(), val.head_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("helmet time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t1 多线程测火焰
    void thread_function_flame() {
        gx_flame_api* api_temp = new gx_flame_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "flame.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_flame(img);
                if (condition)
                    printf("[flame] : fire_list = %zu\n", val.fire_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("flame time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t2 多线程测反光衣
    void thread_function_refvest() {
        gx_refvest_api* api_temp = new gx_refvest_api(CONFIG_PATH);
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "refvest.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_refvest(img);
                if (condition)
                    printf("[refvest] : with_refvest_list = %lu without_refvest_list = %lu\n",
                        val.with_refvest_list.size(), val.without_refvest_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("refvest time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t6 多线程测睡岗
    void thread_function_sleep() {
        gx_sleep_api* api_temp = new gx_sleep_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "sleep1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_sleep(img, 1);
                if (condition)
                    printf("[sleep] : lying_list = %lu work_list = %lu\n", val.lying_list.size(), val.work_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("sleep time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t7 多线程测抽烟
    void thread_function_smoke() {
        gx_smoke_api* api_temp = new gx_smoke_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "smoke3.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smoke(img);
                if (condition)
                    printf("[smoke] : smoke_list = %lu norm_list = %lu\n", val.smoke_list.size(), val.norm_list.size());
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
            printf("smoke time = %ld microsecond\n", duration);
        delete api_temp;
    }


    // t8 多线程测玩手机
    void thread_function_playphone() {
        gx_playphone_api* api_temp = new gx_playphone_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "playphone.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
                if (condition)
                    printf("[playphone] : playphone_list = %zu norm_list = %zu bodyerror_list = %zu\n",
                        val.playphone_list.size(), val.norm_list.size(), val.bodyerror_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("playphone time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t9 多线程测打电话
    void thread_function_onphone() {
        gx_onphone_api* api_temp         = new gx_onphone_api(CONFIG_PATH);
        gx_head_api* api_head_temp       = new gx_head_api(CONFIG_PATH);
        gx_posture_api* api_posture_temp = new gx_posture_api(CONFIG_PATH);
        const gx_img_api img(std::string(IMG_PATH) + "onphone.png", static_cast<int>(1e9));
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
    // t11 多线程测车辆
    void thread_function_vehicle() {
        gx_vehicle_api* api_temp = new gx_vehicle_api(CONFIG_PATH);
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "vehicle.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_vehicle(img);
                if (condition)
                    printf("[vehicle] : vehicle_list = %zu\n", val.vehicle_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("vehicle time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t12 多线程测行人检测
    void thread_function_pedestrian() {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api(CONFIG_PATH);
        int T                       = TIMES;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "pedestrian.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian(img);
                if (condition)
                    printf("[pedestrian] : person_list = %zu\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pedestrian time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t14 多线程测烟雾
    void thread_function_smog() {
        gx_smog_api* api_temp = new gx_smog_api(CONFIG_PATH);
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "smog.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smog(img);
                if (condition)
                    printf("[smog] : smog_list = %zu\n", val.smog_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("smog time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t15 多线程测跌倒
    void thread_function_tumble() {
        gx_tumble_api* api_temp = new gx_tumble_api(CONFIG_PATH);
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_tumble(img);
                if (condition)
                    printf("[tumble] : tumble_list = %lu stand_list = %lu\n", val.tumble_list.size(),
                        val.stand_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("tumble time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t16 多线程测攀爬
    void thread_function_climb() {
        gx_climb_api* api_temp = new gx_climb_api(CONFIG_PATH);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb(img);
                if (condition)
                    printf("[climb] : climb_list = %zu normal_list = %zu\n", val.climb_list.size(),
                        val.normal_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("climb time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t17 多线程测聚众
    void thread_function_crowd() {
        gx_crowd_api* api_temp = new gx_crowd_api(CONFIG_PATH);
        auto start             = std::chrono::high_resolution_clock::now();
        int T                  = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "crowd.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_crowd(img, 5, 30, 0);
                if (condition)
                    printf("[crowd] : head_list = %lu\n", val.head_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition_time)
                printf("crowd time = %ld microsecond\n", duration.count());
        }
        delete api_temp;
    }


    // t18 多线程测徘徊
    void thread_function_wander() {
        gx_wander_api* api_temp = new gx_wander_api(CONFIG_PATH);
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "wander.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_wander(img, i, 1, 60);
                if (condition) {
                    printf("[wander] : wander_list = %zu device =%d\n", val.person_info.size(), 1);
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
            printf("wander time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t21 多线程测越界
    void thread_function_wander_limit() {
        gx_wander_api* api_temp                = new gx_wander_api(CONFIG_PATH);
        gx_pedestrian_api* api_pedestrian_temp = new gx_pedestrian_api(CONFIG_PATH);
        int T                                  = TIMES;
        auto start                             = std::chrono::high_resolution_clock::now();
        const gx_img_api img1(std::string(IMG_PATH) + "wander_limit1.png", static_cast<int>(1e9));
        const gx_img_api img2(std::string(IMG_PATH) + "wander_limit2.png", static_cast<int>(1e9));
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
            printf("wander_limit time = %ld microsecond\n", duration.count());
        }
        delete api_temp;
    }


    // t19 多线程测打架斗殴
    void thread_function_fighting() {
        try {

            gx_fighting_api* api_temp = new gx_fighting_api(CONFIG_PATH);
            int T                     = TIMES;
            auto start                = std::chrono::high_resolution_clock::now();
            std::vector<gx_img_api> img_list;
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_0th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_5th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_10th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_15th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_20th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_25th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_30th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_35th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_40th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "fighting/fight_45th.jpg", static_cast<int>(1e9)));
            for (int i = 0; i < T; ++i) {
                auto val = api_temp->safe_production_fighting(img_list, {0, 0, 1920, 1080});
                if (condition)
                    printf("[fighting] : fight_list =%zu normal_list =%zu\n", val.fight_list.size(),
                        val.normal_list.size());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition_time)
                printf("flame time = %ld microsecond\n", duration.count());
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
                gx_img_api img(std::string(IMG_PATH) + "posture.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_posture(img);
                if (condition)
                    printf("[posture] : score =%f category=%zu\n", val[0].score, val[0].key_points.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("flame time = %ld microsecond\n", duration.count());
        delete api_temp;
    }

    // t22 多线程测人头
    void thread_function_head() {
        gx_head_api* api_temp = new gx_head_api(CONFIG_PATH);
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "head.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_head(img);
                if (condition)
                    printf("[head] : head_list = %zu\n", val.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("head time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t23 多线程测偷电瓶
    void thread_function_batterypilferers() {
        gx_batterypilferers_api* api_temp = new gx_batterypilferers_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        std::vector<gx_img_api> img_list;
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_5.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_6.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_7.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_8.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(
            gx_img_api(std::string(IMG_PATH) + "batterypilferers/batterypilferers_9.jpg", static_cast<int>(1e9)));

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
            printf("batterypilferers time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    void thread_function_crossing() {
        gx_crossing_api* api_temp = new gx_crossing_api(CONFIG_PATH);
        int T                     = TIMES;
        for (int i = 0; i < T; ++i) {
            try {
                {
                    gx_img_api img(std::string(IMG_PATH) + "crossing1.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
                    if (condition)
                        printf("[crossing1] : %llu \n", val.crossing_list.size());
                }
                {
                    gx_img_api img(std::string(IMG_PATH) + "crossing2.jpg", static_cast<int>(1e9));
                    auto val = api_temp->safe_production_crossing(img);
                    if (condition)
                        printf("[crossing2] : %llu \n", val.crossing_list.size());
                }
                {
                    gx_img_api img(std::string(IMG_PATH) + "crossing3.jpg", static_cast<int>(1e9));
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
                const gx_img_api img(std::string(IMG_PATH) + "pedestrian_min.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian_min(img);
                if (condition)
                    printf("[pedestrian_min] : pedestrian_min_list = %zu\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pedestrian_min time = %ld microsecond\n", duration.count());
        delete api_temp;
    }
    // t10 多线程测工服检测
    void thread_function_workcloth() {
        gx_workcloth_api* api_temp = new gx_workcloth_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "workcloth.jpg", static_cast<int>(1e9));
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


    // t37 多线程测攀爬跌倒的攀爬
    void thread_function_climb_tumble_pedestrian_climb() {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(CONFIG_PATH);
        int T                                    = TIMES;
        auto start                               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 0);
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
            printf("climb_tumble_pedestrian_climb time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

    void thread_function_climb_tumble_pedestrian_tumble() {
        gx_climb_tumble_pedestrian_api* api_temp = new gx_climb_tumble_pedestrian_api(CONFIG_PATH);
        int T                                    = TIMES;
        auto start                               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img(std::string(IMG_PATH) + "tumble.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb_tumble_pedestrian(img, 1);
                if (condition)
                    printf(
                        "[climb_tumble_pedestrian:tumble] : persion_list = %llu climb_list = %llu tumble_list = %llu "
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
            printf("climb_tumble_pedestrian_tumble time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t33 多线程测定制工作状态
    void thread_function_pump_work_status() {
        gx_pump_work_status_api* api_temp = new gx_pump_work_status_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        std::vector<pump_work_status_point> polygon;
        polygon.emplace_back(pump_work_status_point{773, 407});
        polygon.emplace_back(pump_work_status_point{1072, 407});
        polygon.emplace_back(pump_work_status_point{1526, 1080});
        polygon.emplace_back(pump_work_status_point{895, 1080});
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(std::string(IMG_PATH) + "pump_work_status.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_work_status(img, 1, polygon);
                if (condition)
                    printf("[pump_work_status] : %s \n", val.security_status.c_str());
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

    // t31 多线程测定制泵业焊接
    void thread_function_pump_weld() {
        gx_pump_weld_api* api_temp = new gx_pump_weld_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        std::vector<gx_img_api> img_list;
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/0.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/1.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/2.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/3.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/4.jpg", static_cast<int>(1e9)));
        img_list.emplace_back(gx_img_api(std::string(IMG_PATH) + "pump_weld/5.jpg", static_cast<int>(1e9)));
        for (int i = 0; i < T; ++i) {
            try {
                auto val = api_temp->safe_production_pump_weld(img_list);
                if (condition) {
                    if (val.persons_weld.size() > 0)
                        printf("[pump_weld] : category=%d\n", val.persons_weld[0].category);
                    else
                        printf("[pump_weld] : category=%d\n", 10);
                }
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

    // t27 多线程测定制泵顶行人
    void thread_function_pump_pumptop_person() {
        gx_pump_pumptop_person_api* api_temp = new gx_pump_pumptop_person_api(CONFIG_PATH);
        int T                                = TIMES;
        auto start                           = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                // gx_img_api img(std::string(IMG_PATH) + "pumptop_person.jpg", static_cast<int>(1e9));
                gx_img_api img(std::string(IMG_PATH) + "pump_pumptop_person.jpg", static_cast<int>(1e9));
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

    // t26 多线程测定制大门状态
    void thread_function_pump_gate_status() {
        gx_pump_gate_status_api* api_temp = new gx_pump_gate_status_api(CONFIG_PATH);
        int T                             = TIMES;
        auto start                        = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(std::string(IMG_PATH) + "pump_gate_status.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pump_gate_status(img, 15);
                if (condition)
                    printf("[pump_gate_status] : %s  \n", val.security_status.c_str());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }

        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition_time)
            printf("pump_gate_status time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    //  多线程测定制防护面罩
    void thread_function_pump_mask() {
        gx_pump_mask_api* api_temp = new gx_pump_mask_api(CONFIG_PATH);
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img(std::string(IMG_PATH) + "pump_mask.jpg", static_cast<int>(1e9));
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
    // 多线程测定制泵业狭小空间（天车工吊装）
    void thread_function_pump_hoisting() {
        gx_pump_hoisting_api* api_temp = new gx_pump_hoisting_api(CONFIG_PATH);
        int T                          = TIMES;
        auto start                     = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img1(std::string(IMG_PATH) + "pump_hoistring2.jpg", static_cast<int>(1e9));
                api_temp->safe_production_pump_hoisting(img1, 1);
                gx_img_api img2(std::string(IMG_PATH) + "pump_hoistring1.jpg", static_cast<int>(1e9));
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

    // void thread_function_policeuniform() {
    //     gx_policeuniform_api* api_temp = new gx_policeuniform_api(CONFIG_PATH);
    //     int T                          = TIMES;
    //     auto start                     = std::chrono::high_resolution_clock::now();
    //     for (int i = 0; i < T; ++i) {
    //         try {
    //             const gx_img_api img(abi::string(IMG_PATH) + "policeuniform.png", static_cast<int>(1e9));
    //             auto val = api_temp->safe_production_policeuniform(img);
    //             if (condition)
    //                 printf("[policeuniform] : policeuniform_list = %d\n", val.without_policeuniform_list.size());

    //        } catch (const std::exception& ex) {
    //            printf("error =  %s\n", ex.what());
    //        }
    //    }
    //    auto end      = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //    if (condition_time)
    //        printf("policeuniform time = %lld microsecond\n", duration.count());
    //    delete api_temp;
    //}
    // void thread_function_pump_glove() {
    //    gx_pump_glove_api* api_temp = new gx_pump_glove_api(CONFIG_PATH);
    //    int T                       = TIMES;
    //    auto start                  = std::chrono::high_resolution_clock::now();
    //    for (int i = 0; i < T; ++i) {
    //        try {
    //            const gx_img_api img(abi::string(IMG_PATH) + "pump_glove0.jpg", static_cast<int>(1e9));
    //            auto val = api_temp->safe_production_pump_glove(img);
    //            if (condition)
    //                printf("[pump_glove] : unglove_list = %d\n", val.unglove_list.size());

    //        } catch (const std::exception& ex) {
    //            printf("error =  %s\n", ex.what());
    //        }
    //    }
    //    auto end      = std::chrono::high_resolution_clock::now();
    //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //    if (condition_time)
    //        printf("pump_glove time = %lld microsecond\n", duration.count());
    //    delete api_temp;
    //}

    // void thread_function_pump_protect_face() {
    //     gx_pump_protect_face_api* api_temp = new gx_pump_protect_face_api(glasssix::abi::string(CONFIG_PATH));
    //     int T                              = TIMES;
    //     auto start                         = std::chrono::high_resolution_clock::now();
    //     for (int i = 0; i < T; ++i) {
    //         try {
    //             gx_img_api img(abi::string(IMG_PATH) + "pump_protect_face.jpg", static_cast<int>(1e9));
    //             auto val = api_temp->safe_production_pump_protect_face(img);
    //             if (condition) {
    //                 if (val.pump_no_protect_face_list.size())
    //                     printf("[pump_protect_face] : category=%d\n",
    //                         val.pump_no_protect_face_list[0].category);
    //                 else
    //                     printf("[pump_protect_face] : category=%d\n", 10);
    //             }
    //         } catch (const std::exception& ex) {
    //             printf("error =  %s\n", ex.what());
    //         }
    //     }
    //     auto end      = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //     if (condition_time)
    //         printf("pump_protect_face time = %lld microsecond\n", duration.count());
    //     delete api_temp;
    // }

    // void thread_function_pump_cover_plate() {
    //     gx_pump_cover_plate_api* api_temp = new gx_pump_cover_plate_api(CONFIG_PATH);
    //     int T                             = TIMES;
    //     auto start                        = std::chrono::high_resolution_clock::now();
    //     for (int i = 0; i < T; ++i) {
    //         try {
    //             {
    //                 gx_img_api img(abi::string(IMG_PATH) + "pump_cover_plate.jpg", static_cast<int>(1e9));
    //                 auto val = api_temp->safe_production_pump_cover_plate(
    //                     img, abi::vector<pump_cover_plate_point>{pump_cover_plate_point{1699, 827},
    //                              pump_cover_plate_point{2009, 769}, pump_cover_plate_point{2357, 1035},
    //                              pump_cover_plate_point{2069, 1179}});
    //                 if (condition)
    //                     printf("[pump_cover_plate] : score =%f cover_plate_status=%d\n", val.score,
    //                         val.cover_plate_status);
    //             }
    //             {
    //                 gx_img_api img(abi::string(IMG_PATH) + "pump_cover_plate_close.jpg", static_cast<int>(1e9));
    //                 auto val = api_temp->safe_production_pump_cover_plate(
    //                     img, abi::vector<pump_cover_plate_point>{pump_cover_plate_point{1699, 827},
    //                              pump_cover_plate_point{2009, 769}, pump_cover_plate_point{2357, 1035},
    //                              pump_cover_plate_point{2069, 1179}});
    //                 if (condition)
    //                     printf("[pump_cover_plate] : score =%f cover_plate_status=%d\n", val.score,
    //                         val.cover_plate_status);
    //             }
    //             {
    //                 gx_img_api img(abi::string(IMG_PATH) + "pump_cover_plate_open.jpg", static_cast<int>(1e9));
    //                 auto val = api_temp->safe_production_pump_cover_plate(
    //                     img, abi::vector<pump_cover_plate_point>{pump_cover_plate_point{1699, 827},
    //                              pump_cover_plate_point{2009, 769}, pump_cover_plate_point{2357, 1035},
    //                              pump_cover_plate_point{2069, 1179}});
    //                 if (condition)
    //                     printf("[pump_cover_plate] : score =%f cover_plate_status=%d\n", val.score,
    //                         val.cover_plate_status);
    //             }
    //         } catch (const std::exception& ex) {
    //             printf("error =  %s\n", ex.what());
    //         }
    //     }
    //     auto end      = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //     if (condition_time)
    //         printf("pump_cover_plate time = %lld microsecond\n", duration.count());
    //     delete api_temp;
    // }
} // namespace glasssix