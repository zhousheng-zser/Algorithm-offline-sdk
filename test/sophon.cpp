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
#include <gx_face_api.hpp>
// #include <opencv2/opencv.hpp>
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
    // t4 多线程测融合搜索
    void thread_function_integration() {
        gx_face_api* api_temp = new gx_face_api("/data/zser/glasssix-offline-sdk/config");
        // api_temp->user_load();
        auto start                    = std::chrono::high_resolution_clock::now();
        std::vector<std::string> temp = find_file_test("/data/zser/img/");
        int T                         = TIMES;
        for (int i = 0; i < temp.size(); i++) {
            try {
                auto val = api_temp->detect(gx_img_api{abi::string{temp[i]}, 1 << 28});
                std::cout << val.size() << "   \n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("integration time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
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

        // t[0]  = std::thread(thread_function_helmet);
        // t[1]  = std::thread(thread_function_flame);
        // t[2]  = std::thread(thread_function_refvest);
        // t[3]  = std::thread(thread_function_search);
        t[4] = std::thread(thread_function_integration);
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
        t[4].join();
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
