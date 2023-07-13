#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <thread>

// #include <gtest/gtest.h>
#include <gx_api.hpp>
#include <gx_face_api.hpp>
#include <gx_flame_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_leavepost_api.hpp>
#include <gx_refvest_api.hpp>
#include <gx_sleep_api.hpp>
#include <gx_smoke_api.hpp>
// #include <gx_api_c.hpp>
using namespace glasssix;

// 用于windows 播放显示
/*
namespace glasssix::display_test {
    void test_detect(gx_api* _api) {

        cv::VideoCapture capture;
        capture.open("D:/test/img/20230115-092810.jpg");
        int cnt = 0;
        while (1) {
            cnt++;
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            abi::vector<face_info> faces;
            faces = _api->detect(img_buff);
            if (faces.size() > 0) {
                for (int i = 0; i < faces.size(); i++) {
                    face_info info = faces[i];
                    // 人脸置信度
                    printf("detect score is:" << info.confidence << std::endl;
                    // 人脸宽度
                    printf("detect mWidth is:" << info.width << std::endl;
                    // 人脸高度
                    printf("detect mHeight is:" << info.height << std::endl;
                    // 中心点X,Y坐标
                    printf("detect mCenter_x is:" << info.x + info.width / 2 << std::endl;
                    printf("detect mCenter_y is:" << info.y + info.height / 2 << std::endl;

                    // 特征点坐标
                    for (int j = 0; j < info.landmark.size(); j++) {
                        printf("info.landmark[" << j << "] :" << info.landmark[j].x << std::endl;
                        printf("info.landmark[" << j << "] :" << info.landmark[j].y << std::endl;
                    }

                    // printf("detect eyes glass is:" << info.attributes.glass_index << std::endl;
                    if (info.attributes.has_value())
                        printf("detect eyes glass is:" << info.attributes->glass_index << std::endl;

                    rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                        cv::Scalar(255, 255, 255), 2);
                }
            }
            cv::imshow("video-demo", img);
            cv::waitKey(0);
        }
    }

    void test_track(gx_api* _api) {
        cv::VideoCapture capture;
        capture.open("D:/test/video/123456.mp4");
        while (1) {
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(1024 * 1024);

            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            abi::vector<face_trace_info> faces;
            faces = _api->track(img_buff);
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

    void test_blur(gx_api* _api) {
        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            faces_blur faces;
            faces = _api->face_blur(img_buff);
            for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); i++) {
                face_info info = faces.facerectwithfaceinfo_list[i];
                printf("detect clarity is:" << faces.clarity[i] << std::endl;

                rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                    cv::Scalar(0, 255, 0), 2);
                cv::putText(img, std::to_string(faces.clarity[i]).c_str(), cv::Point(info.x, info.y),
                    cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
            }

            printf(U8("-------------------------------------\n");
            cv::imshow("video-demo", img);
            cv::waitKey(20);
        }
    }

    void test_action_live(gx_api* _api) {
        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            face_info info;
            bool action_result = 0;
            abi::string temp;
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img_buff);
            if (action_result)
                printf("----------------------detected success Blink of an eye\n";
            else
                printf("detected fail Blink of an eye\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img_buff);
            if (action_result)
                printf("----------------------detected success Open mouth\n ";
            else
                printf("detected fail Open mouth\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img_buff);
            if (action_result)
                printf("----------------------detected success Nutation\n ";
            else
                printf("detected fail Nutation\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img_buff);
            if (action_result)
                printf("----------------------detected success Left shake head\n ";
            else
                printf("detected fail Left shake head\n";

            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img_buff);
            if (action_result)
                printf("----------------------detected success Right shake head\n ";
            else
                printf("detected fail Right shake head\n";
            printf("\n\n";
            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(0, 255, 0), 2);
            cv::imshow("video-demo", img);
            cv::waitKey(20);
        }
    }

    void test_spoofing_live(gx_api* _api) {
        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            faces_spoofing faces;
            faces = _api->face_spoofing_live(img_buff);
            for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
                face_info info = faces.facerectwithfaceinfo_list[i];
                printf(faces.spoofing_result[i].prob[0] << "  " << faces.spoofing_result[i].prob[1] << "  "
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

    void test_feature(gx_api* _api) {

        cv::Mat img = cv::imread("D:/test/img/20221208.jpg");
        gx_img_api img_path("D:/test/img/20221208.jpg", IMG_2K);
        abi::vector<faces_feature> faces;
        faces = _api->face_feature(img_path, false);
        for (int i = 0; i < faces[0].facerectwithfaceinfo_list.size(); ++i) {
            face_info info = faces[0].facerectwithfaceinfo_list[i];

            for (int j = 0; j < faces[0].features[i].feature.size(); j++)
                printf(" " << faces[0].features[i].feature[j];
            printf("\nsize= " << faces[0].features[i].feature.size() << "------------\n";
            rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                cv::Scalar(200, 255, 0), 2);
        }
        puts("");
        cv::imshow("video-demo", img);
        // cv::waitKey(20);
        cv::waitKey(0);
    }

    void test_feature_comparison(gx_api* _api) {

        gx_img_api img_pathA("D:/test/img/A/610111200208264510.jpg", IMG_2K);
        gx_img_api img_pathB("D:/test/img/B/610111200208264510.jpg", IMG_2K);
        double ans = _api->feature_comparison(img_pathA, img_pathB);

        printf("feature_comparison: " << ans << std::endl;

        cv::imshow("video-A", cv::imread("D:/test/img/A/610111200208264510.jpg"));
        cv::imshow("video-B", cv::imread("D:/test/img/B/610111200208264510.jpg"));
        cv::waitKey(20);
        cv::waitKey(0);
    }

    void test_user(gx_api* _api) {

        int flag;
        abi::vector<gx_img_api> imgs;
        imgs.push_back(gx_img_api("D:/test/img/B/610111200208264510.jpg"));
        imgs.push_back(gx_img_api("D:/test/img/A/610111200208264510.jpg"));

        abi::vector<abi::vector<float>> features;
        abi::vector<abi::string> keys;
        keys.push_back("B-----61011");
        keys.push_back("A-----61011");

        do {
            printf("Input Irisviel key (0-6), (-1 exit): \n");
            scanf_s("%d", &flag);
            if (flag == 0)
                _api->user_load(); // 人员库加载
            else if (flag == 1)
                _api->user_search(imgs[0], 5, 0.1f); // 人员库搜索
            else if (flag == 2)
                _api->user_remove_all(); // 人员库清空  清内存和磁盘
            else if (flag == 3)
                _api->user_remove_records(keys); // 人员库批量删除记录
            else if (flag == 4)
                _api->user_add_records(keys, imgs, false, false); // 人员库批量添加记录
            else if (flag == 5)
                _api->user_add_records(keys, features); // 人员库批量添加记录
            else
                break;
        } while (flag != -1);
    }

    void test_detect_integration(gx_api* _api) {

        std::vector<cv::Mat> imgs;

        cv::VideoCapture capture;
        capture.open(0);
        while (1) {
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_2K);
            faces_integration_search_info faces = _api->detect_integration(img_buff, 5, 0.4f);
            for (int i = 0; i < faces.result.size(); i++) {

                // 相似度
                printf("detect similarity is:" << faces.result[i].similarity << std::endl;
                // 键值
                printf("detect key is:" << faces.result[i].data.key << std::endl;
            }
            printf("\n";

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
                if (strcmp(fileinfo.name, "..") == 0 || strcmp(fileinfo.name, ".") == 0)
                    continue;
                if (fileinfo.attrib == _A_SUBDIR) {
                    getFiles(path + "/" + fileinfo.name, files);
                    continue;
                }
                files.push_back(path + "/" + fileinfo.name);

            } while (_findnext(hFile, &fileinfo) == 0); // 寻找下一个，成功返回0，否则-1

            _findclose(hFile);
        }
    }

    void test_add_folder_all(gx_api* _api) {
        abi::string working_directory = "D:/test/img_align_celeba";
        std::vector<abi::string> namelist;
        getFiles(working_directory, namelist);
        for (int i = 2; i < namelist.size();) {
            int T = 500;
            abi::vector<gx_img_api> imgs;
            abi::vector<abi::string> keys;
            while (T--) {
                imgs.push_back(gx_img_api(working_directory + "/" + namelist[i]));
                keys.push_back(namelist[i]);
                i++;
            }
            _api->user_add_records(keys, imgs, false, false);
        }
    }

} // namespace glasssix::display_test
*/

// 人脸 GoogleTest
namespace glasssix {

    // gx_face_api* api = new gx_face_api();
    ////人脸检测
    //   TEST(Api, Detect) {
    //       gx_img_api img("/root/img/20221209.jpg", IMG_2K);
    //       abi::vector<face_info> faces;
    //       faces          = api->detect(img);
    //       face_info info = faces[0];
    //       EXPECT_GE(info.confidence, 0);
    //       EXPECT_LE(info.confidence, 1);
    //       EXPECT_GT(info.width, 0);
    //       EXPECT_GT(info.height, 0);
    //       EXPECT_EQ(info.landmark.size(), 5);
    //       EXPECT_TRUE(info.attributes.has_value());
    //       EXPECT_EQ(info.attributes->glass_index, 0);
    //       EXPECT_EQ(info.attributes->mask_index, 0);
    //       EXPECT_GT(info.attributes->yaw, -90.0);
    //       EXPECT_LT(info.attributes->yaw, 90.0);
    //       EXPECT_GT(info.attributes->pitch, -90.0);
    //       EXPECT_LT(info.attributes->pitch, 90.0);
    //       EXPECT_GT(info.attributes->roll, -90.0);
    //       EXPECT_LT(info.attributes->roll, 90.0);
    //   }

    //   // 人脸追踪
    //    TEST(Api, Track) {
    //        gx_img_api img("/root/img/000011.jpg", IMG_2K);
    //        abi::vector<face_trace_info> faces;
    //        faces = api->track(img);
    //        EXPECT_GT(faces.size(), 0);
    //        for (int i = 0; i < faces.size(); i++) {
    //            EXPECT_TRUE(faces[i].trace_success);
    //            std::optional<face_info> info = faces[i].facerectwithfaceinfo;
    //            EXPECT_TRUE(info.has_value());
    //            EXPECT_GE(info->confidence, 0);
    //            EXPECT_LE(info->confidence, 1);
    //            EXPECT_GT(info->width, 0);
    //            EXPECT_GT(info->height, 0);
    //            EXPECT_EQ(info->landmark.size(), 5);
    //            EXPECT_EQ(info->attributes->glass_index, 0);
    //            EXPECT_EQ(info->attributes->mask_index, 0);
    //            EXPECT_GT(info->attributes->yaw, -90.0);
    //            EXPECT_LT(info->attributes->yaw, 90.0);
    //            EXPECT_GT(info->attributes->pitch, -90.0);
    //            EXPECT_LT(info->attributes->pitch, 90.0);
    //            EXPECT_GT(info->attributes->roll, -90.0);
    //            EXPECT_LT(info->attributes->roll, 90.0);
    //        }
    //    }

    //   // 人脸质量检测
    //   TEST(Api, Face_blur) {
    //        gx_img_api img("/root/img/20230323.png", IMG_2K);
    //       faces_blur faces;
    //       faces = api->face_blur(img);
    //       EXPECT_GT(faces.facerectwithfaceinfo_list.size(), 0);
    //       for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); i++) {
    //           // face_info info = faces.facerectwithfaceinfo_list[i]; 前面测过了
    //           EXPECT_GE(faces.clarity[i], 0.0);
    //           EXPECT_LE(faces.clarity[i], 1.0);
    //       }
    //   }

    //   // 配合活体检测
    //    TEST(Api, Face_action_live) {
    //        abi::vector<gx_img_api> img;
    //        img.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/action_live_1.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/action_live_2.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/action_live_3.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/action_live_4.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/action_live_5.jpg", IMG_2K));
    //        face_info info;
    //        bool action_result = 0;
    //        info               = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result,
    //        img[0]); EXPECT_TRUE(action_result); info =
    //        api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
    //        EXPECT_FALSE(action_result);
    //        printf("ans = %d\n", action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
    //        EXPECT_TRUE(action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
    //        EXPECT_FALSE(action_result);
    //        printf("ans = %d\n", action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
    //        EXPECT_TRUE(action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
    //        EXPECT_FALSE(action_result);
    //        printf("ans = %d\n", action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
    //        EXPECT_TRUE(action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
    //        EXPECT_FALSE(action_result);
    //        printf("ans = %d\n", action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
    //        EXPECT_TRUE(action_result);
    //        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
    //        EXPECT_FALSE(action_result);
    //        printf("ans = %d\n", action_result);
    //    }

    //   // 静默活体检测
    //   TEST(Api, Face_spoofing_live) {
    //       abi::vector<gx_img_api> img;
    //        img.emplace_back(gx_img_api("/root/img/33333.jpg", IMG_2K));
    //       img.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
    //        img.emplace_back(gx_img_api("/root/img/spoofing_2.jpg", IMG_2K));
    //       faces_spoofing faces;
    //       faces = api->face_spoofing_live(img[0]);
    //       for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
    //           //   EXPECT_GE(faces.spoofing_result[i].prob[2], 0.5);  //现在画像算活体
    //       }
    //       faces = api->face_spoofing_live(img[1]);
    //       for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
    //           EXPECT_GE(faces.spoofing_result[i].prob[1], 0.5);
    //       }
    //       faces = api->face_spoofing_live(img[2]);
    //       for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
    //           EXPECT_GE(faces.spoofing_result[i].prob[0], 0.5);
    //       }
    //   }

    //   // 特征值提取
    //   TEST(Api, Face_feature) {
    //       gx_img_api img("/root/img/20221209.jpg", IMG_2K);
    //       faces_feature faces;
    //       faces = api->face_feature(img, false);
    //       EXPECT_EQ(faces.facerectwithfaceinfo_list.size(), faces.features.size());
    //       for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
    //           EXPECT_EQ(faces.features[i].feature.size(), 256);
    //           for (int j = 0; j < faces.features[i].feature.size(); j++) {
    //               EXPECT_GT(faces.features[i].feature[j], -1.0);
    //               EXPECT_LT(faces.features[i].feature[j], 1.0);
    //           }
    //       }
    //   }

    //   // 1:1 人脸对比
    //   TEST(Api, gx_feature_comparison) {
    //       gx_img_api img_pathA("/root/img/action_live_1.jpg", IMG_2K);
    //       gx_img_api img_pathB("/root/img/action_live_5.jpg", IMG_2K);
    //       double ans1 = api->feature_comparison(img_pathA, img_pathB);
    //       EXPECT_GT(ans1, 0.9);
    //        gx_img_api A("/root/img/A.png", IMG_2K);
    //       gx_img_api B("/root/img/B.png", IMG_2K);
    //        gx_img_api C("/root/img/C.png", IMG_2K);
    //        double ans_ab, ans_ac, ans_bc;
    //        ans_ac = api->feature_comparison(A, C);
    //        ans_ab = api->feature_comparison(A, B);
    //        ans_bc = api->feature_comparison(C, B);
    //        EXPECT_GT(ans_ab, ans_ac);
    //        EXPECT_GT(ans_ab, ans_bc);
    //   }

    //   // 人脸特征值底库 + 融合人脸识别
    //   TEST(Api, gx_user_and_detect_integration) {
    //       abi::vector<gx_img_api> imgs;
    //       imgs.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
    //       imgs.emplace_back(gx_img_api("/root/img/action_live_1.jpg", IMG_2K));
    //       imgs.emplace_back(gx_img_api("/root/img/action_live_2.jpg", IMG_2K));
    //       imgs.emplace_back(gx_img_api("/root/img/action_live_3.jpg", IMG_2K));
    //       imgs.emplace_back(gx_img_api("/root/img/action_live_4.jpg", IMG_2K));
    //       abi::vector<abi::string> keys;
    //       keys.emplace_back("action_live_0");
    //       keys.emplace_back("action_live_1");
    //       keys.emplace_back("action_live_2");
    //       keys.emplace_back("action_live_3");
    //       keys.emplace_back("action_live_4");
    //       abi::vector<face_user_result> result;
    //       faces_search_info faces;
    //       faces_integration_search_info faces_i;
    //       gx_img_api img("/root/img/action_live_5.jpg", IMG_2K);
    //       api->user_load(); // 人员库加载
    //       result = api->user_add_records(keys, imgs, false, false); // 人员库批量添加记录
    //       EXPECT_EQ(result.size(), 5);
    //       for (int i = 0; i < result.size(); i++)
    //           EXPECT_EQ(result[i].success, 0);
    //       faces = api->user_search(img, 5, 0.6f); // 人员库搜索
    //       ASSERT_LE(faces.result.size(), 5);
    //       for (int i = 0; i < faces.result.size(); i++) {
    //           EXPECT_GE(faces.result[i].similarity, 0.6);
    //       }
    //       ASSERT_STREQ(faces.result[0].data.key.c_str(), "action_live_0");
    //       faces_i = api->detect_integration(img, 5, 0.6f); // 融合人脸识别
    //       ASSERT_LE(faces_i.result.size(), 5);
    //       for (int i = 0; i < faces_i.result.size(); i++) {
    //           EXPECT_GE(faces_i.result[i].similarity, 0.6);
    //       }
    //       ASSERT_STREQ(faces_i.result[0].data.key.c_str(), "action_live_0");
    //       result = api->user_add_records(keys, imgs, false, false); // 已存在再批量添加则更新
    //       EXPECT_EQ(result.size(), 5);
    //       for (int i = 0; i < result.size(); i++)
    //           EXPECT_EQ(result[i].success, 0);
    //       api->user_remove_records(keys); // 人员库批量删除记录
    //       faces = api->user_search(img, 5, 0.4f); // 人员库搜索
    //       ASSERT_LE(faces.result.size(), 0);
    //       api->user_remove_all(); // 人员库清空  清内存和磁盘
    //   }

} // namespace glasssix

// 帮测试写的测试工具
namespace glasssix {


    std::vector<abi::string> find_file(std::filesystem::path folder_path) {
        std::vector<abi::string> ans_list;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
                std::string temp(entry.path());
                ans_list.emplace_back(temp);
            }
        }
        return ans_list;
    }
    //    // 安全生产指标测试 烟火
    //    //void safe_test1() {
    //    //    std::ofstream safe_file("./flame.log", std::ios::out | std::ios::trunc);
    //    //    // std::filesystem::path folder_path          = "/root/img/production/fire";
    //    //    std::filesystem::path folder_path = "/root/img/production/no_flame";
    //    //    std::vector<abi::string> img_list = find_file(folder_path);
    //    //    for (int i = 0; i < img_list.size(); ++i) {
    //    //        safe_file << img_list[i] << "#";
    //    //        try {
    //    //            gx_img_api img(img_list[i], 1 << 30);
    //    //            auto val = api->safe_production_flame(img);
    //    //            safe_file << val;
    //    //        } catch (const std::exception& ex) {
    //    //            safe_file << ex.what();
    //    //        }
    //    //        safe_file << "\n";
    //    //    }
    //    //}
    //    // 安全生产指标测试 反光衣
    //    //void safe_test2() {
    //    //    std::ofstream safe_file("./refvest.log", std::ios::out | std::ios::trunc);
    //    //    std::filesystem::path folder_path = "/root/img/production/ref_benchmark";
    //    //    std::vector<abi::string> img_list = find_file(folder_path);
    //    //    for (int i = 0; i < img_list.size(); ++i) {
    //    //        safe_file << img_list[i] << "#";
    //    //        try {
    //    //            gx_img_api img(img_list[i], 1 << 30);
    //    //            auto val = api->safe_production_refvest(img);
    //    //            safe_file << val;
    //    //        } catch (const std::exception& ex) {
    //    //            safe_file << ex.what();
    //    //        }
    //    //        safe_file << "\n";
    //    //    }
    //    //}
    //    // 安全生产指标测试 安全帽
    //    //void safe_test3() {
    //    //    std::ofstream safe_file("./helmet.log", std::ios::out | std::ios::trunc);
    //    //    std::filesystem::path folder_path = "/root/img/production/val2017";
    //    //    std::vector<abi::string> img_list = find_file(folder_path);
    //    //    for (int i = 0; i < img_list.size(); ++i) {
    //    //        safe_file << img_list[i] << "#";
    //    //        try {
    //    //            gx_img_api img(img_list[i], 1 << 30);
    //    //            auto val = api->safe_production_helmet(img);
    //    //            safe_file << val;
    //    //        } catch (const std::exception& ex) {
    //    //            safe_file << ex.what();
    //    //        }
    //    //        safe_file << "\n";
    //    //    }
    //    //}
    //
    // 多线程测安全帽
    void thread_function_helmet() {
        gx_helmet_api* api_temp = new gx_helmet_api();
        int T                   = 1000;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/helmet.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_helmet(img);
                printf("with_helmet_list = %d without_helmet_list = %d\n", val.with_helmet_list.size(),
                    val.without_helmet_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("helmet time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测火焰
    void thread_function_flame() {
        gx_flame_api* api_temp = new gx_flame_api();
        int T                  = 1000;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/flame.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_flame(img);
                printf("fire_list = %d smoke_list = %d\n", val.fire_list.size(), val.smoke_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("flame time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测反光衣
    void thread_function_refvest() {
        gx_refvest_api* api_temp = new gx_refvest_api();
        int T                    = 1000;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/refvest.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_refvest(img);
                printf("without_refvest_list = %d with_refvest_list = %d\n", val.without_refvest_list.size(),
                    val.with_refvest_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("refvest time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测搜索
    void thread_function_search() {
        gx_face_api* api_temp = new gx_face_api();
        api_temp->user_load();
        int T      = 500;
        auto start = std::chrono::high_resolution_clock::now();
        while (T--) {
            try {
                gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->user_search(img, 1, 0.5);
                // printf(val.dump() << "\n";
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("search time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测融合搜索
    void thread_function_integration() {
        gx_face_api* api_temp = new gx_face_api();
        api_temp->user_load();
        auto start = std::chrono::high_resolution_clock::now();
        int T      = 500;
        while (T--) {
            try {
                //gx_img_api img("/root/img/bbb.jpg", static_cast<int>(1e9));
                gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);
                // printf(val.dump() << "\n";

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("integration time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 人脸入库
    void test_add_face_all() {
        gx_face_api* _api = new gx_face_api();
        _api->user_load();
        printf(" const = %d \n", _api->user_record_count());
        std::ifstream path_file("/home/paths.txt", std::ios::in);
        abi::string path, key;
        while (1) {
            abi::vector<abi::string> keys;
            abi::vector<gx_img_api> mat;
            int T = 1000;
            while ((path_file >> path >> key) && (T--)) {
                try {
                    mat.emplace_back(gx_img_api{"/home/" + path, static_cast<int>(1e9)});
                    keys.emplace_back(key);
                } catch (const std::exception& ex) {
                    printf("error = %s\n", ex.what());
                }
            }
            if (mat.size() == 0) {
                break;
            } else {
                auto val = _api->user_add_records(keys, mat, false, false);
                printf("T = %d \n", T);
            }
        }
    }
    // 多线程测睡岗
    void thread_function_sleep() {
        gx_sleep_api* api_temp = new gx_sleep_api();
        int T                  = 1000;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/sleep.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_sleep(img);
                printf("desk_list = %d lying_list = %d standing_list = %d work_list = %d\n", val.desk_list.size(),
                    val.lying_list.size(), val.standing_list.size(), val.work_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("sleep time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测抽烟
    void thread_function_smoke() {
        gx_smoke_api* api_temp = new gx_smoke_api();
        int T                  = 1000;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/smoke.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smoke(img);
                printf("norm_list = %d smoke_list = %d\n", val.norm_list.size(), val.smoke_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("smoke time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测离岗
    void thread_function_leavepost() {
        gx_leavepost_api* api_temp = new gx_leavepost_api();
        int T                      = 1000;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img("/root/img/leavepost.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_leavepost(img);
                printf("hat_list = %d\n", val.hat_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("leavepost time = %d microsecond\n", duration.count());
        delete api_temp;
    }
} // namespace glasssix


int main(int argc, char** argv) {
    // C接口测试
    /*
    try {
        char data[] = "[{\"key\":\"action_live_0\",\"imgs\":\"D:/test/test/img/"
                      "action_live_0.jpg\"},{\"key\":\"action_live_1\",\"imgs\":\"/root/test/img/"
                      "action_live_1.jpg\"},{\"key\":\"action_live_2\",\"imgs\":\"/root/test/img/"
                      "action_live_2.jpg\"},{\"key\":\"action_live_3\",\"imgs\":\"/root/test/img/"
                      "action_live_3.jpg\"},{\"key\":\"action_live_4\",\"imgs\":\"/root/test/img/action_live_4.jpg\"}]";
        char keys[] = "[\"action_live_0\",\"action_live_1\",\"action_live_2\",\"action_live_3\",\"action_live_4\"]";
        char img[]  = "D:/test/img/action_live_5.jpg";

        printf_demo('c', img);
        gx_user_load();
        printf("asdsa4445454sad"<< "----\n";
        double as = gx_feature_comparison("/root/img/1027/3.png", "/root/img/1027/5.png");
        //char* ss = gx_detect_integration(img, 10, 0.2);
        printf("%.5f\n", as);
    } catch (const std::exception& ex) {
        printf(ex.what() << "----\n";
    }*/

    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        // 安全生产 指标测试
        // safe_test1();
        // safe_test2();
        // safe_test3();

        // 人脸入库
        // test_add_face_all();


        // 多线程测性能测试
        std::thread t[30];
        // t[0]       = std::thread(thread_function_helmet);
        // t[1]       = std::thread(thread_function_flame);
        // t[2]       = std::thread(thread_function_refvest);
        // t[3]       = std::thread(thread_function_search);
        t[4] = std::thread(thread_function_integration);
        // t[5] = std::thread(thread_function_leavepost);
        // t[6] = std::thread(thread_function_sleep);
        // t[7] = std::thread(thread_function_smoke);

        // t[0].join();
        // t[1].join();
        // t[2].join();
        // t[3].join();
        t[4].join();
        // t[5].join();
        //  t[6].join();
        // t[7].join();

        // auto start = std::chrono::high_resolution_clock::now();
        // auto end      = std::chrono::high_resolution_clock::now();
        // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        // printf("refvest*1_helmet*2_flame*2_search_integration time = " << duration.count() << " microsecond" <<
        // std::endl;

        // 用于windows播放视频或图片的
        /*
         display_test::test_detect(api);
         display_test::test_track(api);
         display_test::test_blur(api);
         display_test::test_action_live(api);
         display_test::test_spoofing_live(api);
         display_test::test_feature(api);
         display_test::test_feature_comparison(api);
         display_test::test_user(api);
         display_test::test_detect_integration(api);
         display_test::test_add_folder_all(_Api);
        */

        // 单元测试

        //::testing::InitGoogleTest(&argc, argv);
        // int ans = RUN_ALL_TESTS();
        // printf( "RUN_ALL_TESTS = %d \n",ans);
        //  delete api;

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}
