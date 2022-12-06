#include "../src/nessus/protocols/face_info.hpp"
#include <gx_face_api.h>

#include <algorithm>
#include <iostream>
#include <optional>

#include <io.h>
#include <opencv2/opencv.hpp>
//#include <immintrin.h>
// using namespace std;
//
using namespace glasssix::face;
using namespace glasssix;

namespace glasssix::face {

    void test_detect(gx_face_api* _api) {

        cv::VideoCapture capture;
        capture.open(0);
        int cnt = 0;
        while (1) {
            cnt++;
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            abi::vector<face_info> faces;
            faces = _api->gx_detect(img_buff);
            if (faces.size() > 0) {
                for (int i = 0; i < faces.size(); i++) {
                    face_info info = faces[i];
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

                    // std::cout << "detect eyes glass is:" << info.attributes.glass_index << std::endl;
                    if (info.attributes.has_value())
                        std::cout << "detect eyes glass is:" << info.attributes->glass_index << std::endl;

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
        capture.open("D:/opencv/test/857102359-1-208.mp4");
        while (1) {
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(1024 * 1024);

            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            abi::vector<face_trace_info> faces;
            faces = _api->gx_track(img_buff);
            if (faces.size() > 0) {
                for (int i = 0; i < faces.size(); i++) {
                    if (faces[i].trace_success == true) {
                        std::optional<face_info> info = faces[i].facerectwithfaceinfo;
                        if (info.has_value()) {
                            cv::rectangle(img, cv::Point(info->x, info->y),
                                cv::Point(info->x + info->width, info->y + info->height), cv::Scalar(0, 255, 0), 2);
                            cv::putText(img, faces[i].trace_id.c_str(), cv::Point(info->x, info->y),
                                cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
                        }
                    }
                }
            }
            cv::imshow("video-demo", img);
            cv::waitKey(10);
        }
    }

    void test_blur(gx_face_api* _api) {
        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            faces_blur faces;
            faces = _api->gx_face_blur(img_buff);
            for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); i++) {
                face_info info = faces.facerectwithfaceinfo_list[i];
                std::cout << "detect clarity is:" << faces.clarity[i] << std::endl;

                rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                    cv::Scalar(0, 255, 0), 2);
                cv::putText(img, std::to_string(faces.clarity[i]).c_str(), cv::Point(info.x, info.y),
                    cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
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
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            face_info info;
            bool action_result = 0;
            abi::string temp;
            info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Blink of an eye\n";
            else
                std::cout << "detected fail Blink of an eye\n";
            info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Open mouth\n ";
            else
                std::cout << "detected fail Open mouth\n";
            info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Nutation\n ";
            else
                std::cout << "detected fail Nutation\n";
            info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Left shake head\n ";
            else
                std::cout << "detected fail Left shake head\n";

            info = _api->gx_face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Right shake head\n ";
            else
                std::cout << "detected fail Right shake head\n";
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
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            faces_spoofing faces;
            faces = _api->gx_face_spoofing_live(img_buff);
            for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
                face_info info = faces.facerectwithfaceinfo_list[i];
                std::cout << faces.spoofing_result[i].prob[0] << "  " << faces.spoofing_result[i].prob[1] << "  "
                          << faces.spoofing_result[i].prob[2] << "\n";
                rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                    cv::Scalar(0, 255, 0), 2);
                cv::putText(img, std::to_string(faces.spoofing_result[i].prob[1]).c_str(), cv::Point(info.x, info.y),
                    cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
            }
            cv::imshow("video-demo", img);
            cv::waitKey(20);
        }
    }

    void test_feature(gx_face_api* _api) {

        cv::Mat img = cv::imread("D:/opencv/2.jpg");
        gx_img_api img_path("D:/opencv/2.jpg");
        faces_feature faces;
        faces = _api->gx_face_feature(img_path);
        for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
            face_info info = faces.facerectwithfaceinfo_list[i];

            for (int j = 0; j < faces.features[i].feature.size(); j++)
                std::cout << " " << faces.features[i].feature[j];
            std::cout << "\nsize= " << faces.features[i].feature.size() << "------------\n";
            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(200, 255, 0), 2);
        }
        puts("");
        cv::imshow("video-demo", img);
        // cv::waitKey(20);
        cv::waitKey(0);
    }

    void test_feature_comparison(gx_face_api* _api) {

        gx_img_api img_pathA("D:/test/img/A/610111200208264510.jpg");
        gx_img_api img_pathB("D:/test/img/B/610111200208264510.jpg");
        std::vector<faces_feature> faces;
        double ans = _api->gx_feature_comparison(img_pathA, img_pathB);

        std::cout << "feature_comparison: " << ans << std::endl;

        cv::imshow("video-A", cv::imread("D:/test/img/A/610111200208264510.jpg"));
        cv::imshow("video-B", cv::imread("D:/test/img/B/610111200208264510.jpg"));
        cv::waitKey(20);
        cv::waitKey(0);
    }

    void test_user(gx_face_api* _api) {

        int flag;
        std::vector<gx_img_api> imgs;
        imgs.push_back(gx_img_api("D:/test/img/B/610111200208264510.jpg"));
        imgs.push_back(gx_img_api("D:/test/img/A/610111200208264510.jpg"));


        abi::vector<abi::string> keys;
        keys.push_back("B-----61011");
        keys.push_back("A-----61011");

        do {
            printf("Input Irisviel key (0-6), (-1 exit): \n");
            scanf_s("%d", &flag);
            if (flag == 0)
                _api->gx_user_load(false); //人员库加载
            else if (flag == 1)
                _api->gx_user_search(imgs[0], 5, 0.4, false); //人员库搜索
            else if (flag == 2)
                _api->gx_user_clear(false); //人员库清除缓存  清内存
            else if (flag == 3)
                _api->gx_user_remove_all(false); //人员库清空  清内存和磁盘
            else if (flag == 4)
                _api->gx_user_remove_records(keys, false); //人员库批量删除记录
            else if (flag == 5)
                _api->gx_user_add_records(keys, imgs, false); //人员库批量添加记录
            else if (flag == 6) {
                std::swap(keys[0], keys[1]);
                _api->gx_user_update_records(keys, imgs, false); //人员库批量更新记录
                std::swap(keys[0], keys[1]);
            } else
                break;
        } while (flag != -1);
    }

    void test_detect_integration(gx_face_api* _api) {

        std::vector<cv::Mat> imgs;

        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            faces_search_info faces = _api->gx_detect_integration(img_buff, 5, 0.4, false);
            for (int i = 0; i < faces.result.size(); i++) {

                // 相似度
                std::cout << "detect similarity is:" << faces.result[i].similarity << std::endl;
                // 键值
                std::cout << "detect key is:" << faces.result[i].data.key << std::endl;
            }
            std::cout << "\n";

            cv::imshow("video-demo", img);
            cv::waitKey(20);
        }
    }

    void getFiles(abi::string path, std::vector<abi::string>& files) {
        // 文件句柄
        intptr_t hFile = 0;
        // 文件信息
        struct _finddata_t fileinfo;

        abi::string p;

        if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
            do {

                files.push_back(fileinfo.name);

            } while (_findnext(hFile, &fileinfo) == 0); //寻找下一个，成功返回0，否则-1

            _findclose(hFile);
        }
    }

    void test_add_folder_all(gx_face_api* _api) {
        abi::string working_directory = "D:/test/img_align_celeba";
        std::vector<abi::string> namelist;
        getFiles(working_directory, namelist);
        for (int i = 2; i < namelist.size();) {
            int T = 10000;
            std::vector<gx_img_api> imgs;
            abi::vector<abi::string> keys;
            while (T--) {
                imgs.push_back(gx_img_api(working_directory + "/" + namelist[i]));
                keys.push_back(namelist[i]);
                i++;
            }
            _api->gx_user_add_records(keys, imgs, false);
        }
    }

} // namespace glasssix::face
int main() {

    try {
        gx_face_api* _api = new gx_face_api();
        // test_detect(_api);
         test_track(_api);
        //  test_blur(_api);
        //  test_action_live(_api);
        //  test_spoofing_live(_api);
        //  test_feature(_api);
        //  test_feature_comparison(_api);
        // test_user(_api);
        // test_detect_integration(_api);
        //  test_add_folder_all(_api); // 入库文件夹内全部人脸

        delete _api;
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "---------------------------\n";
    }
    getchar();
    return 0;
}
