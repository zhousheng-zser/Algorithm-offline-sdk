#include "common.hpp"

using namespace glasssix;

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world -sophon\n");
        auto begin = std::chrono::steady_clock::now();
        // 算丰支持（目前支持）
        // 安全帽、火焰、反光衣、睡岗、抽烟、玩手机、打电话、工服、车辆、行人、离岗、烟雾、跌倒、攀爬、聚众、徘徊、打架斗殴、姿态、越界、人头、偷电瓶、

        /* 多线程测性能测试 */
        if (TIMES > 1) {
            std::jthread t[50];

            t[4]  = std::jthread(thread_function_pedestrian);
            t[5]  = std::jthread(thread_function_head);
            t[6]  = std::jthread(thread_function_posture);
            t[7]  = std::jthread(thread_function_wander);
            t[8]  = std::jthread(thread_function_flame);
            t[9]  = std::jthread(thread_function_refvest);
            t[10] = std::jthread(thread_function_leavepost);
            t[11] = std::jthread(thread_function_sleep);
            t[12] = std::jthread(thread_function_smoke);
            t[13] = std::jthread(thread_function_playphone);
            t[14] = std::jthread(thread_function_onphone);
            t[15] = std::jthread(thread_function_workcloth);
            t[16] = std::jthread(thread_function_vehicle);
            t[17] = std::jthread(thread_function_smog);
            t[18] = std::jthread(thread_function_helmet);
            t[19] = std::jthread(thread_function_fighting);
            t[20] = std::jthread(thread_function_crowd);
            t[23] = std::jthread(thread_function_batterypilferers);
            t[25] = std::jthread(thread_function_climb_tumble_pedestrian_climb);
            t[26] = std::jthread(thread_function_climb_tumble_pedestrian_tumble);
            t[28] = std::jthread(thread_function_policeuniform);

            t[40] = std::jthread(thread_function_pump_light);
            t[41] = std::jthread(thread_function_pump_vesthelmet);
            t[42] = std::jthread(thread_function_pump_gate_status);
            t[43] = std::jthread(thread_function_pump_pumptop_person);
            t[44] = std::jthread(thread_function_pump_mask);
            t[45] = std::jthread(thread_function_pumptop_helmet);
            t[46] = std::jthread(thread_function_pump_hoisting);
            t[47] = std::jthread(thread_function_pump_weld);
            t[48] = std::jthread(thread_function_pump_work_status);

        } else if (TIMES == 1) {
            // 当循环次数为1,进行单线程跑

            thread_function_pedestrian();
            thread_function_head();
            thread_function_posture();
            thread_function_wander();
            thread_function_flame();
            thread_function_refvest();
            thread_function_leavepost();
            thread_function_sleep();
            thread_function_smoke();
            thread_function_playphone();
            thread_function_onphone();
            thread_function_workcloth();
            thread_function_vehicle();
            thread_function_smog();
            thread_function_helmet();
            thread_function_fighting();
            thread_function_crowd();
            thread_function_batterypilferers();
            thread_function_climb_tumble_pedestrian_climb();
            thread_function_climb_tumble_pedestrian_tumble();
            thread_function_policeuniform();

            thread_function_pump_light();
            thread_function_pump_vesthelmet();
            thread_function_pump_gate_status();
            thread_function_pump_pumptop_person();
            thread_function_pump_mask();
            thread_function_pumptop_helmet();
            thread_function_pump_hoisting();
            thread_function_pump_weld();
            thread_function_pump_work_status();

        } else {
        }
        auto end      = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        printf("[ ] : the test all cost time : %d seconds\n", duration);
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}