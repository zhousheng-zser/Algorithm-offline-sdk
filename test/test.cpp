#include "common.hpp"

using namespace glasssix;

int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        auto begin = std::chrono::steady_clock::now();

        //printf("start run video\n");
        //std::string module{"smoke/"};
        //video_data data_{.be_x = 0, .be_y = 0, .ed_x = 2, .ed_y = 00, .fps = 25};
        //todo_video(
        //    "/root/video/fighting.mp4", "/root/img/test/" + module, "/root/img/test/" + module + "ans/", data_);

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

        //subway_anomaly_test("/root/img/test/a_screenshot/a_screenshot/a.mp4_20240715_155244.109.png", "/root/img/test/a_screenshot/a.mp4_20240715_155244.109.png");
        //subway_anomaly_test("/root/img/test/a_screenshot/a_screenshot/a.mp4_20240715_155249.277.png", "/root/img/test/a_screenshot/a.mp4_20240715_155249.277.png");
        //subway_anomaly_test("/root/img/test/a_screenshot/a_screenshot/a.mp4_20240715_155251.095.png", "/root/img/test/a_screenshot/a.mp4_20240715_155251.095.png");
        //subway_anomaly_test("/root/img/test/a_screenshot/a_screenshot/a.mp4_20240715_155258.323.png", "/root/img/test/a_screenshot/a.mp4_20240715_155258.323.png");
        //subway_anomaly_test("/root/img/test/a_screenshot/a_screenshot/a.mp4_20240715_155300.062.png", "/root/img/test/a_screenshot/a.mp4_20240715_155300.062.png");

        //make_video("/root/img/test/ori_result_a.mp4", "/root/img/test/b.mp4");
        /* 多线程测性能测试 */
        if(TIMES > 1)
        {
            std::jthread t[60];

            //t[0]  = std::jthread(thread_function_search);
            //t[1]  = std::jthread(thread_function_integration);
            //t[2]  = std::jthread(thread_function_face_attributes);
            //t[3]  = std::jthread(thread_function_Action_live_Blur);
            //t[4]  = std::jthread(thread_function_pedestrian);
            //t[5]  = std::jthread(thread_function_head);
            //t[6]  = std::jthread(thread_function_posture);
            //t[7]  = std::jthread(thread_function_wander);
            //t[8]  = std::jthread(thread_function_flame);
            //t[9]  = std::jthread(thread_function_refvest);
            //t[10] = std::jthread(thread_function_leavepost);
            //t[11] = std::jthread(thread_function_sleep);
            //t[12] = std::jthread(thread_function_smoke);
            t[13] = std::jthread(thread_function_playphone);
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
            //t[27] = std::jthread(thread_function_subway_anomaly_nzx);
            //t[28] = std::jthread(thread_function_subway_anomaly_yf);

            //t[40] = std::jthread(thread_function_pump_light);
            //t[41] = std::jthread(thread_function_pump_vesthelmet);
            //t[42] = std::jthread(thread_function_pump_gate_status);
            //t[43] = std::jthread(thread_function_pump_pumptop_person);
            //t[44] = std::jthread(thread_function_pump_mask);
            t[45] = std::jthread(thread_function_pumptop_helmet);
            //t[46] = std::jthread(thread_function_pump_hoisting);
            //t[47] = std::jthread(thread_function_pump_weld);
            //t[48] = std::jthread(thread_function_pump_work_status);

        } else if (TIMES == 1)
        {
            //当循环次数为1,进行单线程跑

            //thread_function_search();
            //thread_function_integration();
            //thread_function_face_attributes();
            //thread_function_Action_live_Blur();
            //thread_function_pedestrian();
            //thread_function_head();
            //thread_function_posture();
            //thread_function_wander();
            //thread_function_flame();
            //thread_function_refvest();
            //thread_function_leavepost();
            //thread_function_sleep();
            //thread_function_smoke();
            thread_function_playphone();
            //thread_function_onphone();
            //thread_function_workcloth();
            //thread_function_vehicle();
            //thread_function_smog();
            //thread_function_helmet();
            //thread_function_fighting();
            //thread_function_crowd();
            //thread_function_wander_limit();
            //thread_function_crossing();
            //thread_function_batterypilferers();
            //thread_function_pedestrian_min();
            //thread_function_climb_tumble_pedestrian_climb();
            //thread_function_climb_tumble_pedestrian_tumble();
            //thread_function_subway_anomaly_nzx();
            //thread_function_subway_anomaly_yf();

            //thread_function_pump_light();
            //thread_function_pump_vesthelmet();
            //thread_function_pump_gate_status();
            //thread_function_pump_pumptop_person();
            //thread_function_pump_mask();
            thread_function_pumptop_helmet();
            //thread_function_pump_hoisting();
            //thread_function_pump_weld();
            //thread_function_pump_work_status();

        } else
        {}
        auto end      = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - begin).count();
        printf("[ ] : the test all cost time : %d seconds\n", duration);
    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}