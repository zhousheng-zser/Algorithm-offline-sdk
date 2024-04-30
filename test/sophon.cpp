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
#include <gx_flame_api.hpp>
#include <gx_head_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_tumble_api.hpp>
#include <gx_vehicle_api.hpp>
#include <gx_climb_api.hpp>
#include <gx_fighting_api.hpp>
// #include <opencv2/opencv.hpp>
using namespace glasssix;
bool condition = true;
bool condition_time = true;
abi::string config_path = "/home/linaro/jianzhang/glasssix-offline-sdk/config";
#define TIMES 5

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

    // t1 多线程测火焰
    void thread_function_flame() {
        gx_flame_api* api_temp        = new gx_flame_api(config_path);
        std::vector<abi::string> list = find_file("/data/zser/img/");
        std::cout << "thread_function_flame  --------------------------------------------------\n";
        for (int i = 0; i < list.size(); i++) {
            try {
                auto val = api_temp->safe_production_flame(gx_img_api{list[i], 1 << 28});
                for (auto temp : val.fire_list)
                    std::cout << "thread_function_flame  " << temp.x1 << " " << temp.x2 << " " << temp.y1 << " "
                              << temp.y2 << "\n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        delete api_temp;
    }
    void thread_function_tumble() {
        gx_tumble_api* api_temp       = new gx_tumble_api(config_path);
        std::vector<abi::string> list = find_file("/data/zser/img/");
        std::cout << "thread_function_tumble  --------------------------------------------------\n";
        for (int i = 0; i < list.size(); i++) {
            try {
                auto val = api_temp->safe_production_tumble(gx_img_api{list[i], 1 << 28});
                for (auto temp : val.tumble_list)
                    std::cout << "thread_function_tumble  " << temp.x1 << " " << temp.x2 << " " << temp.y1 << " "
                              << temp.y2 << "\n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        delete api_temp;
    }
    void thread_function_helmet() {
        gx_helmet_api* api_temp       = new gx_helmet_api(config_path);
        std::vector<abi::string> list = find_file("/data/zser/img/");
        std::cout << "thread_function_helmet  --------------------------------------------------\n";
        for (int i = 0; i < list.size(); i++) {
            try {
                auto val = api_temp->safe_production_helmet(gx_img_api{list[i], 1 << 28});
                for (auto temp : val.with_helmet_list)
                    std::cout << "thread_function_helmet  " << temp.x1 << " " << temp.x2 << " " << temp.y1 << " "
                              << temp.y2 << "\n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        delete api_temp;
    }
    void thread_function_vehicle() {
        gx_vehicle_api* api_temp      = new gx_vehicle_api(config_path);
        std::vector<abi::string> list = find_file("/data/zser/img/");
        std::cout << "thread_function_vehicle  --------------------------------------------------\n";
        for (int i = 0; i < list.size(); i++) {
            try {
                auto val = api_temp->safe_production_vehicle(gx_img_api{list[i], 1 << 28});
                for (auto temp : val.vehicle_list)
                    std::cout << "thread_function_vehicle  " << temp.x1 << " " << temp.x2 << " " << temp.y1 << " "
                              << temp.y2 << "\n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        delete api_temp;
    }

    void thread_function_climb() {
        gx_climb_api* api_temp = new gx_climb_api(config_path);
        int T                  = TIMES;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/data/zser/img/climb.jpg", static_cast<int>(1e9));
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

        // t19 多线程测打架斗殴
    void thread_function_fighting() {
        try {

            gx_fighting_api* api_temp = new gx_fighting_api(config_path);
            int T                     = TIMES;
            auto start                = std::chrono::high_resolution_clock::now();
            abi::vector<gx_img_api> img_list;
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_0th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_5th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_10th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_15th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_20th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_25th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_30th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_35th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_40th.jpg", static_cast<int>(1e9)));
            img_list.emplace_back(gx_img_api("/data/zser/img/fight_45th.jpg", static_cast<int>(1e9)));
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
    //// t4 多线程测融合搜索
    // void thread_function_integration() {
    //     gx_face_api* api_temp = new gx_face_api(config_path);
    //     // api_temp->user_load();
    //     auto start                    = std::chrono::high_resolution_clock::now();
    //     std::vector<std::string> temp = find_file("/data/zser/img/");
    //     int T                         = TIMES;
    //     for (int i = 0; i < temp.size(); i++) {
    //         try {
    //             auto val = api_temp->detect(gx_img_api{abi::string{temp[i]}, 1 << 28});
    //             std::cout << val.size() << "   \n";
    //         } catch (const std::exception& ex) {
    //             printf("error =  %s\n", ex.what());
    //         }
    //     }
    //     auto end      = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //     printf("integration time = %lld microsecond\n", duration.count());
    //     delete api_temp;
    // }
    //// t13 多线程测 配合活体 与 质量检测
    // void thread_function_Action_live_Blur() {
    //     gx_face_api* api_temp = new gx_face_api();
    //     auto start            = std::chrono::high_resolution_clock::now();
    //     abi::vector<gx_img_api> img;
    //     img.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
    //     img.emplace_back(gx_img_api("/root/img/action_live_1.jpg", IMG_2K));
    //     img.emplace_back(gx_img_api("/root/img/action_live_2.jpg", IMG_2K));
    //     img.emplace_back(gx_img_api("/root/img/action_live_3.jpg", IMG_2K));
    //     img.emplace_back(gx_img_api("/root/img/action_live_4.jpg", IMG_2K));
    //     img.emplace_back(gx_img_api("/root/img/action_live_5.jpg", IMG_2K));
    //     face_info info;
    //     bool action_result = 0;
    //     int T              = TIMES;
    //     while (T--) {
    //         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
    //          printf("BDFACE_ACTION_LIVE_BLINK %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
    //         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result,
    //         img[1]);
    //          printf("BDFACE_ACTION_LIVE_OPEN_MOUTH %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
    //         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
    //          printf("BDFACE_ACTION_LIVE_NOD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
    //         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
    //          printf("BDFACE_ACTION_LIVE_LEFT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
    //         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result,
    //         img[4]);
    //          printf("BDFACE_ACTION_LIVE_RIGHT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
    //         auto val = api_temp->face_blur(img[5]);
    //          printf("blur ====== %.2f\n", val.clarity[0]);
    //     }
    //     auto end      = std::chrono::high_resolution_clock::now();
    //     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    //     if (condition)
    //         printf("pedestrian time = %lld microsecond\n", duration.count());
    //     delete api_temp;
    // }
} // namespace glasssix


int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();
        /* 多线程测性能测试 */
        std::thread t[30];

        printf("????\n");
        //thread_function_flame();
        //thread_function_helmet();
        //thread_function_vehicle();
        //thread_function_tumble();
        thread_function_climb();
        //thread_function_fighting();
        // t[0]  = std::thread(thread_function_helmet);
        // t[1]  = std::thread(thread_function_flame);
        // t[2]  = std::thread(thread_function_refvest);
        // t[3]  = std::thread(thread_function_search);
        // t[4] = std::thread(thread_function_integration);
        // t[5]  = std::thread(thread_function_leavepost);
        // t[6]  = std::thread(thread_function_sleep);
        // t[7]  = std::thread(thread_function_smoke);
        // t[8]  = std::thread(thread_function_playphone);
        // t[9]  = std::thread(thread_function_onphone);
        // t[10] = std::thread(thread_function_workcloth);
        // t[11] = std::thread(thread_function_vehicle);
        // t[12] = std::thread(thread_function_pedestrian);
        // t[13] = std::thread(thread_function_Action_live_Blur);
        // t[14] = std::thread(thread_function_smog);
        // t[15] = std::thread(thread_function_tumble);
        // t[16] = std::thread(thread_function_climb);
        // t[17] = std::thread(thread_function_crowd);
        // t[18] = std::thread(thread_function_wander);
        // t[19] = std::thread(thread_function_fighting);
        // t[20] = std::thread(thread_function_posture);
        // t[21] = std::thread(thread_function_wander_limit);
        // t[22] = std::thread(thread_function_head);
        // t[23] = std::thread(thread_function_batterypilferers);

        // t[0].join();
        // t[1].join();
        // t[2].join();
        // t[3].join();
        // t[4].join();
        // t[5].join();
        // t[6].join();
        // t[7].join();
        // t[8].join();
        // t[9].join();
        // t[10].join();
        // t[11].join();
        // t[12].join();
        // t[13].join();
        // t[14].join();
        // t[15].join();
        // t[16].join();
        // t[17].join();
        // t[18].join();
        // t[19].join();
        // t[20].join();
        // t[21].join();
        // t[22].join();
        // t[23].join();

        auto end      = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        printf("the test all cost time : %d seconds\n", duration);
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}
