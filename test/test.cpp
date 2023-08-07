#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <thread>

#include <gx_api.hpp>
#include <gx_face_api.hpp>
#include <gx_flame_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_leavepost_api.hpp>
#include <gx_onphone_api.hpp>
#include <gx_pedestrian_api.hpp>
#include <gx_pedestrian_labor_api.hpp>
#include <gx_playphone_api.hpp>
#include <gx_refvest_api.hpp>
#include <gx_sleep_api.hpp>
#include <gx_smoke_api.hpp>
#include <gx_workcloth_api.hpp>
// #include <gx_api_c.hpp>
#include <g6/json_extensions.hpp>

#include <opencv2/opencv.hpp>
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
    // 安全生产指标测试 烟火
    void safe_test1() {
        gx_flame_api* api_temp = new gx_flame_api();
        std::ofstream safe_file("./flame.log", std::ios::out | std::ios::trunc);
        // std::filesystem::path folder_path          = "/root/img/production/fire";
        std::filesystem::path folder_path = "/root/img/production/no_flame";
        std::vector<abi::string> img_list = find_file(folder_path);
        for (int i = 0; i < img_list.size(); ++i) {
            safe_file << img_list[i] << "#####\n";
            try {
                const gx_img_api img(img_list[i], 1 << 30);
                auto val = api_temp->safe_production_flame(img);
                safe_file << "fire_list = " << val.fire_list.size() << "\n";
                for (int j = 0; j < val.fire_list.size(); j++)
                    safe_file << "score = " << val.fire_list[j].score << " x1 = " << val.fire_list[j].x1
                              << " y1 = " << val.fire_list[j].y1 << " x2 = " << val.fire_list[j].x2
                              << " y2 = " << val.fire_list[j].y2 << "\n";
                safe_file << "smoke_list = " << val.smoke_list.size() << "\n";
                for (int j = 0; j < val.smoke_list.size(); j++)
                    safe_file << "score = " << val.smoke_list[j].score << " x1 = " << val.smoke_list[j].x1
                              << " y1 = " << val.smoke_list[j].y1 << " x2 = " << val.smoke_list[j].x2
                              << " y2 = " << val.smoke_list[j].y2 << "\n";
            } catch (const std::exception& ex) {
                safe_file << ex.what();
            }
            safe_file << "\n";
        }
    }
    // 安全生产指标测试 反光衣
    void safe_test2() {
        gx_refvest_api* api_temp = new gx_refvest_api();
        std::ofstream safe_file("./refvest.log", std::ios::out | std::ios::trunc);
        std::filesystem::path folder_path = "/root/img/production/ref_benchmark";
        std::vector<abi::string> img_list = find_file(folder_path);
        for (int i = 0; i < img_list.size(); ++i) {
            safe_file << img_list[i] << "#####\n";
            try {
                const gx_img_api img(img_list[i], 1 << 30);
                auto val = api_temp->safe_production_refvest(img);
                safe_file << "without_refvest_list = " << val.without_refvest_list.size() << "\n";
                for (int j = 0; j < val.without_refvest_list.size(); j++)
                    safe_file << "score = " << val.without_refvest_list[j].score
                              << " x1 = " << val.without_refvest_list[j].x1
                              << " y1 = " << val.without_refvest_list[j].y1
                              << " x2 = " << val.without_refvest_list[j].x2
                              << " y2 = " << val.without_refvest_list[j].y2 << "\n";
                safe_file << "with_refvest_list = " << val.with_refvest_list.size() << "\n";
                for (int j = 0; j < val.with_refvest_list.size(); j++)
                    safe_file << "score = " << val.with_refvest_list[j].score << " x1 = " << val.with_refvest_list[j].x1
                              << " y1 = " << val.with_refvest_list[j].y1 << " x2 = " << val.with_refvest_list[j].x2
                              << " y2 = " << val.with_refvest_list[j].y2 << "\n";
            } catch (const std::exception& ex) {
                safe_file << ex.what();
            }
            safe_file << "\n";
        }
    }
    // 安全生产指标测试 安全帽
    void safe_test3() {
        gx_helmet_api* api_temp = new gx_helmet_api();
        std::ofstream safe_file("./helmet.log", std::ios::out | std::ios::trunc);
        std::filesystem::path folder_path = "/root/img/production/val2017";
        std::vector<abi::string> img_list = find_file(folder_path);
        for (int i = 0; i < img_list.size(); ++i) {
            safe_file << img_list[i] << "#####\n";
            try {
                const gx_img_api img(img_list[i], 1 << 30);
                auto val = api_temp->safe_production_helmet(img);
                safe_file << "with_helmet_list = " << val.with_helmet_list.size() << "\n";
                for (int j = 0; j < val.with_helmet_list.size(); j++)
                    safe_file << "score = " << val.with_helmet_list[j].score << " x1 = " << val.with_helmet_list[j].x1
                              << " y1 = " << val.with_helmet_list[j].y1 << " x2 = " << val.with_helmet_list[j].x2
                              << " y2 = " << val.with_helmet_list[j].y2 << "\n";
                safe_file << "with_helmet_list = " << val.with_helmet_list.size() << "\n";
                for (int j = 0; j < val.with_helmet_list.size(); j++)
                    safe_file << "score = " << val.with_helmet_list[j].score << " x1 = " << val.with_helmet_list[j].x1
                              << " y1 = " << val.with_helmet_list[j].y1 << " x2 = " << val.with_helmet_list[j].x2
                              << " y2 = " << val.with_helmet_list[j].y2 << "\n";
            } catch (const std::exception& ex) {
                safe_file << ex.what();
            }
            safe_file << "\n";
        }
    }
    // 安全生产指标测试 睡岗
    void safe_test4() {
        gx_sleep_api* api_temp = new gx_sleep_api();
        std::ofstream safe_file("./sleep.log", std::ios::out | std::ios::trunc);
        std::filesystem::path folder_path = "/root/img/production/sleep";
        std::vector<abi::string> img_list = find_file(folder_path);
        for (int i = 0; i < img_list.size(); ++i) {
            safe_file << img_list[i] << "#####\n";
            try {
                const gx_img_api img(img_list[i], 1 << 30);
                auto val = api_temp->safe_production_sleep(img);
                safe_file << "desk_list = " << val.desk_list.size() << "\n";
                for (int j = 0; j < val.desk_list.size(); j++)
                    safe_file << "score = " << val.desk_list[j].score << " x1 = " << val.desk_list[j].x1
                              << " y1 = " << val.desk_list[j].y1 << " x2 = " << val.desk_list[j].x2
                              << " y2 = " << val.desk_list[j].y2 << "\n";
                safe_file << "lying_list = " << val.lying_list.size() << "\n";
                for (int j = 0; j < val.lying_list.size(); j++)
                    safe_file << "score = " << val.lying_list[j].score << " x1 = " << val.lying_list[j].x1
                              << " y1 = " << val.lying_list[j].y1 << " x2 = " << val.lying_list[j].x2
                              << " y2 = " << val.lying_list[j].y2 << "\n";
                safe_file << "standing_list = " << val.standing_list.size() << "\n";
                for (int j = 0; j < val.standing_list.size(); j++)
                    safe_file << "score = " << val.standing_list[j].score << " x1 = " << val.standing_list[j].x1
                              << " y1 = " << val.standing_list[j].y1 << " x2 = " << val.standing_list[j].x2
                              << " y2 = " << val.standing_list[j].y2 << "\n";
                safe_file << "work_list = " << val.work_list.size() << "\n";
                for (int j = 0; j < val.work_list.size(); j++)
                    safe_file << "score = " << val.work_list[j].score << " x1 = " << val.work_list[j].x1
                              << " y1 = " << val.work_list[j].y1 << " x2 = " << val.work_list[j].x2
                              << " y2 = " << val.work_list[j].y2 << "\n";
            } catch (const std::exception& ex) {
                safe_file << ex.what();
            }
            safe_file << "\n";
        }
    }
    // 安全生产指标测试 离岗
    void safe_test5() {
        gx_leavepost_api* api_temp = new gx_leavepost_api();
        std::ofstream safe_file("./leavepost.log", std::ios::out | std::ios::trunc);
        std::filesystem::path folder_path = "/root/img/production/leavepost";
        std::vector<abi::string> img_list = find_file(folder_path);
        for (int i = 0; i < img_list.size(); ++i) {
            safe_file << img_list[i] << "#####\n";
            try {
                const gx_img_api img(img_list[i], 1 << 30);
                auto val = api_temp->safe_production_leavepost(img);

                safe_file << "hat_list = " << val.hat_list.size() << "\n";
                for (int j = 0; j < val.hat_list.size(); j++)
                    safe_file << "score = " << val.hat_list[j].score << " x1 = " << val.hat_list[j].x1
                              << " y1 = " << val.hat_list[j].y1 << " x2 = " << val.hat_list[j].x2
                              << " y2 = " << val.hat_list[j].y2 << "\n";
            } catch (const std::exception& ex) {
                safe_file << ex.what();
            }
            safe_file << "\n";
        }
    }

    // 多线程测安全帽
    void thread_function_helmet() {
        gx_helmet_api* api_temp = new gx_helmet_api();
        int T                   = 1000;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/helmet.jpg", static_cast<int>(1e9));
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
                const gx_img_api img("/root/img/flame.jpg", static_cast<int>(1e9));
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
                const gx_img_api img("/root/img/refvest.jpg", static_cast<int>(1e9));
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
                const gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->user_search(img, 1, 0.5);
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
                // gx_img_api img("/root/img/bbb.jpg", static_cast<int>(1e9));
                const gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);

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
                const gx_img_api img("/root/img/sleep.jpg", static_cast<int>(1e9));
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
                const gx_img_api img("/root/img/smoke.jpg", static_cast<int>(1e9));
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
                const gx_img_api img("/root/img/leavepost.jpg", static_cast<int>(1e9));
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
    // 多线程测玩手机
    void thread_function_playphone() {
        gx_playphone_api* api_temp = new gx_playphone_api();
        int T                      = 1000;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/playphone.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_playphone(img);
                printf("phone_list = %d no_phone_list= %d\n", val.phone_list.size(), val.no_phone_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("playphone time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测打电话
    void thread_function_onphone() {
        gx_onphone_api* api_temp = new gx_onphone_api();
        int T                    = 1000;
        auto start               = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/onphone.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_onphone(img);
                printf("norm_list = %d onphone_list = %d\n", val.norm_list.size(), val.onphone_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("onphone time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测工服检测
    void thread_function_workcloth() {
        gx_workcloth_api* api_temp = new gx_workcloth_api();
        int T                      = 1000;
        auto start                 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/workcloth.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_workcloth(img);
                printf("workcloth_list = %d\n", val.cloth_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("workcloth time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测劳保检测
    void thread_function_pedestrian_labor() {
        gx_pedestrian_labor_api* api_temp = new gx_pedestrian_labor_api();
        int T                             = 1000;
        auto start                        = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/pedestrian_labor.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian_labor(img);
                printf("pedestrian_labor_list = %d\n", val.pedestrian_labor_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("pedestrian_labor time = %d microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测行人检测
    void thread_function_pedestrian() {
        gx_pedestrian_api* api_temp = new gx_pedestrian_api();
        int T                       = 1000;
        auto start                  = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/pedestrian.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_pedestrian(img);
                printf("person_list = %d\n", val.person_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("pedestrian time = %d microsecond\n", duration.count());
        delete api_temp;
    }

} // namespace glasssix

// 处理视频的
namespace glasssix {
    const cv::Scalar RED   = CV_RGB(250, 0, 0); // 红
    const cv::Scalar GREEN = CV_RGB(0, 250, 0); // 绿
    const cv::Scalar WHITE = CV_RGB(255, 255, 255); // 白

    void flame_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_flame_api* api_temp = new gx_flame_api();
        int cnt                = 0;
        int sum                = capture.get(7);
        while (1) {
            printf("flame %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_flame(img_buff);

            for (int j = 0; j < val.fire_list.size(); j++) {
                int x1      = val.fire_list[j].x1;
                int x2      = val.fire_list[j].x2;
                int y1      = val.fire_list[j].y1;
                int y2      = val.fire_list[j].y2;
                float score = val.fire_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "fire:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.smoke_list.size(); j++) {
                int x1      = val.smoke_list[j].x1;
                int x2      = val.smoke_list[j].x2;
                int y1      = val.smoke_list[j].y1;
                int y2      = val.smoke_list[j].y2;
                float score = val.smoke_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "smoke:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void helmet_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_helmet_api* api_temp = new gx_helmet_api();
        int cnt                 = 0;
        int sum                 = capture.get(7);
        while (1) {
            printf("helmet %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_helmet(img_buff);

            for (int j = 0; j < val.with_helmet_list.size(); j++) {
                int x1      = val.with_helmet_list[j].x1;
                int x2      = val.with_helmet_list[j].x2;
                int y1      = val.with_helmet_list[j].y1;
                int y2      = val.with_helmet_list[j].y2;
                float score = val.with_helmet_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "with_helmet:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.without_helmet_list.size(); j++) {
                int x1      = val.without_helmet_list[j].x1;
                int x2      = val.without_helmet_list[j].x2;
                int y1      = val.without_helmet_list[j].y1;
                int y2      = val.without_helmet_list[j].y2;
                float score = val.without_helmet_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "without_helmet:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void refvest_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_refvest_api* api_temp = new gx_refvest_api();
        int cnt                  = 0;
        int sum                  = capture.get(7);
        while (1) {
            printf("refvest %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_refvest(img_buff);

            for (int j = 0; j < val.with_refvest_list.size(); j++) {
                int x1      = val.with_refvest_list[j].x1;
                int x2      = val.with_refvest_list[j].x2;
                int y1      = val.with_refvest_list[j].y1;
                int y2      = val.with_refvest_list[j].y2;
                float score = val.with_refvest_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "with_refvest:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.without_refvest_list.size(); j++) {
                int x1      = val.without_refvest_list[j].x1;
                int x2      = val.without_refvest_list[j].x2;
                int y1      = val.without_refvest_list[j].y1;
                int y2      = val.without_refvest_list[j].y2;
                float score = val.without_refvest_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "without_refvest:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void sleep_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_sleep_api* api_temp = new gx_sleep_api();
        int cnt                = 0;
        int sum                = capture.get(7);
        while (1) {
            printf("sleep %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_sleep(img_buff);

            for (int j = 0; j < val.desk_list.size(); j++) {
                int x1      = val.desk_list[j].x1;
                int x2      = val.desk_list[j].x2;
                int y1      = val.desk_list[j].y1;
                int y2      = val.desk_list[j].y2;
                float score = val.desk_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "desk:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.lying_list.size(); j++) {
                int x1      = val.lying_list[j].x1;
                int x2      = val.lying_list[j].x2;
                int y1      = val.lying_list[j].y1;
                int y2      = val.lying_list[j].y2;
                float score = val.lying_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "lying:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.standing_list.size(); j++) {
                int x1      = val.standing_list[j].x1;
                int x2      = val.standing_list[j].x2;
                int y1      = val.standing_list[j].y1;
                int y2      = val.standing_list[j].y2;
                float score = val.standing_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "standing:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.work_list.size(); j++) {
                int x1      = val.work_list[j].x1;
                int x2      = val.work_list[j].x2;
                int y1      = val.work_list[j].y1;
                int y2      = val.work_list[j].y2;
                float score = val.work_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "work:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void leavepost_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_leavepost_api* api_temp = new gx_leavepost_api();
        int cnt                    = 0;
        int sum                    = capture.get(7);
        while (1) {
            printf("leavepost %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_leavepost(img_buff);

            for (int j = 0; j < val.hat_list.size(); j++) {
                int x1      = val.hat_list[j].x1;
                int x2      = val.hat_list[j].x2;
                int y1      = val.hat_list[j].y1;
                int y2      = val.hat_list[j].y2;
                float score = val.hat_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "hat:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void smoke_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_smoke_api* api_temp = new gx_smoke_api();
        int cnt                = 0;
        int sum                = capture.get(7);
        while (1) {
            printf("smoke %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_smoke(img_buff);

            for (int j = 0; j < val.smoke_list.size(); j++) {
                int x1      = val.smoke_list[j].x1;
                int x2      = val.smoke_list[j].x2;
                int y1      = val.smoke_list[j].y1;
                int y2      = val.smoke_list[j].y2;
                float score = val.smoke_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "smoke:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.norm_list.size(); j++) {
                int x1      = val.norm_list[j].x1;
                int x2      = val.norm_list[j].x2;
                int y1      = val.norm_list[j].y1;
                int y2      = val.norm_list[j].y2;
                float score = val.norm_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "norm:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void workcloth_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_workcloth_api* api_temp = new gx_workcloth_api();
        int cnt                    = 0;
        int sum                    = capture.get(7);
        while (1) {
            printf("workcloth %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_workcloth(img_buff);

            for (int j = 0; j < val.cloth_list.size(); j++) {
                int x1      = val.cloth_list[j].x1;
                int x2      = val.cloth_list[j].x2;
                int y1      = val.cloth_list[j].y1;
                int y2      = val.cloth_list[j].y2;
                float score = val.cloth_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text =
                    "cloth:" + std::to_string(score) + "up_rgb:" + std::to_string(val.cloth_list[j].up_rgb.r) + ","
                    + std::to_string(val.cloth_list[j].up_rgb.g) + "," + std::to_string(val.cloth_list[j].up_rgb.b)
                    + " lw_rgb:" + std::to_string(val.cloth_list[j].lw_rgb.r) + ","
                    + std::to_string(val.cloth_list[j].lw_rgb.g) + "," + std::to_string(val.cloth_list[j].lw_rgb.b);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void playphone_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_playphone_api* api_temp = new gx_playphone_api();
        int cnt                    = 0;
        int sum                    = capture.get(7);
        while (1) {
            printf("playphone %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_playphone(img_buff);

            for (int j = 0; j < val.phone_list.size(); j++) {
                int x1      = val.phone_list[j].x1;
                int x2      = val.phone_list[j].x2;
                int y1      = val.phone_list[j].y1;
                int y2      = val.phone_list[j].y2;
                float score = val.phone_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "phone:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.no_phone_list.size(); j++) {
                int x1      = val.no_phone_list[j].x1;
                int x2      = val.no_phone_list[j].x2;
                int y1      = val.no_phone_list[j].y1;
                int y2      = val.no_phone_list[j].y2;
                float score = val.no_phone_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "nophone:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void onphone_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_onphone_api* api_temp = new gx_onphone_api();
        int cnt                  = 0;
        int sum                  = capture.get(7);
        while (1) {
            printf("onphone %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_onphone(img_buff);

            for (int j = 0; j < val.onphone_list.size(); j++) {
                int x1      = val.onphone_list[j].x1;
                int x2      = val.onphone_list[j].x2;
                int y1      = val.onphone_list[j].y1;
                int y2      = val.onphone_list[j].y2;
                float score = val.onphone_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                std::string text  = "onphone:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            for (int j = 0; j < val.norm_list.size(); j++) {
                int x1      = val.norm_list[j].x1;
                int x2      = val.norm_list[j].x2;
                int y1      = val.norm_list[j].y1;
                int y2      = val.norm_list[j].y2;
                float score = val.norm_list[j].score;
                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "norm:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void pedestrian_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        capture.open(name);

        cv::Size size        = cv::Size(capture.get(cv::CAP_PROP_FRAME_WIDTH), capture.get(cv::CAP_PROP_FRAME_HEIGHT));
        int fps              = capture.get(cv::CAP_PROP_FPS);
        std::string new_name = name;
        int len              = name.length();
        new_name[len - 4]    = '_';
        new_name += add;
        cv::VideoWriter writer(new_name, cv::VideoWriter::fourcc('M', 'P', '4', '2'), fps, size, true);

        gx_pedestrian_api* api_temp = new gx_pedestrian_api();
        int cnt                     = 0;
        int sum                     = capture.get(7);
        while (1) {
            printf("pedestrian %d / %d \n", cnt++, sum);
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(IMG_Full_Aperture_4K);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer, IMG_Full_Aperture_4K);
            auto val = api_temp->safe_production_pedestrian(img_buff);

            for (int j = 0; j < val.person_list.size(); j++) {
                int x1      = val.person_list[j].x1;
                int x2      = val.person_list[j].x2;
                int y1      = val.person_list[j].y1;
                int y2      = val.person_list[j].y2;
                float score = val.person_list[j].score;

                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = "person:" + std::to_string(score);
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }

            writer.write(img);
        }
        capture.release();
        writer.release();
    }

    void video_wait(std::thread tt[], int& cnt) {
        for (int i = 0; i < cnt; i++)
            tt[i].join();
        cnt = 0;
        printf(" OK ------------------\n ");
    }
    void todo_video() {
        std::thread tt[30];
        int cnt   = 0;
        tt[cnt++] = std::thread(helmet_video, "/root/img/video/xiangmu/test_yeyazhan.mp4", "_helmet.avi");
        // tt[cnt++] = std::thread(helmet_video, "/root/img/video/xiangmu/yeyazhan.mp4", "_helmet.avi");
        // tt[cnt++] = std::thread(workcloth_video, "/root/img/video/xiangmu/yeyazhan.mp4", "_workcloth.avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/xiangmu/yeyazhan.mp4", "_smoke.avi");
        // video_wait(tt, cnt);
        // tt[cnt++] = std::thread(helmet_video, "/root/img/video/xiangmu/zhenshai.mp4", "_helmet.avi");
        // tt[cnt++] = std::thread(workcloth_video, "/root/img/video/xiangmu/zhenshai.mp4", "_workcloth.avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/xiangmu/zhenshai.mp4", "_smoke.avi");
        // video_wait(tt, cnt);
        // tt[cnt++] = std::thread(sleep_video, "/root/img/video/sleep/sleep_1.mp4", ".avi");
        // tt[cnt++] = std::thread(sleep_video, "/root/img/video/sleep/sleep_2.mp4", ".avi");
        // tt[cnt++] = std::thread(sleep_video, "/root/img/video/sleep/sleep_3.mp4", ".avi");
        // video_wait(tt, cnt);
        // tt[cnt++] = std::thread(playphone_video, "/root/img/video/playphone/playphone_1.mp4", ".avi");
        // tt[cnt++] = std::thread(playphone_video, "/root/img/video/playphone/playphone_2.mp4", ".avi");
        // tt[cnt++] = std::thread(playphone_video, "/root/img/video/playphone/playphone_3.mp4", ".avi");
        // video_wait(tt, cnt);
        // tt[cnt++] = std::thread(leavepost_video, "/root/img/video/leavepost/leavepost_1.mp4", ".avi");
        // tt[cnt++] = std::thread(leavepost_video, "/root/img/video/leavepost/leavepost_2.mp4", ".avi");
        // tt[cnt++] = std::thread(leavepost_video, "/root/img/video/leavepost/leavepost_3.mp4", ".avi");
        // video_wait(tt, cnt);
        // tt[cnt++] = std::thread(pedestrian_video, "/root/img/video/pedestrian/pedestrian_1.mp4", ".avi");
        // tt[cnt++] = std::thread(pedestrian_video, "/root/img/video/pedestrian/pedestrian_2.mp4", ".avi");
        // tt[cnt++] = std::thread(onphone_video, "/root/img/video/onphone/onphone_1.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_1.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_2.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_fu_1.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_fu_2.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_fu_3.mp4", ".avi");
        // tt[cnt++] = std::thread(smoke_video, "/root/img/video/smoke/smoke_fu_4.mp4", ".avi");
        video_wait(tt, cnt);
    }

} // namespace glasssix


int main(int argc, char** argv) {
    /* C++ 接口测试*/
    try {
        printf("hello world\n");
        // 安全生产 指标测试
        // safe_test1();
        // safe_test2();
        // safe_test3();
        // safe_test4();
        // safe_test5();

        // 人脸入库
        // test_add_face_all();

        // todo_video();

        // 多线程测性能测试
        std::thread t[30];
        //t[0]  = std::thread(thread_function_helmet);
        //t[1]  = std::thread(thread_function_flame);
        //t[2]  = std::thread(thread_function_refvest);
        //t[3]  = std::thread(thread_function_search);
        //t[4]  = std::thread(thread_function_integration);
        //t[5]  = std::thread(thread_function_leavepost);
        //t[6]  = std::thread(thread_function_sleep);
        //t[7]  = std::thread(thread_function_smoke);
        //t[8]  = std::thread(thread_function_playphone);
        //t[9]  = std::thread(thread_function_onphone);
        //t[10] = std::thread(thread_function_workcloth);
        //t[11] = std::thread(thread_function_pedestrian_labor);////////////////////
        //t[12] = std::thread(thread_function_pedestrian);
        //t[0].join();
        //t[1].join();
        //t[2].join();
        //t[3].join();
        //t[4].join();
        //t[5].join();
        //t[6].join();
        //t[7].join();
        //t[8].join();
        //t[9].join();
        //t[10].join();
        //t[11].join();
        //t[12].join();
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

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}
