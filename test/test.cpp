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
#include <gx_crowd_api.hpp>
#include <gx_face_api.hpp>
#include <gx_fighting_api.hpp>
#include <gx_flame_api.hpp>
#include <gx_head_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_leavepost_api.hpp>
#include <gx_onphone_api.hpp>
#include <gx_pedestrian_api.hpp>
#include <gx_playphone_api.hpp>
#include <gx_posture_api.hpp>
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
bool condition = true;
#define TIMES 1000

namespace glasssix {

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
        gx_helmet_api* api_temp = new gx_helmet_api();
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/helmet.jpg", static_cast<int>(1e9));
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
        if (condition)
            printf("helmet time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t22 多线程测人头
    void thread_function_head() {
        gx_head_api* api_temp = new gx_head_api();
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/head.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_head(img);
                if (condition)
                    printf("[head] : head_list = %d\n", val.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("head time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t1 多线程测火焰
    void thread_function_flame() {
        gx_flame_api* api_temp = new gx_flame_api();
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/flame.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_flame(img);
                if (condition)
                    printf("[flame] : fire_list = %d\n", val.fire_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t14 多线程测烟雾
    void thread_function_smog() {
        gx_smog_api* api_temp = new gx_smog_api();
        int T                 = TIMES;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/smog3.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smog(img);
                if (condition)
                    printf("[smog] : smog_list = %d\n", val.smog_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("smog time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t2 多线程测反光衣
    void thread_function_refvest() {
        gx_refvest_api* api_temp = new gx_refvest_api();
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/refvest.jpeg", static_cast<int>(1e9));
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
        if (condition)
            printf("refvest time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t3 多线程测搜索
    void thread_function_search() {
        gx_face_api* api_temp = new gx_face_api();
        api_temp->user_load();
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        const gx_img_api img("/root/img/action_live_0.jpg", static_cast<int>(1e9));
        api_temp->user_add_records(abi::vector<abi::string>{"123"}, abi::vector<gx_img_api>{img}, false, false);
        while (T--) {
            try {
                auto val =
                    api_temp->user_search(gx_img_api{"/root/img/action_live_5.jpg", static_cast<int>(1e9)}, 1, 0.5);
                if (condition)
                    printf("[search] : similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("search time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t4 多线程测融合搜索
    void thread_function_integration() {
        gx_face_api* api_temp = new gx_face_api();
        api_temp->user_load();
        auto start = std::chrono::high_resolution_clock::now();
        int T      = TIMES;
        while (T--) {
            try {
                const gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);
                if (condition)
                    printf("[integration] : prob = %.3f\n", val.prob);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("integration time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t13 多线程测 配合活体 与 质量检测
    void thread_function_Action_live_Blur() {
        gx_face_api* api_temp = new gx_face_api();
        auto start            = std::chrono::high_resolution_clock::now();

        abi::vector<gx_img_api> img;
        img.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_1.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_2.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_3.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_4.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_5.jpg", IMG_2K));
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
        if (condition)
            printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t6 多线程测睡岗
    void thread_function_sleep() {
        gx_sleep_api* api_temp = new gx_sleep_api();
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/sleep1.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_sleep(img);
                if (condition)
                    printf("[sleep] : lying_list = %d work_list = %d\n", val.lying_list.size(), val.work_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("sleep time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t7 多线程测抽烟
    void thread_function_smoke() {
        gx_smoke_api* api_temp = new gx_smoke_api();
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/smoke.jpg", static_cast<int>(1e9));
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
        if (condition)
            printf("smoke time = %lld microsecond\n", duration);
        delete api_temp;
    }
    // t15 多线程测跌倒
    void thread_function_tumble() {
        gx_tumble_api* api_temp = new gx_tumble_api();
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/tumble.jpg", static_cast<int>(1e9));
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
        if (condition)
            printf("tumble time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t11 多线程测车辆
    void thread_function_vehicle() {
        gx_vehicle_api* api_temp = new gx_vehicle_api();
        int T                    = TIMES;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/vehicle.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_vehicle(img);
                if (condition)
                    printf("[vehicle] : vehicle_list = %d\n", val.vehicle_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("vehicle time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t18 多线程测徘徊
    void thread_function_wander() {
        gx_wander_api* api_temp = new gx_wander_api();
        int T                   = TIMES;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/wander.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_wander(img, i, 1);
                if (condition) {
                    printf("[wander] : wander_list = %d device =%d\n", val.person_info.size(), 1);
                    printf("[wander] : wander_remove_id ans =%d\n", api_temp->wander_remove_id(val.person_info[0].id));
                }
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        if (condition)
            printf("%d\n", api_temp->wander_remove_library());
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("wander time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t21 多线程测越界
    void thread_function_wander_limit() {
        gx_wander_api* api_temp                = new gx_wander_api();
        gx_pedestrian_api* api_pedestrian_temp = new gx_pedestrian_api();
        int T                                  = TIMES;
        auto start                             = std::chrono::high_resolution_clock::now();
        const gx_img_api img1("/root/img/wander_limit1.png", static_cast<int>(1e9));
        const gx_img_api img2("/root/img/wander_limit2.png", static_cast<int>(1e9));
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
            printf("wander_limit time = %lld microsecond\n", duration.count());
        }
        delete api_temp;
    }
    // t5 多线程测离岗
    void thread_function_leavepost() {
        gx_leavepost_api* api_temp = new gx_leavepost_api();
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/leavepost.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_leavepost(img);
                if (condition)
                    printf("[leavepost] : hat_list = %d\n", val.hat_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("leavepost time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t8 多线程测玩手机
    void thread_function_playphone() {
        gx_playphone_api* api_temp = new gx_playphone_api();
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
#if 1 // 这里必须要有表达式,不能省略
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/playphone_zj.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
                if (condition)
                    printf("[playphone] : bodyerror_list = %d norm_list = %d playphone_list = %d\n",
                        val.bodyerror_list.size(), val.norm_list.size(), val.playphone_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
#else // 测试要求进行多图片检测
        try {
            std::vector<std::string> v_img;
            for (auto enter : std::filesystem::directory_iterator("/root/img/playphone/")) {
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
        if (condition)
            printf("playphone time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t9 多线程测打电话
    void thread_function_onphone() {
        gx_onphone_api* api_temp         = new gx_onphone_api();
        gx_head_api* api_head_temp       = new gx_head_api();
        gx_posture_api* api_posture_temp = new gx_posture_api();
        const gx_img_api img("/root/img/onphone.png", static_cast<int>(1e9));
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
        if (condition)
            printf("onphone time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t10 多线程测工服检测
    void thread_function_workcloth() {
        gx_workcloth_api* api_temp = new gx_workcloth_api();
        int T                      = TIMES;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/workcloth.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_workcloth(img, 0);
                if (condition)
                    printf("[workcloth] : workcloth_list = %d\n", val.cloth_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("workcloth time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t12 多线程测行人检测
    void thread_function_pedestrian() {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api();
        int T                       = TIMES;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/pedestrian.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian(img);
                if (condition)
                    printf("[pedestrian] : person_list = %d\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t16 多线程测攀爬
    void thread_function_climb() {
        gx_climb_api* api_temp = new gx_climb_api();
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb(
                    img, abi::vector<climb_point>{
                             climb_point{0, 0}, climb_point{1080, 0}, climb_point{1920, 1080}, climb_point{0, 1920}});
                if (condition)
                    printf(
                        "[climb] : climb_list = %d normal_list = %d\n", val.climb_list.size(), val.normal_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("climb time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t17 多线程测聚众
    void thread_function_crowd() {
        gx_crowd_api* api_temp = new gx_crowd_api();
        int T                  = TIMES;
        for (int i = 0; i < T; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            try {
                const gx_img_api img("/root/img/crowd.jpg", static_cast<int>(1e9));
                // const gx_img_api img("/root/img/crowd.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_crowd(img, 5);
                if (condition)
                    printf("[crowd] : head_list = %d\n", val.head_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            if (condition)
                printf("crowd time = %lld microsecond\n", duration.count());
        }
        delete api_temp;
    }
    // 多线程测偷电瓶
    void thread_function_batterypilferers() {
        gx_batterypilferers_api* api_temp = new gx_batterypilferers_api();
        if (condition)
            printf("-------\n");
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img0("/root/img/batterypilferers/batterypilferers_2.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img0);
                gx_img_api img1("/root/img/batterypilferers/batterypilferers_3.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img1);
                gx_img_api img2("/root/img/batterypilferers/batterypilferers_4.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img2);
                gx_img_api img3("/root/img/batterypilferers/batterypilferers_5.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img3);
                gx_img_api img4("/root/img/batterypilferers/batterypilferers_6.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img4);
                gx_img_api img5("/root/img/batterypilferers/batterypilferers_7.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img5);
                gx_img_api img6("/root/img/batterypilferers/batterypilferers_8.jpg", static_cast<int>(1e9));
                api_temp->safe_production_batterypilferers(img6);
                gx_img_api img7("/root/img/batterypilferers/batterypilferers_9.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_batterypilferers(img7);
                if (condition)
                    printf("[batterypilferers] : score =%f category=%d\n", val.score, val.category);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("batterypilferers time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测打架
    void thread_function_fighting() {
        gx_fighting_api* api_temp = new gx_fighting_api();
        if (condition)
            printf("-------\n");
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img0("/root/img/fighting/fight_0th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img0);
                gx_img_api img1("/root/img/fighting/fight_5th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img1);
                gx_img_api img2("/root/img/fighting/fight_10th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img2);
                gx_img_api img3("/root/img/fighting/fight_15th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img3);
                gx_img_api img4("/root/img/fighting/fight_20th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img4);
                gx_img_api img5("/root/img/fighting/fight_25th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img5);
                gx_img_api img6("/root/img/fighting/fight_30th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img6);
                gx_img_api img7("/root/img/fighting/fight_35th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img7);
                gx_img_api img8("/root/img/fighting/fight_40th.jpg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img8);
                gx_img_api img9("/root/img/fighting/fight_45th.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_fighting(img9);
                if (condition)
                    printf("[fighting] : score =%f category=%d\n", val.score, val.category);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // t20 多线程测姿态
    void thread_function_posture() {
        gx_posture_api* api_temp = new gx_posture_api();
        if (condition)
            printf("-------\n");
        int T      = TIMES;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/posture.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_posture(img);
                if (condition)
                    printf("[posture] : score =%f category=%d\n", val[0].score, val[0].key_points.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        if (condition)
            printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }

} // namespace glasssix

// 处理视频的
namespace glasssix {

    const cv::Scalar RED   = CV_RGB(250, 0, 0); // 红
    const cv::Scalar GREEN = CV_RGB(0, 250, 0); // 绿
    const cv::Scalar WHITE = CV_RGB(255, 255, 255); // 白
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

                if (z > 30) {
                    y++;
                    z %= 30;
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
        gx_climb_api* api_temp = new gx_climb_api();
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
                auto val             = api_temp->safe_production_climb(gx_img_api{abi::string{temp[i]}, 1 << 28},
                                abi::vector<climb_point>{
                        climb_point{0, 0}, climb_point{1920, 0}, climb_point{1920, 1080}, climb_point{0, 1080}});
                cv::Mat img          = cv::imread(abi::string{temp[i]}.c_str());
#if 1
                if (val.climb_list.size() > 0) {
                    std::cout << " I am here: " << std::endl;
                    printf("-------- %s.jpg\t --------\n", temp[i].c_str());
                    for (int j = 0; j < val.climb_list.size(); j++) {
                        int x1      = val.climb_list[j].x1;
                        int x2      = val.climb_list[j].x2;
                        int y1      = val.climb_list[j].y1;
                        int y2      = val.climb_list[j].y2;
                        float score = val.climb_list[j].score;
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
        // try_a_try(name, save_path, data_);//分割视频的,测试目录图片时,可以不使用//! 目前报错,暂不使用
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
//             // gx_img_api img("/root/img/bbb.jpg", static_cast<int>(1e9));
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

    const gx_img_api img_new("/root/img/NULL.jpg", static_cast<int>(1e9));
    const gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
    gx_face_api* temp_api = new gx_face_api();
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
    cv::VideoCapture capture("/root/img/111.gif");

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
        std::string outputName = "/root/img/" + std::to_string(frameCount) + ".jpeg";
        cv::imwrite(outputName, frame);

        frameCount++;
    }

    // 释放 VideoCapture 资源
    capture.release();

    std::cout << "成功解码 GIF 文件，共生成了 " << frameCount << " 张图像" << std::endl;

    return;
}

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        // video_data data_{.be_x = 0, .be_y = 0, .ed_x = 0, .ed_y = 18, .fps = 30};
        // printf("start run video\n");
        // todo_video("/root/video/climb_test.mp4", "/root/video/climb/", "/root/video/climb/ans/", data_);

        // yuv_test();
        // gif_test();

        /* 多线程测性能测试 */
        std::thread t[30];

        t[0]  = std::thread(thread_function_helmet);
        t[1]  = std::thread(thread_function_flame);
        t[2]  = std::thread(thread_function_refvest);
        t[3]  = std::thread(thread_function_search);
        t[4]  = std::thread(thread_function_integration);
        t[5]  = std::thread(thread_function_leavepost);
        t[6]  = std::thread(thread_function_sleep);
        t[7]  = std::thread(thread_function_smoke);
        t[8]  = std::thread(thread_function_playphone);
        t[9]  = std::thread(thread_function_onphone);
        t[10] = std::thread(thread_function_workcloth);
        t[11] = std::thread(thread_function_vehicle);
        t[12] = std::thread(thread_function_pedestrian);
        t[13] = std::thread(thread_function_Action_live_Blur);
        t[14] = std::thread(thread_function_smog);
        t[15] = std::thread(thread_function_tumble);
        t[16] = std::thread(thread_function_climb);
        t[17] = std::thread(thread_function_crowd);
        t[18] = std::thread(thread_function_wander);
        t[19] = std::thread(thread_function_fighting);
        t[20] = std::thread(thread_function_posture);
        t[21] = std::thread(thread_function_wander_limit);
        t[22] = std::thread(thread_function_head);
        t[23] = std::thread(thread_function_batterypilferers);

        t[0].join();
        t[1].join();
        t[2].join();
        t[3].join();
        t[4].join();
        t[5].join();
        t[6].join();
        t[7].join();
        t[8].join();
        t[9].join();
        t[10].join();
        t[11].join();
        t[12].join();
        t[13].join();
        t[14].join();
        t[15].join();
        t[16].join();
        t[17].join();
        t[18].join();
        t[19].join();
        t[20].join();
        t[21].join();
        t[22].join();
        t[23].join();

        auto end      = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        printf("[ ] : the test all cost time : %d seconds\n", duration);
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}
