#include <iostream>
#include <cstdio>
#include "common.hpp"

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        // printf("start run video\n");
        // video_data data_{.be_x = 0, .be_y = 0, .ed_x = 2, .ed_y = 00, .fps = 25};
        // todo_video("/root/video/fighting.mp4", "/root/video/smk/", "/root/video/smk/ans/", data_);

        // yuv_test();
        // gif_test();
        // wangder_limit();
        // crossing("/root/video/192.168.3.225_01_20240313160125612.mp4", "12__");
        // crossing("/root/video/192.168.3.225_01_20240313160432579.mp4", "79__");
        // crossing("/root/video/192.168.3.225_01_20240313160527787.mp4", "87__");
        // crossing("/root/video/192.168.3.225_01_20240313160622539.mp4", "39__");
        // gate_status1();
        // gate_status2();
        // face_test();

        /* 多线程测性能测试 */
        if (TIMES > 1) {
            std::jthread t[50];
            //t[8] = std::jthread(thread_function_playphone);
            //t[14] = std::jthread(thread_function_smog);
            //t[15] = std::jthread(thread_function_tumble);
            //t[16] = std::jthread(thread_function_climb);
            //t[17] = std::jthread(thread_function_crowd);
            //t[19] = std::jthread(thread_function_fighting);
            //t[22] = std::jthread(thread_function_head);
            t[23] = std::jthread(thread_function_batterypilferers);
            //t[12] = std::jthread(thread_function_pedestrian); ////没测
            //t[12] = std::jthread(thread_function_pedestrian_min); ////没测
            //t[20] = std::jthread(thread_function_posture);

        } else {
            // 当循环次数为1,进行单线程跑
              thread_function_smog();
        }

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
    }