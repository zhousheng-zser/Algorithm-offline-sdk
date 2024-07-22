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
            //t[0] = std::jthread(thread_function_helmet);
            //t[1] = std::jthread(thread_function_flame);
            //t[2] = std::jthread(thread_function_refvest);//algorithmzoo  还没有重构
            //t[6] = std::jthread(thread_function_sleep);
            //t[7] = std::jthread(thread_function_smoke);
            //t[8] = std::jthread(thread_function_playphone);
            //t[11] = std::jthread(thread_function_vehicle);//algorithmzoo  还没有重构
            //t[14] = std::jthread(thread_function_smog);
            //t[15] = std::jthread(thread_function_tumble);
            //t[16] = std::jthread(thread_function_climb);
            //t[17] = std::jthread(thread_function_crowd);
            t[18] = std::jthread(thread_function_wander);////algorithmzoo  删库接口还没有重构
            //t[19] = std::jthread(thread_function_fighting);
            //t[22] = std::jthread(thread_function_head);
            //t[23] = std::jthread(thread_function_batterypilferers);
            //t[12] = std::jthread(thread_function_pedestrian); ////没测
            //t[12] = std::jthread(thread_function_pedestrian_min); ////没测
            //t[20] = std::jthread(thread_function_posture);
            //离岗  没测
            //工服  没测
            //泵业灯光  没测
            //泵业防护面罩  没测
            //泵业天车工  没测
            //泵顶安全帽  没测
            //大门关闭  没测
            //狭小空间  没测
            //焊接规范  没测

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