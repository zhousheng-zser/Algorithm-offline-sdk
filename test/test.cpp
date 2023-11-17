#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <thread>

#include <g6/json_extensions.hpp>

#include <gx_api.hpp>
#include <gx_climb_api.hpp>
#include <gx_crowd_api.hpp>
#include <gx_face_api.hpp>
#include <gx_fighting_api.hpp>
#include <gx_flame_api.hpp>
#include <gx_helmet_api.hpp>
#include <gx_leavepost_api.hpp>
#include <gx_onphone_api.hpp>
#include <gx_pedestrian_api.hpp>
#include <gx_playphone_api.hpp>
#include <gx_refvest_api.hpp>
#include <gx_sleep_api.hpp>
#include <gx_smog_api.hpp>
#include <gx_smoke_api.hpp>
#include <gx_tumble_api.hpp>
#include <gx_wander_api.hpp>
#include <gx_workcloth_api.hpp>
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
                    safe_file << " x1 = " << val.with_helmet_list[j].x1 << " y1 = " << val.with_helmet_list[j].y1
                              << " x2 = " << val.with_helmet_list[j].x2 << " y2 = " << val.with_helmet_list[j].y2
                              << "\n";
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

    // 人脸入库
    void test_add_face_all() {
        gx_face_api* _api = new gx_face_api();
        _api->user_load();
        //_api->user_remove_all();
        printf(" const = %d \n", _api->user_record_count());
        auto start = std::chrono::high_resolution_clock::now();
        std::ifstream path_file("/root/cc_test_origin/1.txt", std::ios::in);
        std::ofstream log_file("/root/face_group.log", std::ios::out | std::ios::trunc);
        abi::string path, key;
        while (1) {
            abi::vector<abi::string> keys;
            abi::vector<gx_img_api> mat;
            int T = 1000;
            while ((path_file >> path >> key) && (T--)) {
                try {
                    mat.emplace_back(gx_img_api{"/root/cc_test_origin/" + path, static_cast<int>(1e9)});
                    keys.emplace_back(key);
                } catch (const std::exception& ex) {
                    printf("error = %s\n", ex.what());
                }
            }
            if (mat.size() == 0) {
                break;
            } else {
                auto val = _api->user_add_records(keys, mat, false, false);
                // abi::vector<face_user_result>
                for (auto& x : val) {
                    log_file << x.key << " " << (x.success == 0 ? "OK\n" : "FAIL\n");
                }
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        log_file << "time = " << duration.count() << " microsecond\n";
    }
    // 人脸1:1
    void test_face_compare() {
        gx_face_api* _api = new gx_face_api();
        auto start        = std::chrono::high_resolution_clock::now();
        std::fstream path_file("/root/cc_test_origin/3.txt", std::ios::in);
        std::ofstream log_file("/root/face_compare.log", std::ios::out | std::ios::trunc);
        abi::string path1, path2;
        while (path_file >> path1 >> path2) {
            log_file << path1 << "  " << path2 << " ";

            gx_img_api img1("/root/cc_test_origin/" + path1, 1e9);
            gx_img_api img2("/root/cc_test_origin/" + path2, 1e9);
            log_file << _api->feature_comparison(img1, img2) << "\n";
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        log_file << "time = " << duration.count() << " microsecond\n";
    }
    // 人脸活体
    void test_face_liveness() {
        gx_face_api* _api = new gx_face_api();
        auto start        = std::chrono::high_resolution_clock::now();
        std::fstream path_file("/root/cc_test_origin/2.txt", std::ios::in);
        std::ofstream log_file("/root/liveness_true.log", std::ios::out | std::ios::trunc);
        abi::string path, key;
        while (path_file >> path >> key) {
            log_file << "/root/cc_test_origin/" << path << "  ";
            gx_img_api img("/root/cc_test_origin/" + path, IMG_2K);
            auto val = _api->face_spoofing_live(img);
            log_file << (val.spoofing_result.size() > 0 ? val.spoofing_result[0].prob[1] : 0.0) << "\n";
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        log_file << "time = " << duration.count() << " microsecond\n";
        delete _api;
    }
    // 人脸搜索
    void test_face_search() {
        gx_face_api* _api = new gx_face_api();
        auto start        = std::chrono::high_resolution_clock::now();
        std::ofstream log_file("/root/face_search.log", std::ios::out | std::ios::trunc);
        std::fstream path_file("/root/cc_test_origin/2.txt", std::ios::in);
        abi::string path, key;
        int cnt(0), sum(0);
        _api->user_load();
        while (path_file >> path >> key) {
            log_file << "/root/cc_test_origin/" << path << "  ";
            gx_img_api img("/root/cc_test_origin/" + path, IMG_2K);
            if (_api->user_contains_key(key)) {
                auto val = _api->user_search(img, 1, 0.1);
                if (val.result.size()) {
                    log_file << val.result[0].data.key << " " << val.result[0].similarity << "\n";
                    cnt += (val.result[0].data.key == key ? 1 : 0);
                } else
                    log_file << "Search Fail\n";
                sum++;
            } else
                log_file << "Search Fail\n";
        }

        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        log_file << "time = " << duration.count() << " microsecond\n";
        log_file << "cnt = " << cnt << " sum = " << sum << "\n";
        delete _api;
    }

} // namespace glasssix


// 调试代码
namespace glasssix {
    // 多线程测安全帽
    void thread_function_helmet() {
        gx_helmet_api* api_temp = new gx_helmet_api();
        int T                   = 1000;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/helmet.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_helmet(img);
                printf("with_helmet_list = %d with_hat_list = %d head_list = %d\n", val.with_helmet_list.size(),
                    val.with_hat_list.size(), val.head_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("helmet time = %lld microsecond\n", duration.count());
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
                printf("fire_list = %d\n", val.fire_list.size());

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测烟雾
    void thread_function_smog() {
        gx_smog_api* api_temp = new gx_smog_api();
        int T                 = 1000;
        auto start            = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/smog.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_smog(img);
                printf("smog_list = %d\n", val.smog_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("smog time = %lld microsecond\n", duration.count());
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
        printf("refvest time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测搜索
    void thread_function_search() {
        gx_face_api* api_temp = new gx_face_api();
        api_temp->user_load();
        int T      = 500;
        auto start = std::chrono::high_resolution_clock::now();
        const gx_img_api img("/root/img/action_live_0.jpg", static_cast<int>(1e9));
        api_temp->user_add_records(abi::vector<abi::string>{"123"}, abi::vector<gx_img_api>{img}, false, false);
        while (T--) {
            try {
                auto val =
                    api_temp->user_search(gx_img_api{"/root/img/action_live_5.jpg", static_cast<int>(1e9)}, 1, 0.5);
                printf("similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("search time = %lld microsecond\n", duration.count());
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
                const gx_img_api img("/root/img/action_live_5.jpg", static_cast<int>(1e9));
                auto val = api_temp->detect_integration(img, 1, 0.5);
                printf("prob = %.3f\n", val.prob);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("integration time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测 配合活体 与 质量检测
    void thread_function_Action_live_Blur() {
        gx_face_api* api_temp = new gx_face_api();
        auto start            = std::chrono::high_resolution_clock::now();

        abi::vector<gx_img_api> img;
        img.emplace_back(gx_img_api("/root/img/action_live_0.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_1.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_2.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_3.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_4.jpg", IMG_2K));
        img.emplace_back(gx_img_api("/root/img/action_live_5.jpg", IMG_2K));
        face_info info;
        bool action_result = 0;
        int T              = 100;
        while (T--) {
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
            printf("BDFACE_ACTION_LIVE_BLINK %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
            printf("BDFACE_ACTION_LIVE_OPEN_MOUTH %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
            printf("BDFACE_ACTION_LIVE_NOD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
            printf("BDFACE_ACTION_LIVE_LEFT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
            printf("BDFACE_ACTION_LIVE_RIGHT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
            auto val = api_temp->face_blur(img[5]);
            printf("blur ====== %.2f\n", val.clarity[0]);
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
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
        printf("sleep time = %lld microsecond\n", duration.count());
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
        printf("smoke time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测跌倒
    void thread_function_tumble() {
        gx_tumble_api* api_temp = new gx_tumble_api();
        int T                   = 1000;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/tumble.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_tumble(img);
                printf("stand_list = %d tumble_list = %d\n", val.stand_list.size(), val.tumble_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("tumble time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测徘徊
    void thread_function_wander() {
        gx_wander_api* api_temp = new gx_wander_api();
        int T                   = 20;
        auto start              = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/wander.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_wander(img, i, 1);
                printf("wander_list = %d device =%d\n", val.person_info.size(), 1);
                printf("wander_remove_id ans =%d\n", api_temp->wander_remove_id(val.person_info[0].id));
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        printf("%d\n", api_temp->wander_remove_library());
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("wander time = %lld microsecond\n", duration.count());
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
        printf("leavepost time = %lld microsecond\n", duration.count());
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
        printf("playphone time = %lld microsecond\n", duration.count());
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
        printf("onphone time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测工服检测
    void thread_function_workcloth() {
        gx_workcloth_api* api_temp = new gx_workcloth_api();
        int T                      = 500;
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
        printf("workcloth time = %lld microsecond\n", duration.count());
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
        printf("pedestrian time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测攀爬
    void thread_function_climb() {
        gx_climb_api* api_temp = new gx_climb_api();
        int T                  = 1000;
        auto start             = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                const gx_img_api img("/root/img/climb.jpg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_climb(
                    img, abi::vector<climb_point>{
                             climb_point{20, 30}, climb_point{1000, 20}, climb_point{1000, 710}, climb_point{50, 750}});
                printf("normal_list = %d climb_list = %d\n", val.normal_list.size(), val.climb_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("climb time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
    // 多线程测聚众
    void thread_function_crowd() {
        gx_crowd_api* api_temp = new gx_crowd_api();
        int T                  = 100;
        for (int i = 0; i < T; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            try {
                const gx_img_api img("/root/img/count6.jpg", static_cast<int>(1e9));
                // const gx_img_api img("/root/img/crowd.png", static_cast<int>(1e9));
                auto val = api_temp->safe_production_crowd(img);
                printf("head_list = %d\n", val.head_list.size());
            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            printf("crowd time = %lld microsecond\n", duration.count());
        }
        delete api_temp;
    }
    // 多线程测打架
    void thread_function_fighting() {
        gx_fighting_api* api_temp = new gx_fighting_api();
        printf("-------\n");
        int T      = 1000;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < T; ++i) {
            try {
                gx_img_api img0("/root/img/0.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img0);
                gx_img_api img1("/root/img/1.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img1);
                gx_img_api img2("/root/img/2.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img2);
                gx_img_api img3("/root/img/3.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img3);
                gx_img_api img4("/root/img/4.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img4);
                gx_img_api img5("/root/img/5.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img5);
                gx_img_api img6("/root/img/6.jpeg", static_cast<int>(1e9));
                api_temp->safe_production_fighting(img6);
                gx_img_api img7("/root/img/7.jpeg", static_cast<int>(1e9));
                auto val = api_temp->safe_production_fighting(img7);
                printf("score =%f category=%d\n", val.score, val.category);

            } catch (const std::exception& ex) {
                printf("error =  %s\n", ex.what());
            }
        }
        auto end      = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        printf("flame time = %lld microsecond\n", duration.count());
        delete api_temp;
    }
} // namespace glasssix

// 处理视频的
namespace glasssix {

    std::unordered_map<int, helmet_info::boxes> track_history;
    std::unordered_map<int, std::string> track_history_id;
    inline int ComputeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int x = std::max(0, std::min(ax2, bx2) - std::max(ax1, bx1));
        int y = std::max(0, std::min(ay2, by2) - std::max(ay1, by1));
        return x * y;
    }
    std::string track_check(helmet_info::boxes& list) {
        std::unordered_map<int, helmet_info::boxes>::iterator it;
        for (it = track_history.begin(); it != track_history.end(); it++) {
            if (1.0
                    * ComputeArea(
                        list.x1, list.y1, list.x2, list.y2, it->second.x1, it->second.y1, it->second.x2, it->second.y2)
                    / std::min((list.x2 - list.x1) * (list.y2 - list.y1),
                        (it->second.x2 - it->second.x1) * (it->second.y2 - it->second.y1))
                >= 0.60) {
                return track_history_id[it->first];
            }
        }
        return "";
    }

    abi::string get_random_string(size_t len) {
        abi::string ans;
        std::random_device rd; // 将用于为随机数引擎获得种子
        std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
        std::uniform_int_distribution<> dis(0, 61);
        for (int i = 0; i < len; i++) {
            int temp = dis(gen);
            if (temp < 26)
                ans += ('a' + temp);
            else if (temp < 52)
                ans += ('A' + temp - 26);
            else
                ans += ('0' + temp - 52);
        }
        return ans;
    }
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

            writer.write(img);
        }
        capture.release();
        writer.release();
    }
    void helmet_video(const std::string& name, const std::string& add) {
        cv::VideoCapture capture;
        std::cout << name << "--------\n";
        capture.open("/root/img/video/onphone/onphone_1.mp4");
        std::cout << capture.get(7) << "--------\n";

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

        track_history.clear();
        track_history_id.clear();

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
            // std::vector<int> key_temp;
            // std::vector<helmet_info::boxes> boxes_temp;
            //  for (int i = 0; i < val.head_list.size(); i++) {
            //     if (!track_check(val.head_list[i])) {
            //        int key = (val.head_list[i].x1 + val.head_list[i].x2 >> 1) * 10000
            //                + (val.head_list[i].y1 + val.head_list[i].y2 >> 1);
            //        key_temp.emplace_back(key);
            //        boxes_temp.emplace_back(val.head_list[i]);
            //     }
            // }
            //  for (int i = 0; i < key_temp.size(); i++) {
            //     track_history[key_temp[i] ] = val.head_list[i];
            //     track_history_id[key_temp[i]] = get_random_string(5);
            //  }
            std::unordered_map<int, helmet_info::boxes> temp_faces;
            std::unordered_map<int, std::string> temp_faces_id;
            for (int j = 0; j < val.head_list.size(); j++) {
                int x1              = val.head_list[j].x1;
                int x2              = val.head_list[j].x2;
                int y1              = val.head_list[j].y1;
                int y2              = val.head_list[j].y2;
                int key             = (x1 + x2 >> 1) * 10000 + (y1 + y2 >> 1);
                std::string id_temp = track_check(val.head_list[j]);
                temp_faces[key]     = val.head_list[j];
                if (id_temp == "") {
                    temp_faces_id[key] = get_random_string(5);
                } else
                    temp_faces_id[key] = id_temp;

                rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), GREEN, 6);
                std::string text  = temp_faces_id[key];
                cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                cv::rectangle(
                    img, cv::Point(x1, y1), cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), GREEN, -1);
                putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
            }
            track_history.clear();
            track_history = std::move(temp_faces);
            track_history_id.clear();
            track_history_id = std::move(temp_faces_id);

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
        tt[cnt++] = std::thread(helmet_video, "/root/img/video/onphone/onphone_1.mp4", "_helmet.avi");
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

    void try_a_try(const std::string& name, const std::string& save_path) {
        cv::VideoCapture capture;
        capture.open(name);
        for (int i = 0; i < (1 * 60 + 10) * 20; i++) { // 结束时间
            cv::Mat img;
            capture >> img;
            if (img.empty())
                break;
            if (i >= ((0 * 60 + 10) * 20)) // 开始时间
                cv::imwrite(save_path + "/" + std::to_string(i) + ".jpg", img);
        }
        capture.release();
    }
    void helmet_test(const std::string& save_path, const std::string& ans_path) {
        std::vector<abi::string> temp = find_file(save_path);
        gx_helmet_api* api_temp       = new gx_helmet_api();
        for (int i = 0; i < temp.size(); i++) {
            auto val = api_temp->safe_production_helmet(
                gx_img_api{abi::string{save_path + "/" + std::to_string(i + (0 * 60 + 10) * 20) + ".jpg"}, 1 << 28});
            cv::Mat img =
                cv::imread(abi::string{save_path + "/" + std::to_string(i + (0 * 60 + 10) * 20) + ".jpg"}.c_str());
            if (val.head_list.size() > 0) {
                printf("%d.jpg --------\n", i + (0 * 60 + 10) * 20);
                for (int j = 0; j < val.head_list.size(); j++) {
                    int x1      = val.head_list[j].x1;
                    int x2      = val.head_list[j].x2;
                    int y1      = val.head_list[j].y1;
                    int y2      = val.head_list[j].y2;
                    float score = val.head_list[j].score;
                    rectangle(img, cv::Point(x1, y1), cv::Point(x2, y2), RED, 6);
                    std::string text  = std::to_string(score);
                    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.2, 2, 0);
                    cv::rectangle(img, cv::Point(x1, y1),
                        cv::Point(x1, y1) + cv::Point(textSize.width, -textSize.height), RED, -1);
                    putText(img, text, cv::Point(x1, y1), cv::FONT_HERSHEY_SIMPLEX, 1, WHITE, 2);
                }
                cv::imwrite(ans_path + "/" + std::to_string(i + (0 * 60 + 10) * 20) + ".jpg", img);
            }
        }
    }

} // namespace glasssix


// 3566
//// 多线程测搜索
// void thread_function_search() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     api_temp->user_load();
//     int T      = 500;
//     auto start = std::chrono::high_resolution_clock::now();
//     while (T--) {
//         try {
//             const gx_img_api img("/sdcard/img/action_live_5.jpg", static_cast<int>(1e9));
//             auto val = api_temp->user_search(img, 1, 0.5);
//             printf("similarity =%.3f\n", val.result.size() > 0 ? val.result[0].similarity : 0.0);
//         } catch (const std::exception& ex) {
//             printf("error =  %s\n", ex.what());
//         }
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("search time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }
//// 多线程测融合搜索
// void thread_function_integration() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     api_temp->user_load();
//     auto start = std::chrono::high_resolution_clock::now();
//     int T      = 100;
//     while (T--) {
//         try {
//             // gx_img_api img("/root/img/bbb.jpg", static_cast<int>(1e9));
//             const gx_img_api img("/sdcard/img/action_live_5.jpg", static_cast<int>(1e9));
//             auto val = api_temp->detect_integration(img, 1, 0.5);
//             printf("prob = %.3f\n", val.prob);
//
//         } catch (const std::exception& ex) {
//             printf("error =  %s\n", ex.what());
//         }
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("integration time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }
//// 多线程测 配合活体 与 质量检测
// void thread_function_Action_live_Blur() {
//     gx_face_api* api_temp = new gx_face_api("/sdcard/glasssix-offline-sdk/config");
//     auto start            = std::chrono::high_resolution_clock::now();
//     abi::vector<gx_img_api> img;
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_0.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_1.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_2.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_3.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_4.jpg", IMG_2K));
//     img.emplace_back(gx_img_api("/sdcard/img/action_live_5.jpg", IMG_2K));
//     face_info info;
//     bool action_result = 0;
//     int T              = 500;
//     while (T--) {
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_BLINK, action_result, img[0]);
//         printf("BDFACE_ACTION_LIVE_BLINK %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_OPEN_MOUTH, action_result, img[1]);
//         printf("BDFACE_ACTION_LIVE_OPEN_MOUTH %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_NOD, action_result, img[2]);
//         printf("BDFACE_ACTION_LIVE_NOD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_LEFT_HEAD, action_result, img[3]);
//         printf("BDFACE_ACTION_LIVE_LEFT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         info = api_temp->face_action_live(action_live_type::BDFACE_ACTION_LIVE_RIGHT_HEAD, action_result, img[4]);
//         printf("BDFACE_ACTION_LIVE_RIGHT_HEAD %s\n", action_result ? "VVVVVVVVV" : "XXXXXXXXX");
//         auto val = api_temp->face_blur(img[5]);
//         printf("blur ====== %.2f\n", val.clarity[0]);
//     }
//     auto end      = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//     printf("pedestrian time = %lld microsecond\n", duration.count());
//     delete api_temp;
// }

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
        // test_add_face_all();
        // test_face_search();
        // test_face_compare();
        // test_face_liveness();

        // todo_video();
        // try_a_try("/root/img/helmet.mp4", "/root/img/helmet");
        // helmet_test("/root/img/helmet", "/root/img/helmet_ans");

        /* 多线程测性能测试 */
        std::thread t[30];
        t[0]  = std::thread(thread_function_helmet);
        t[1]  = std::thread(thread_function_flame);
        t[2]  = std::thread(thread_function_refvest);
        t[3]  = std::thread(thread_function_search);
        t[4]  = std::thread(thread_function_integration);
        t[5]  = std::thread(thread_function_leavepost);
        t[6]  = std::thread(thread_function_sleep);
        t[7]  = std::thread(thread_function_smoke);
        t[8]  = std::thread(thread_function_playphone);
        t[9]  = std::thread(thread_function_onphone);
        t[10] = std::thread(thread_function_workcloth);
        t[12] = std::thread(thread_function_pedestrian);
        t[13] = std::thread(thread_function_Action_live_Blur);
        t[14] = std::thread(thread_function_smog);
        t[15] = std::thread(thread_function_tumble);
        t[16] = std::thread(thread_function_climb);
        t[17] = std::thread(thread_function_crowd);
        t[18] = std::thread(thread_function_wander);
        t[19] = std::thread(thread_function_fighting);
        t[0].join();
        t[1].join();
        t[2].join();
        t[3].join();
        t[4].join();
        t[5].join();
        t[6].join();
        t[7].join();
        t[8].join();
        t[9].join();
        t[10].join();
        t[12].join();
        t[13].join();
        t[14].join();
        t[15].join();
        t[16].join();
        t[17].join();
        t[18].join();
        t[19].join();
        //    auto start    = std::chrono::high_resolution_clock::now();
        //    auto end      = std::chrono::high_resolution_clock::now();
        //    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

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
