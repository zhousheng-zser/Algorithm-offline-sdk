#include "common.hpp"

using namespace glasssix;

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        //printf("start run video\n");
        //video_data data_{.be_x = 0, .be_y = 0, .ed_x = 2, .ed_y = 00, .fps = 25};
        //todo_video("/root/video/fighting.mp4", "/root/img/test/person_detection_test/", "/root/img/test/person_detection_test/ans/", data_);

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
        if(TIMES > 1)
        {
            std::jthread t[50];

            //t[0]  = std::jthread(thread_function_helmet);
            // t[1]  = std::jthread(thread_function_flame);
            // t[2]  = std::jthread(thread_function_refvest);
            // t[3]  = std::jthread(thread_function_search);
            // t[4]  = std::jthread(thread_function_integration);
            // t[5]  = std::jthread(thread_function_leavepost);
            // t[6]  = std::jthread(thread_function_sleep);
            // t[7]  = std::jthread(thread_function_smoke);
            // t[8]  = std::jthread(thread_function_playphone);
            // t[9]  = std::jthread(thread_function_onphone);
            // t[10] = std::jthread(thread_function_workcloth);
            // t[11] = std::jthread(thread_function_vehicle);
            // t[12] = std::jthread(thread_function_pedestrian);
            // t[13] = std::jthread(thread_function_Action_live_Blur);
            // t[14] = std::jthread(thread_function_smog);
             //t[15] = std::jthread(thread_function_tumble);
             //t[16] = std::jthread(thread_function_climb);
             t[17] = std::jthread(thread_function_crowd);
             t[18] = std::jthread(thread_function_wander);
             t[19] = std::jthread(thread_function_fighting);
            // // t[20] = std::jthread(thread_function_posture);
            // // t[21] = std::jthread(thread_function_wander_limit);
            // // t[22] = std::jthread(thread_function_head);
             t[23] = std::jthread(thread_function_batterypilferers);
            // // t[24] = std::jthread(thread_function_pump_light);
            // t[25] = std::jthread(thread_function_pump_vesthelmet);
            // t[26] = std::jthread(thread_function_pump_gate_status);
            // t[27] = std::jthread(thread_function_pump_pumptop_person);
            // t[28] = std::jthread(thread_function_pump_mask);
            // t[29] = std::jthread(thread_function_pumptop_helmet);
            // t[30] = std::jthread(thread_function_pump_hoisting);
            // t[31] = std::jthread(thread_function_pump_weld);
            // t[32] = std::jthread(thread_function_face_attributes);
            // t[33] = std::jthread(thread_function_pump_work_status);
            // t[34] = std::jthread(thread_function_crossing);
            // t[35] = std::jthread(thread_function_pedestrian_min);
             //t[36] = std::jthread(thread_function_tumble_pedestrian);
             t[37] = std::jthread(thread_function_climb_tumble_pedestrian_climb);
             t[38] = std::jthread(thread_function_climb_tumble_pedestrian_tumble);

        }
        else
        {
            //当循环次数为1,进行单线程跑

            //thread_function_helmet();
            // thread_function_flame();
            // thread_function_refvest();
            // thread_function_search();
            // thread_function_integration();
            // thread_function_leavepost();
            // thread_function_sleep();
            // thread_function_smoke();
            // thread_function_playphone();
            // thread_function_onphone();
            // thread_function_workcloth();
            // thread_function_vehicle();
            // thread_function_pedestrian();
            // thread_function_pedestrian_min();
            // thread_function_Action_live_Blur();
            // thread_function_smog();
             //thread_function_tumble();
             //thread_function_climb();
             thread_function_crowd();
             thread_function_wander();
             thread_function_fighting();
            // // thread_function_posture();
            // // thread_function_wander_limit();
            // // thread_function_head();
             thread_function_batterypilferers();
            // thread_function_pump_light();
            // thread_function_pump_vesthelmet();
            // thread_function_pump_gate_status();
            // thread_function_pump_pumptop_person();
            // thread_function_pump_mask();
            // thread_function_pumptop_helmet();
            // thread_function_pump_hoisting();
            // thread_function_pump_weld();
            // thread_function_face_attributes();
            // thread_function_pump_work_status();
            // thread_function_crossing();
            //  thread_function_tumble_pedestrian();
             thread_function_climb_tumble_pedestrian_climb();
             thread_function_climb_tumble_pedestrian_tumble();
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