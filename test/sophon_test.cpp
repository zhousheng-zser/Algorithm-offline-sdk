#include "common.hpp"

#include <cstdio>
#include <iostream>

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        /* 多线程测性能测试 */
        if (TIMES > 1) {
            std::jthread t[60];

             //t[0]  = std::jthread(thread_function_search);
            //t[1]  = std::jthread(thread_function_integration);
            //t[2]  = std::jthread(thread_function_face_attributes);
            //t[3]  = std::jthread(thread_function_Action_live_Blur);
            t[4]  = std::jthread(thread_function_pedestrian);
            t[5]  = std::jthread(thread_function_head);
            t[6]  = std::jthread(thread_function_posture);
            //t[7]  = std::jthread(thread_function_wander);
            //t[8]  = std::jthread(thread_function_flame);
            //t[9]  = std::jthread(thread_function_refvest);
            //t[11] = std::jthread(thread_function_sleep);
            //t[12] = std::jthread(thread_function_smoke);
            //t[13] = std::jthread(thread_function_playphone);
            //t[14] = std::jthread(thread_function_onphone);
            //t[15] = std::jthread(thread_function_workcloth);
            //t[16] = std::jthread(thread_function_vehicle);
            //t[17] = std::jthread(thread_function_smog);
            //t[18] = std::jthread(thread_function_helmet);
            //t[19] = std::jthread(thread_function_fighting);
            //t[20] = std::jthread(thread_function_crowd);
            //t[21] = std::jthread(thread_function_wander_limit);
            //t[22] = std::jthread(thread_function_crossing);
            //t[23] = std::jthread(thread_function_batterypilferers);
            //t[24] = std::jthread(thread_function_pedestrian_min);
            //t[25] = std::jthread(thread_function_climb_tumble_pedestrian_climb);
            //t[26] = std::jthread(thread_function_climb_tumble_pedestrian_tumble);
            //t[27] = std::jthread(thread_function_subway_anomaly_nzx);// 只上3588
            //t[28] = std::jthread(thread_function_subway_anomaly_yf);// 只上3588


            //t[40] = std::jthread(thread_function_pump_light);
            //t[41] = std::jthread(thread_function_pump_vesthelmet);
            //t[42] = std::jthread(thread_function_pump_gate_status);
            //t[43] = std::jthread(thread_function_pump_pumptop_person);
            //t[44] = std::jthread(thread_function_pump_mask);
            //t[45] = std::jthread(thread_function_pumptop_helmet);
            //t[46] = std::jthread(thread_function_pump_hoisting);
            //t[47] = std::jthread(thread_function_pump_weld);
            //t[48] = std::jthread(thread_function_pump_work_status);
            //pump_protect_face
            //pump_glove
            //pump_cover_plate


        } else {

            // thread_function_search();
            // thread_function_integration();
            // thread_function_face_attributes();
            // thread_function_Action_live_Blur();
            // thread_function_head();//V
            // thread_function_pedestrian();//V
            // thread_function_posture();//V
            // thread_function_wander();//X
            // thread_function_flame();//V
            // thread_function_refvest();//V
            // thread_function_sleep();//V
            // thread_function_smoke();//V
            // thread_function_playphone();//X
            // thread_function_onphone();//V
            // thread_function_workcloth();
            // thread_function_vehicle();//V
            // thread_function_smog();//V
            // thread_function_helmet();//V
            // thread_function_fighting();//V
            // thread_function_crowd();//V
            // thread_function_wander_limit();//X
            // thread_function_crossing();//X
            // thread_function_batterypilferers();//V
            thread_function_pedestrian_min();
            // thread_function_climb_tumble_pedestrian_climb();//V
            // thread_function_climb_tumble_pedestrian_tumble();//V

             //thread_function_pump_light();
            // thread_function_pump_vesthelmet();
            // thread_function_pump_gate_status();
            // thread_function_pump_pumptop_person();
            // thread_function_pump_mask();
            // thread_function_pumptop_helmet();
            // thread_function_pump_hoisting();
            // thread_function_pump_weld();
            // thread_function_pump_work_status();
            // pump_protect_face
            // pump_glove
            // pump_cover_plate
        }

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}