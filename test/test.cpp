#include "common.hpp"

#include <cstdio>
#include <iostream>

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
            std::jthread t[60];

            //t[0]  = std::jthread(thread_function_search);
            //t[1]  = std::jthread(thread_function_integration);
            //t[2]  = std::jthread(thread_function_face_attributes);
            //t[3]  = std::jthread(thread_function_Action_live_Blur);
            //t[4]  = std::jthread(thread_function_pedestrian);//V
            //t[5]  = std::jthread(thread_function_head);//V
            //t[6]  = std::jthread(thread_function_posture);//V
            //t[7]  = std::jthread(thread_function_wander);//X
            //t[8]  = std::jthread(thread_function_flame);//V
            //t[9]  = std::jthread(thread_function_refvest);//V
            //t[11] = std::jthread(thread_function_sleep);//V
            //t[12] = std::jthread(thread_function_smoke);//V
            //t[13] = std::jthread(thread_function_playphone);//X
            //t[14] = std::jthread(thread_function_onphone);//V
            //t[15] = std::jthread(thread_function_workcloth);
            //t[16] = std::jthread(thread_function_vehicle);//V
            //t[17] = std::jthread(thread_function_smog);//V
            //t[18] = std::jthread(thread_function_helmet);//V
            //t[19] = std::jthread(thread_function_fighting);//V
            //t[20] = std::jthread(thread_function_crowd);//V
            //t[21] = std::jthread(thread_function_wander_limit);
            //t[22] = std::jthread(thread_function_crossing);
            //t[23] = std::jthread(thread_function_batterypilferers);
            //t[24] = std::jthread(thread_function_pedestrian_min);//V
            //t[25] = std::jthread(thread_function_climb_tumble_pedestrian_climb);//V
            //t[26] = std::jthread(thread_function_climb_tumble_pedestrian_tumble);//V
            //t[27] = std::jthread(thread_function_subway_anomaly_nzx);
            //t[28] = std::jthread(thread_function_subway_anomaly_yf);


            //t[40] = std::jthread(thread_function_pump_light);
            //t[41] = std::jthread(thread_function_pump_vesthelmet);
            //t[42] = std::jthread(thread_function_pump_gate_status);
            //t[43] = std::jthread(thread_function_pump_pumptop_person);
            //t[44] = std::jthread(thread_function_pump_mask);
            //t[45] = std::jthread(thread_function_pumptop_helmet);
            //t[46] = std::jthread(thread_function_pump_hoisting);
            //t[47] = std::jthread(thread_function_pump_weld);
            //t[48] = std::jthread(thread_function_pump_work_status);


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