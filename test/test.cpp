#include <iostream>
#include <cstdio>
#include "common.hpp"

int main(int argc, char** argv) {
    /* C++ �ӿڲ���*/
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

        /* ���̲߳����ܲ��� */
        if (TIMES > 1) {
            std::jthread t[50];
            //t[0] = std::jthread(thread_function_helmet);
            //t[1] = std::jthread(thread_function_flame);
            //t[2] = std::jthread(thread_function_refvest);//algorithmzoo  ��û���ع�
            //t[6] = std::jthread(thread_function_sleep);
            //t[7] = std::jthread(thread_function_smoke);
            //t[8] = std::jthread(thread_function_playphone);
            //t[11] = std::jthread(thread_function_vehicle);//algorithmzoo  ��û���ع�
            //t[14] = std::jthread(thread_function_smog);
            //t[15] = std::jthread(thread_function_tumble);
            //t[16] = std::jthread(thread_function_climb);
            //t[17] = std::jthread(thread_function_crowd);
            t[18] = std::jthread(thread_function_wander);////algorithmzoo  ɾ��ӿڻ�û���ع�
            //t[19] = std::jthread(thread_function_fighting);
            //t[22] = std::jthread(thread_function_head);
            //t[23] = std::jthread(thread_function_batterypilferers);
            //t[12] = std::jthread(thread_function_pedestrian); ////û��
            //t[12] = std::jthread(thread_function_pedestrian_min); ////û��
            //t[20] = std::jthread(thread_function_posture);
            //���  û��
            //����  û��
            //��ҵ�ƹ�  û��
            //��ҵ��������  û��
            //��ҵ�쳵��  û��
            //�ö���ȫñ  û��
            //���Źر�  û��
            //��С�ռ�  û��
            //���ӹ淶  û��

        } else {
            // ��ѭ������Ϊ1,���е��߳���
              thread_function_smog();
        }

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
    }