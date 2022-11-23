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
                // 人脸置信度
                std::cout << "detect score is:" << info.confidence << std::endl;
                // 人脸宽度
                std::cout << "detect mWidth is:" << info.width << std::endl;
                // 人脸高度
                std::cout << "detect mHeight is:" << info.height << std::endl;
                // 中心点X,Y坐标
                std::cout << "detect mCenter_x is:" << info.x + info.width / 2 << std::endl;
                std::cout << "detect mCenter_y is:" << info.y + info.height / 2 << std::endl;

                // 特征点坐标
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

        std::cout << "-------------华丽的分割线-----------------\n";
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
            std::cout << "----------------------检测到 眨眨眼\n";
        else
            std::cout << "未检测到 眨眨眼\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, &img);
        if (action_result)
            std::cout << "----------------------检测到 张张嘴\n ";
        else
            std::cout << "未检测到 张张嘴\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, &img);
        if (action_result)
            std::cout << "----------------------检测到 点点头\n ";
        else
            std::cout << "未检测到 点点头\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, &img);
        if (action_result)
            std::cout << "----------------------检测到 左摇头\n ";
        else
            std::cout << "未检测到 左摇头\n";
        info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, &img);
        if (action_result)
            std::cout << "----------------------检测到 右摇头\n ";
        else
            std::cout << "未检测到 右摇头\n";
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
