#include "common.hpp"

using namespace glasssix;

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world -sophon\n");
        auto begin = std::chrono::steady_clock::now();
        // 算丰支持
        //(睡岗、聚众、打架斗殴、攀爬、跌倒、工服、反光衣、抽烟、姿态、安全帽、打电话、玩手机、离岗、火焰、人头、烟雾、徘徊、偷电瓶）
        // 车辆、行人、越界（待定）、行人迷你（待定）

        // 算丰支持
        // 安全帽、火焰、反光衣、睡岗、打电话、玩手机、工服、车辆、行人、离岗、烟雾、跌倒、攀爬、聚众、徘徊、打架斗殴、姿态、越界（待定）、人头、偷电瓶、翻越（待定）、行人迷你（待定）

        // 算丰支持（目前支持）
        // 安全帽、火焰、睡岗、车辆、行人、跌倒、攀爬、聚众、徘徊、打架斗殴、姿态、人头、偷电瓶、

        /* 多线程测性能测试 */
        if (TIMES > 1) {
            std::jthread t[50];

            t[0]  = std::jthread(thread_function_helmet);
            t[1]  = std::jthread(thread_function_flame);
            t[2]  = std::jthread(thread_function_refvest);
            t[6]  = std::jthread(thread_function_sleep);
            t[7]  = std::jthread(thread_function_smoke);
            t[8]  = std::jthread(thread_function_playphone);
            t[9]  = std::jthread(thread_function_onphone);
            t[10] = std::jthread(thread_function_workcloth);
            t[11] = std::jthread(thread_function_vehicle);
            t[12] = std::jthread(thread_function_pedestrian);
            t[13] = std::jthread(thread_function_leavepost);
            t[14] = std::jthread(thread_function_smog);
            t[15] = std::jthread(thread_function_tumble);
            t[16] = std::jthread(thread_function_climb);
            t[17] = std::jthread(thread_function_crowd);
            t[18] = std::jthread(thread_function_wander);
            t[19] = std::jthread(thread_function_fighting);
            t[20] = std::jthread(thread_function_posture);
            t[22] = std::jthread(thread_function_head);
            t[23] = std::jthread(thread_function_batterypilferers);

        } else {
            // 当循环次数为1,进行单线程跑

            // thread_function_helmet();
            // thread_function_flame();
            // thread_function_refvest();
            // thread_function_sleep();
            thread_function_smoke();
            // thread_function_playphone();
            // thread_function_onphone();
            // thread_function_workcloth();
            // thread_function_vehicle();
            // thread_function_pedestrian();
            // thread_function_leavepost();
            // thread_function_smog();
            // thread_function_tumble();
            // thread_function_climb();
            // thread_function_crowd();
            // thread_function_wander();
            // thread_function_fighting();
            // thread_function_posture();
            // thread_function_head();
            // thread_function_batterypilferers();
        }

        auto end      = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        printf("the test all cost time : %d seconds\n", duration);
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}