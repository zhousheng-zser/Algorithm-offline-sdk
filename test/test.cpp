#include <algorithm>
#include <iostream>
#include <optional>

#include <gtest/gtest.h>
#include <gx_face_api.h>

// #include <gx_face_api_c.hpp>
// #include <opencv2/opencv.hpp>
using namespace glasssix::face;
using namespace glasssix;

/*  //用于windows 播放显示
namespace glasssix::display_test {
    void test_detect(gx_face_api* _api) {

        cv::VideoCapture capture;
        capture.open("D:/test/img/20230115-092810.jpg");
        int cnt = 0;
        while (1) {
            cnt++;
            cv::Mat img;
            capture >> img;
            std::vector<uchar> buffer(1024 * 1024);
            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
            abi::vector<face_info> faces;
            faces = _api->detect(img_buff);
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
            cv::waitKey(0);
        }
    }

    void test_track(gx_face_api* _api) {
        cv::VideoCapture capture;
        capture.open("D:/test/video/123456.mp4");
        while (1) {
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            std::vector<uchar> buffer(1024 * 1024);

            cv::imencode(".jpg", img, buffer);
            gx_img_api img_buff(buffer);
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
            faces = _api->face_blur(img_buff);
            for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); i++) {
                face_info info = faces.facerectwithfaceinfo_list[i];
                std::cout << "detect clarity is:" << faces.clarity[i] << std::endl;

                rectangle(img, cv::Point(info.x, info.y), cv::Point(info.x + info.width, info.y + info.height),
                    cv::Scalar(0, 255, 0), 2);
                cv::putText(img, std::to_string(faces.clarity[i]).c_str(), cv::Point(info.x, info.y),
                    cv::FONT_HERSHEY_COMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
            }

            std::cout << U8("-------------------------------------\n");
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
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Blink of an eye\n";
            else
                std::cout << "detected fail Blink of an eye\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Open mouth\n ";
            else
                std::cout << "detected fail Open mouth\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Nutation\n ";
            else
                std::cout << "detected fail Nutation\n";
            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img_buff);
            if (action_result)
                std::cout << "----------------------detected success Left shake head\n ";
            else
                std::cout << "detected fail Left shake head\n";

            info = _api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img_buff);
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
            faces = _api->face_spoofing_live(img_buff);
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

        cv::Mat img = cv::imread("D:/test/img/20221208.jpg");
        gx_img_api img_path("D:/test/img/20221208.jpg");
        abi::vector<faces_feature> faces;
        faces = _api->face_feature(img_path, false);
        for (int i = 0; i < faces[0].facerectwithfaceinfo_list.size(); ++i) {
            face_info info = faces[0].facerectwithfaceinfo_list[i];

            for (int j = 0; j < faces[0].features[i].feature.size(); j++)
                std::cout << " " << faces[0].features[i].feature[j];
            std::cout << "\nsize= " << faces[0].features[i].feature.size() << "------------\n";
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
        double ans = _api->feature_comparison(img_pathA, img_pathB);

        std::cout << "feature_comparison: " << ans << std::endl;

        cv::imshow("video-A", cv::imread("D:/test/img/A/610111200208264510.jpg"));
        cv::imshow("video-B", cv::imread("D:/test/img/B/610111200208264510.jpg"));
        cv::waitKey(20);
        cv::waitKey(0);
    }

    void test_user(gx_face_api* _api) {

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
            faces_integration_search_info faces = _api->detect_integration(img_buff, 5, 0.4f);
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

    void test_add_folder_all(gx_face_api* _api) {
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


namespace glasssix::face {

    gx_face_api* api = new gx_face_api();
    // 人脸检测
    TEST(FaceApi, Detect) {
        gx_img_api img("/root/img/20221209.jpg");
        abi::vector<face_info> faces;
        faces = api->detect(img);

        face_info info = faces[0];

        EXPECT_GT(info.confidence, 0);
        EXPECT_LT(info.confidence, 1);
        EXPECT_GT(info.width, 0);
        EXPECT_GT(info.height, 0);
        EXPECT_EQ(info.landmark.size(), 5);
        EXPECT_TRUE(info.attributes.has_value());
        EXPECT_EQ(info.attributes->glass_index, 0);
        EXPECT_EQ(info.attributes->mask_index, 0);
        EXPECT_GT(info.attributes->yaw, -90.0);
        EXPECT_LT(info.attributes->yaw, 90.0);
        EXPECT_GT(info.attributes->pitch, -90.0);
        EXPECT_LT(info.attributes->pitch, 90.0);
        EXPECT_GT(info.attributes->roll, -90.0);
        EXPECT_LT(info.attributes->roll, 90.0);
    }
    // 人脸追踪
    TEST(FaceApi, Track) {
        gx_img_api img("/root/img/img_align_celeba/000011.jpg");
        abi::vector<face_trace_info> faces;
        faces = api->track(img);

        EXPECT_GT(faces.size(), 0);
        for (int i = 0; i < faces.size(); i++) {
            EXPECT_TRUE(faces[i].trace_success);
            std::optional<face_info> info = faces[i].facerectwithfaceinfo;
            EXPECT_TRUE(info.has_value());
            EXPECT_GT(info->confidence, 0);
            EXPECT_LT(info->confidence, 1);
            EXPECT_GT(info->width, 0);
            EXPECT_GT(info->height, 0);
            EXPECT_EQ(info->landmark.size(), 5);
            EXPECT_EQ(info->attributes->glass_index, 0);
            EXPECT_EQ(info->attributes->mask_index, 0);
            EXPECT_GT(info->attributes->yaw, -90.0);
            EXPECT_LT(info->attributes->yaw, 90.0);
            EXPECT_GT(info->attributes->pitch, -90.0);
            EXPECT_LT(info->attributes->pitch, 90.0);
            EXPECT_GT(info->attributes->roll, -90.0);
            EXPECT_LT(info->attributes->roll, 90.0);
        }
    }

    // 人脸质量检测
    TEST(FaceApi, Face_blur) {
        gx_img_api img("/root/img/20230323.png");
        faces_blur faces;
        faces = api->face_blur(img);
        EXPECT_GT(faces.facerectwithfaceinfo_list.size(), 0);
        nlohmann::json x(faces);
        for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); i++) {
            // face_info info = faces.facerectwithfaceinfo_list[i]; 前面测过了
            EXPECT_GE(faces.clarity[i], 0.0);
            EXPECT_LE(faces.clarity[i], 1.0);
        }
    }

    // 配合活体检测
    TEST(FaceApi, Face_action_live) {
        abi::vector<gx_img_api> img;
        img.emplace_back(gx_img_api("/root/img/action_live_0.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_1.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_2.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_3.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_4.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_5.jpg"));

        face_info info;
        bool action_result = 0;
        info               = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
        EXPECT_TRUE(action_result);
        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
        EXPECT_FALSE(action_result);


        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
        EXPECT_TRUE(action_result);
        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
        EXPECT_FALSE(action_result);


        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
        EXPECT_TRUE(action_result);
        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
        EXPECT_FALSE(action_result);


        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
        EXPECT_TRUE(action_result);
        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
        EXPECT_FALSE(action_result);


        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
        EXPECT_TRUE(action_result);
        info = api->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[5]);
        EXPECT_FALSE(action_result);
    }

    // 静默活体检测
    TEST(FaceApi, Face_spoofing_live) {
        abi::vector<gx_img_api> img;
        img.emplace_back(gx_img_api("/root/img/spoofing_0.jpg"));
        img.emplace_back(gx_img_api("/root/img/action_live_0.jpg"));
        img.emplace_back(gx_img_api("/root/img/spoofing_2.jpg"));
        faces_spoofing faces;
        faces = api->face_spoofing_live(img[0]);
        for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
            EXPECT_GE(faces.spoofing_result[i].prob[0], 0.5);
        }
        faces = api->face_spoofing_live(img[1]);
        for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
            EXPECT_GE(faces.spoofing_result[i].prob[1], 0.5);
        }
        faces = api->face_spoofing_live(img[2]);
        for (int i = 0; i < faces.facerectwithfaceinfo_list.size(); ++i) {
            EXPECT_GE(faces.spoofing_result[i].prob[2], 0.5);
        }
    }

    // 特征值提取
    TEST(FaceApi, Face_feature) {
        gx_img_api img("/root/img/20221209.jpg");
        abi::vector<faces_feature> faces;

        faces = api->face_feature(img, false);
        EXPECT_EQ(faces[0].facerectwithfaceinfo_list.size(), faces[0].features.size());
        for (int i = 0; i < faces[0].facerectwithfaceinfo_list.size(); ++i) {

            EXPECT_EQ(faces[0].features[i].feature.size(), 256);
            for (int j = 0; j < faces[0].features[i].feature.size(); j++) {
                EXPECT_GT(faces[0].features[i].feature[j], -1.0);
                EXPECT_LT(faces[0].features[i].feature[j], 1.0);
            }
        }
    }

    // 1:1 人脸对比
    TEST(FaceApi, gx_feature_comparison) {
        gx_img_api img_pathA("/root/img/action_live_1.jpg");
        gx_img_api img_pathB("/root/img/action_live_5.jpg");

        double ans1 = api->feature_comparison(img_pathA, img_pathB);
        EXPECT_GT(ans1, 0.9);
    }

    // 人脸特征值底库 + 融合人脸识别
    TEST(FaceApi, gx_user_and_detect_integration) {

        abi::vector<gx_img_api> imgs;
        imgs.emplace_back(gx_img_api("/root/img/action_live_0.jpg"));
        imgs.emplace_back(gx_img_api("/root/img/action_live_1.jpg"));
        imgs.emplace_back(gx_img_api("/root/img/action_live_2.jpg"));
        imgs.emplace_back(gx_img_api("/root/img/action_live_3.jpg"));
        imgs.emplace_back(gx_img_api("/root/img/action_live_4.jpg"));
        abi::vector<abi::string> keys;
        keys.emplace_back("action_live_0");
        keys.emplace_back("action_live_1");
        keys.emplace_back("action_live_2");
        keys.emplace_back("action_live_3");
        keys.emplace_back("action_live_4");

        abi::vector<face_user_result> result;
        faces_search_info faces;
        faces_integration_search_info faces_i;
        gx_img_api img("/root/img/action_live_5.jpg");


        api->user_load(); // 人员库加载

        result = api->user_add_records(keys, imgs, false, false); // 人员库批量添加记录
        EXPECT_EQ(result.size(), 5);
        for (int i = 0; i < result.size(); i++)
            EXPECT_EQ(result[i].success, 0);

        faces = api->user_search(img, 5, 0.4f); // 人员库搜索
        ASSERT_LE(faces.result.size(), 5);
        for (int i = 0; i < faces.result.size(); i++) {
            EXPECT_GE(faces.result[i].similarity, 0.4);
        }
        ASSERT_STREQ(faces.result[0].data.key.c_str(), "action_live_0");

        faces_i = api->detect_integration(img, 5, 0.4f); // 融合人脸识别
        ASSERT_LE(faces_i.result.size(), 5);
        for (int i = 0; i < faces_i.result.size(); i++) {
            EXPECT_GE(faces_i.result[i].similarity, 0.4);
        }
        ASSERT_STREQ(faces.result[0].data.key.c_str(), "action_live_0");

        result = api->user_add_records(keys, imgs, false, false); // 已存在再批量添加则更新
        EXPECT_EQ(result.size(), 5);
        for (int i = 0; i < result.size(); i++)
            EXPECT_EQ(result[i].success, 0);


        api->user_remove_records(keys); // 人员库批量删除记录
        faces = api->user_search(img, 5, 0.4f); // 人员库搜索
        ASSERT_LE(faces.result.size(), 0);

        api->user_remove_all(); // 人员库清空  清内存和磁盘
    }

} // namespace glasssix::face


#include <fstream>
int main(int argc, char** argv) {
    /*C接口测试
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
        std::cout << "asdsa4445454sad"<< "----\n";
        double as = gx_feature_comparison("/root/img/1027/3.png", "/root/img/1027/5.png");
        //char* ss = gx_detect_integration(img, 10, 0.2);
        printf("%.5f\n", as);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "----\n";
    }*/

    /* C++ 接口测试*/
    try {

        /*简单测试*/
        //std::ifstream file;
        //file.open("C:/Users/zs/Downloads/100000.txt", std::ios::in);
        //std::vector<glasssix::abi::string> names;
        //glasssix::abi::string name;
        //while (file >> name) {
        //    std::cout << name << "\n";
        //    names.emplace_back(name);
        //}
        //api->user_load();
        //api->user_remove_all();
        //std::ofstream ff;
        //ff.open("./100000.txt", std::ios::app|std::ios::out);
        //for (int i = 0;i< names.size(); ) {
        //    int T = 1000;
        //    glasssix::abi::vector<gx_img_api> imgs;
        //    glasssix::abi::vector<glasssix::abi::string> keys;
        //    while (i < names.size() && T--) {
        //    imgs.push_back(gx_img_api("D:/test/img/nanhu_2/" + names[i]));
        //    keys.push_back(glasssix::abi::string {std::to_string(i)});
        //    i++;
        //    }
        //    auto ans = api->user_add_records(keys, imgs, false, false);
        //    for (int j=0;j<ans.size() ;j++) {
        //        ff << ans[j].key << "|" << names[j] << "|" << ans[j].success << "\n";
        //    }
        //}
       
        /* 用于windows播放视频或图片的*/
        // display_test::test_detect(api);
        // display_test::test_track(api);
        // display_test::test_blur(api);
        // display_test::test_action_live(api);
        // display_test::test_spoofing_live(api);
        // display_test::test_feature(api);
        // display_test::test_feature_comparison(api);
        // display_test::test_user(api);
        // display_test::test_detect_integration(api);
        // display_test::test_add_folder_all(_Api);

        /* 单元测试 */
        testing::InitGoogleTest(&argc, argv);
        int ans = RUN_ALL_TESTS();
        std::cout << "RUN_ALL_TESTS = " << ans << "\n";
        delete api;
    } catch (const std::exception& ex) {
        std::cout << ex.what() << "----\n";
    }
    return 0;
}
