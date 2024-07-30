#include "common.hpp"

using namespace glasssix;

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        /* 多线程测性能测试 */
        if(TIMES > 1)
        {
            std::jthread t[50];

            t[17] = std::jthread(thread_function_crowd);
            t[18] = std::jthread(thread_function_wander);
            t[19] = std::jthread(thread_function_fighting);
            t[23] = std::jthread(thread_function_batterypilferers);
            t[37] = std::jthread(thread_function_climb_tumble_pedestrian_climb);
            t[38] = std::jthread(thread_function_climb_tumble_pedestrian_tumble);
            t[39] = std::jthread(thread_function_subway_anomaly_nzx);
            t[40] = std::jthread(thread_function_subway_anomaly_yf);
        }
        else
        {
            //当循环次数为1,进行单线程跑

            thread_function_crowd();
            thread_function_wander();
            thread_function_fighting();
            thread_function_batterypilferers();
            thread_function_climb_tumble_pedestrian_climb();
            thread_function_climb_tumble_pedestrian_tumble();
            thread_function_subway_anomaly_nzx();
            thread_function_subway_anomaly_yf();

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