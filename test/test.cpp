#include <algorithm>
#include <iostream>

#include <config.h>
#include <gx_face_api.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
// using namespace std;
//
using namespace glasssix::face;


void test_detect(gx_face_api* _api) {

    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        std::vector<face_box> faces;
        faces = _api->gx_detect(&img);
        if (faces.size() > 0) {
            for (int i = 0; i < faces.size(); i++) {
                face_box info = faces[i];
                // �������Ŷ�
                std::cout << "detect score is:" << info.confidence << std::endl;
                // �������
                std::cout << "detect mWidth is:" << info.width << std::endl;
                // �����߶�
                std::cout << "detect mHeight is:" << info.height << std::endl;
                // ���ĵ�X,Y����
                std::cout << "detect mCenter_x is:" << info.x + info.width / 2 << std::endl;
                std::cout << "detect mCenter_y is:" << info.y + info.height / 2 << std::endl;

                // ����������
                for (int j = 0; j < info.landmark.size(); j++) {
                    std::cout << "info.landmark[" << j << "] :" << info.landmark[j].x << std::endl;
                    std::cout << "info.landmark[" << j << "] :" << info.landmark[j].y << std::endl;
                }

                std::cout << "detect eyes glass is:" << info.attributes.glass_index << std::endl;

                rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                    cv::Scalar(255, 255, 255), 2);
            }
        }
        cv::imshow("video-demo", img);
        cv::waitKey(20);
    }
}

void test_track(gx_face_api* _api) {
    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        std::vector<track_face_box> faces;
        faces = _api->gx_track(&img);
        if (faces.size() > 0) {
            for (int i = 0; i < faces.size(); i++) {
                if (faces[i].trace_success == true) {
                    face_box info = faces[i]._face_box;
                    rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                        cv::Scalar(0, 255, 0), 2);
                }
            }
        }
        cv::imshow("video-demo", img);
        cv::waitKey(20);
    }
}

void test_blur(gx_face_api* _api) {
    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        std::vector<blur> faces;
        faces = _api->gx_face_blur(&img);
            for (int i = 0; i < faces.size(); i++) {
            face_box info = faces[i]._face_box;
            std::cout << "detect clarity is:" << faces[i].clarity << std::endl;

            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(0, 255, 0), 2);
            }

        std::cout << "-------------�����ķָ���-----------------\n";
        cv::imshow("video-demo", img);
        cv::waitKey(20);
    }
}


void test_action_live(gx_face_api* _api) {
    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        face_box info;
        int action_result;
        std::string temp;
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, &img);
        if (action_result)
            std::cout << "----------------------��⵽ գգ��\n";
        else
            std::cout << "δ��⵽ գգ��\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, &img);
        if (action_result)
            std::cout << "----------------------��⵽ ������\n ";
        else
            std::cout << "δ��⵽ ������\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, &img);
        if (action_result)
            std::cout << "----------------------��⵽ ���ͷ\n ";
        else
            std::cout << "δ��⵽ ���ͷ\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, &img);
        if (action_result)
            std::cout << "----------------------��⵽ ��ҡͷ\n ";
        else
            std::cout << "δ��⵽ ��ҡͷ\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, &img);
        if (action_result)
            std::cout << "----------------------��⵽ ��ҡͷ\n ";
        else
            std::cout << "δ��⵽ ��ҡͷ\n";
        std::cout << "\n\n";
        rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
            cv::Scalar(0, 255, 0), 2);
        cv::imshow("video-demo", img);
        cv::waitKey(20);
    }
}


int main() {

    // config *x = new config();
    gx_face_api* _api = new gx_face_api();

    // test_detect(_api);
    // test_track(_api);
    // test_blur(_api);
    test_action_live(_api);

    delete _api;
    getchar();
    return 0;
}
