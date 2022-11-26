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
void test_spoofing_live(gx_face_api* _api) {
    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        std::vector<spoofing> faces;
        faces = _api->gx_face_spoofing_live(&img);
        for (int i = 0; i < faces.size(); ++i) {
            face_box info = faces[i]._face_box;
            std::cout << faces[i].prob[0] << "  " << faces[i].prob[1] << "  " << faces[i].prob[2] << "\n";

            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(200, 255, 0), 2);
        }
        puts("");
        cv::imshow("video-demo", img);
        cv::waitKey(20);
    }
}

void test_feature(gx_face_api* _api) {
    cv::VideoCapture capture;
    capture.open("D:/opencv/2.jpg");
    // while (1)
    {

        cv::Mat img;
        capture >> img;
        std::vector<face_feature> faces;
        faces = _api->gx_face_feature(&img);
        for (int i = 0; i < faces.size(); ++i) {
            face_box info = faces[i]._face_box;

            for (int j = 0; j < faces[i].feature.size(); j++)
                std::cout << " " << faces[i].feature[j];
            std::cout << "\n";
            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(200, 255, 0), 2);
        }
        puts("");
        cv::imshow("video-demo", img);
        // cv::waitKey(20);
        cv::waitKey(0);
    }
}

void test_feature_comparison(gx_face_api* _api) {
    // while (1)
    cv::VideoCapture capture;
    cv::Mat img_a, img_b;
    capture.open("D:/test/img/A/610111200208264510.jpg");
    capture >> img_a;
    capture.open("D:/test/img/B/610111200208264510.jpg");
    capture >> img_b;

    std::vector<face_box> fa = _api->gx_detect(&img_a);
    std::vector<face_box> fb = _api->gx_detect(&img_b);

    std::cout << "fa size=" << fa.size() << " fb size= " << fb.size() << "\n";

    std::vector<face_feature> faces;
    double ans = _api->gx_feature_comparison(&img_a, &img_b);

    std::cout << "feature_comparison: " << ans << std::endl;

    cv::imshow("video-demo", img_b);
    cv::waitKey(20);
    cv::waitKey(0);
}


void test_user(gx_face_api* _api) {

    int flag;
    std::vector<cv::Mat> imgs;
    imgs.push_back(cv::imread("D:/test/img/B/610111200208264510.jpg"));
    imgs.push_back(cv::imread("D:/test/img/A/610111200208264510.jpg"));
    imgs.push_back(cv::imread("D:/test/img/B/410305199405011513.jpg"));
    imgs.push_back(cv::imread("D:/test/img/A/410305199405011513.jpg"));


    std::vector<std::string> keys;
    keys.push_back("B-61011");
    keys.push_back("A-61011");
    keys.push_back("B-41030");
    keys.push_back("A-41030");

    do {
        printf("Input Irisviel key (0-6), (-1 exit): \n");
        scanf_s("%d", &flag);
        if (flag == 0)
            _api->gx_user_load(false); //人员库加载
        else if (flag == 1)
            _api->gx_user_search(&imgs[0], 3, 0.4, false); //人员库搜索
        else if (flag == 2)
            _api->gx_user_clear(false); //人员库清除缓存  清内存
        else if (flag == 3)
            _api->gx_user_remove_all(false); //人员库清空  清内存和磁盘
        else if (flag == 4)
            _api->gx_user_remove_records(keys, false); //人员库批量删除记录
        else if (flag == 5)
            _api->gx_user_add_records(keys, imgs, false); //人员库批量添加记录
        else if (flag == 6) {
            _api->gx_user_update_records(keys, imgs, false); //人员库批量更新记录
        } else
            break;
    } while (flag != -1);
}

void test_detect_integration(gx_face_api* _api) {

    int flag;
    std::vector<cv::Mat> imgs;

    cv::VideoCapture capture;
    capture.open(0);
    while (1) {
        cv::Mat img;
        capture >> img;
        std::vector<face_info> faces = _api->gx_detect_integration(&img, 5, 0.4, false);
        for (int i = 0; i < faces.size(); i++) {

            // 相似度
            std::cout << "detect similarity is:" << faces[i].similarity << std::endl;
            // 键值
            std::cout << "detect key is:" << faces[i].data.key << std::endl;
        }
        std::cout << "\n";

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
    // test_action_live(_api);
    // test_spoofing_live(_api);
    // test_feature(_api);
    // test_feature_comparison(_api);
    // test_user(_api);
    test_detect_integration(_api);
    delete _api;
    getchar();
    return 0;
}
