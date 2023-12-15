#include <parser_c.hpp>
#include <json.h>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <opencv2/opencv.hpp>

std::string longinus_guid;

Json::Value add_trace(Json::Value jsonobj_param, Json::Value jsonobj_face) {
    Json::Value temp;
    temp.clear();
    temp["instance_guid"]  = jsonobj_param["instance_guid"];
    temp["format"]         = jsonobj_param["format"];
    temp["height"]         = jsonobj_param["height"];
    temp["width"]          = jsonobj_param["width"];
    temp["face"]["x"]      = jsonobj_face["x"];
    temp["face"]["y"]      = jsonobj_face["y"];
    temp["face"]["width"]  = jsonobj_face["width"];
    temp["face"]["height"] = jsonobj_face["height"];
    return temp;
}

int test_longinus(void* parser, std::string longinus_guid, Json::FastWriter& writer) {
    // videocapture结构创建一个catture视频对象
    VideoCapture capture;
    // 连接视频
    // capture.open("D:/opencv/test/e8dda5b6c23915758ffcba00753ae2a9.mp4");
    capture.open("D:/opencv/2.jpg");
    // capture.open("D:/opencv/test/weixin.jpg");


    if (!capture.isOpened()) {
        printf("could not load video data...\n");
        return -1;
    }

    int frames = capture.get(CAP_PROP_FRAME_COUNT); // 获取视频针数目(一帧就是一张图片)
    double fps = capture.get(CAP_PROP_FPS); // 获取每针视频的频率
    // 获取帧的视频宽度，视频高度
    Size size = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
    std::cout << frames << std::endl;
    std::cout << fps << std::endl;
    std::cout << size << std::endl;
    namedWindow("video-demo", WINDOW_AUTOSIZE);
    // 创建视频中每张图片对象
    Mat img, temp;
    std::map<int, Json::Value> faces;
    while (1) {

        capture >> img;
        if (img.empty())
            break;
        // cv::cvtColor(temp, img, COLOR_BGR2YUV_I420);

        Json::Reader reader(Json::Features::strictMode());
        Json::Value jsonobj_param;
        Json::Value jsonobj_result;
        Json::Value jsonobj_trace;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"]  = Json::Value(longinus_guid);
        jsonobj_param["format"]         = Json::Int(1);
        jsonobj_param["height"]         = Json::Int(img.rows);
        jsonobj_param["width"]          = Json::Int(img.cols);
        jsonobj_param["min_size"]       = Json::Value(48);
        jsonobj_param["threshold"]      = Json::Value(0.1);
        jsonobj_param["do_attributing"] = Json::Value(false);
        char* result_str                = parser_parse(parser, "Longinus.detect", writer.write(jsonobj_param).c_str(),
                           reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, NULL, 0);
        reader.parse(result_str, jsonobj_result);
        Json::Value jsonobj_face;
        int flag = 0;
        if (jsonobj_result["status"]["code"].asInt() == 0) {
            int list_size = jsonobj_result["facerectwithfaceinfo_list"].size();
            if (list_size)
                flag = 1;
            romancia_data.clear();
            for (int i = 0; i < list_size; i++) {
                jsonobj_face = jsonobj_result["facerectwithfaceinfo_list"][i];

                romancia_data["facerectwithfaceinfo_list"][i]["confidence"] = jsonobj_face["confidence"];
                romancia_data["facerectwithfaceinfo_list"][i]["height"]     = jsonobj_face["height"];
                romancia_data["facerectwithfaceinfo_list"][i]["landmark"]   = jsonobj_face["landmark"];
                romancia_data["facerectwithfaceinfo_list"][i]["width"]      = jsonobj_face["width"];
                romancia_data["facerectwithfaceinfo_list"][i]["x"]          = jsonobj_face["x"];
                romancia_data["facerectwithfaceinfo_list"][i]["y"]          = jsonobj_face["y"];

                int x, y;
                x = jsonobj_face["x"].asInt();
                y = jsonobj_face["y"].asInt();
                int width, height;
                width                = jsonobj_face["width"].asInt();
                height               = jsonobj_face["height"].asInt();
                faces[x * 10000 + y] = add_trace(jsonobj_param, jsonobj_face);
                rectangle(img, Point(x, y), Point(x + width, y + height), Scalar(255, 255, 255), 2);
            }
        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].asString().c_str());
            continue;
        }
        parser_free(result_str);
        result_str = nullptr;

        // 追踪人脸
        std::map<int, Json::Value>::iterator it;
        std::map<int, Json::Value> temp_faces;
        for (it = faces.begin(); it != faces.end();) {
            result_str = parser_parse(parser, "Longinus.trace", writer.write(it->second).c_str(),
                reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, results, 0);
            reader.parse(result_str, jsonobj_trace);

            if (jsonobj_trace["status"]["code"].asInt() == 0 && jsonobj_trace["trace_success"].asBool() == true) {
                flag = 1;
                int x, y;
                x = jsonobj_trace["facerectwithfaceinfo"]["x"].asInt();
                y = jsonobj_trace["facerectwithfaceinfo"]["y"].asInt();
                int width, height;
                width  = jsonobj_trace["facerectwithfaceinfo"]["width"].asInt();
                height = jsonobj_trace["facerectwithfaceinfo"]["height"].asInt();
                rectangle(img, Point(x, y), Point(x + width, y + height), Scalar(0, 255, 0), 2);
                // 更新追踪坐标
                it->second["face"]["x"]      = jsonobj_trace["facerectwithfaceinfo"]["x"];
                it->second["face"]["y"]      = jsonobj_trace["facerectwithfaceinfo"]["y"];
                it->second["face"]["width"]  = jsonobj_trace["facerectwithfaceinfo"]["width"];
                it->second["face"]["height"] = jsonobj_trace["facerectwithfaceinfo"]["height"];
                temp_faces[x * 10000 + y]    = it->second;
                faces.erase(it++);
            } else if (jsonobj_trace["trace_success"].asBool() == false) {
                printf("Error info : %s\n", "trace_success = false ");
                faces.erase(it++);
            } else {
                printf("Error info : %s\n", jsonobj_trace["status"]["message"].asString().c_str());
                faces.erase(it++);
            }
        }
        faces.clear();
        faces = temp_faces;

        cv::imshow("video-demo", img);
        // 在视频播放期间按键退出
        if (flag && waitKey(10) >= 0)
            break;
        else if (waitKey(10) >= 0)
            break;
    }

    // 释放
    capture.release();
}

int test_romancia(void* parser, std::string romancia_guid, Json::FastWriter& writer) {
    // videocapture结构创建一个catture视频对象
    VideoCapture capture;
    // 连接视频
    capture.open("D:/opencv/2.jpg");
    // capture.open("D:/test/img/A/610111200208264510.jpg");
    // capture.open("D:/opencv/test/weixin.jpg");

    if (!capture.isOpened()) {
        printf("could not load video data...\n");
        return -1;
    }

    int frames = capture.get(CAP_PROP_FRAME_COUNT); // 获取视频针数目(一帧就是一张图片)
    double fps = capture.get(CAP_PROP_FPS); // 获取每针视频的频率
    // 获取帧的视频宽度，视频高度
    Size size = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
    std::cout << frames << std::endl;
    std::cout << fps << std::endl;
    std::cout << size << std::endl;
    namedWindow("video-demo", WINDOW_AUTOSIZE);
    // 创建视频中每张图片对象
    Mat img;
    capture >> img;

    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_param;
    Json::Value jsonobj_result;
    jsonobj_param.clear();
    jsonobj_param                  = romancia_data;
    jsonobj_param["instance_guid"] = Json::Value(romancia_guid);
    jsonobj_param["format"]        = Json::Int(1);
    jsonobj_param["height"]        = Json::Int(img.rows);
    jsonobj_param["width"]         = Json::Int(img.cols);

    // 适用于128维特征提取（Gaius）的人脸对齐
    //     char* result_str = parser_parse(parser, "Romancia.alignFace128", writer.write(jsonobj_param).c_str(),
    //     	reinterpret_cast<char*>(img.data), 1ll * img.channels() * img.cols * img.rows, results, 0);
    // 人脸对齐


    char* result_str = parser_parse(parser, "Romancia.alignFace", writer.write(jsonobj_param).c_str(),
        reinterpret_cast<char*>(img.data), 1ll * img.channels() * img.cols * img.rows, results, 0);
    reader.parse(result_str, jsonobj_result);
    if (jsonobj_result["status"]["code"].asInt() == 0) {
        aligned_images_data.clear();
        aligned_images_data["aligned_images"] = jsonobj_result["aligned_images"];
        aligned_images_data["format"]         = jsonobj_result["format"];
    } else {
        std::cout << jsonobj_result["status"]["message"].asString() << std::endl;
    }
    parser_free(result_str);
    result_str = nullptr;

    cv::imshow("video-demo", img);
    // 在视频播放期间按键退出
    //    waitKey(0);
    // 释放
    capture.release();
}

int test_damocles(void* parser, std::string damocles_guid, Json::FastWriter& writer) {
    // videocapture结构创建一个catture视频对象
    VideoCapture capture(0);
    // 连接视频
    // capture.open("D:/opencv/e8dda5b6c23915758ffcba00753ae2a9.mp4");
    // capture.open("D:/opencv/QQ20220809100238.mp4");
    // capture.open("D:/opencv/49909ccdec3c04b95dddb5b9917b96ed.mp4");

    if (!capture.isOpened()) {
        printf("could not load video data...\n");
        return -1;
    }

    int frames = capture.get(CAP_PROP_FRAME_COUNT); // 获取视频针数目(一帧就是一张图片)
    double fps = capture.get(CAP_PROP_FPS); // 获取每针视频的频率
    // 获取帧的视频宽度，视频高度
    Size size = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
    std::cout << frames << std::endl;
    std::cout << fps << std::endl;
    std::cout << size << std::endl;
    namedWindow("video-demo", WINDOW_AUTOSIZE);
    // 创建视频中每张图片对象
    Mat img;
    while (1) {
        capture >> img;
        if (img.empty())
            break;
        Json::Reader reader(Json::Features::strictMode());
        Json::Value jsonobj_param;
        Json::Value jsonobj_result;

        jsonobj_param.clear();
        jsonobj_param["instance_guid"]  = Json::Value(longinus_guid);
        jsonobj_param["format"]         = Json::Int(1);
        jsonobj_param["height"]         = Json::Int(img.rows);
        jsonobj_param["width"]          = Json::Int(img.cols);
        jsonobj_param["min_size"]       = Json::Value(48);
        jsonobj_param["threshold"]      = Json::Value(0.1);
        jsonobj_param["do_attributing"] = Json::Value(false);
        char* result_str                = parser_parse(parser, "Longinus.detect", writer.write(jsonobj_param).c_str(),
                           reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, results, 0);
        reader.parse(result_str, jsonobj_result);
        Json::Value jsonobj_face;
        int x, y;
        int width, height;
        if (jsonobj_result["status"]["code"].asInt() == 0) {
            int list_size = jsonobj_result["facerectwithfaceinfo_list"].size();
            for (int i = 0; i < list_size; i++) {
                jsonobj_face = jsonobj_result["facerectwithfaceinfo_list"][i];
                x            = jsonobj_face["x"].asInt();
                y            = jsonobj_face["y"].asInt();
                width        = jsonobj_face["width"].asInt();
                height       = jsonobj_face["height"].asInt();
                rectangle(img, Point(x, y), Point(x + width, y + height), Scalar(255, 255, 255), 2);
                std::cout << "face x is:" << x << std::endl;
                std::cout << "face y is:" << y << std::endl;
                std::cout << "face width is:" << width << std::endl;
                std::cout << "face height is:" << height << std::endl;
            }
        }
        parser_free(result_str);
        result_str = nullptr;

        jsonobj_param.clear();
        jsonobj_param["instance_guid"] = Json::Value(damocles_guid);
        jsonobj_param["action_cmd"] = Json::Int(3); //// { 0: 眨眼; 1 : 张嘴; 2 : 点头; 3 : 左摇头; 4 : 右摇头}
        jsonobj_param["format"]             = Json::Int(1);
        jsonobj_param["height"]             = Json::Int(img.rows);
        jsonobj_param["width"]              = Json::Int(img.cols);
        jsonobj_param["facerect"]["x"]      = Json::Int(x);
        jsonobj_param["facerect"]["y"]      = Json::Int(y);
        jsonobj_param["facerect"]["width"]  = Json::Int(width);
        jsonobj_param["facerect"]["height"] = Json::Int(height);
        result_str = parser_parse(parser, "Damocles.presentation_attack_detect", writer.write(jsonobj_param).c_str(),
            reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, results, 0);
        reader.parse(result_str, jsonobj_result);
        bool flag = 0;
        if (jsonobj_result["status"]["code"].asInt() == 0) {
            if (jsonobj_result["presentation_attack_result"].asBool() == true) {
                std::cout << "-------动作已经被检测到 :"
                          << "左摇头" << std::endl;

                /*int x, y;
                x = jsonobj_param["facerect"]["x"].asInt() + 10;
                y = jsonobj_param["facerect"]["y"].asInt() + 10;
                int width, height;
                width = jsonobj_param["facerect"]["width"].asInt() - 50;
                height = jsonobj_param["facerect"]["height"].asInt() - 200;
                rectangle(img, Point(x, y), Point(x + width, y + height), Scalar(255, 255, 255), 2);*/
                flag = 1;
            }
        } else {
            printf("Error info : %s\n", jsonobj_result["status"]["message"].asString().c_str());
            continue;
        }
        parser_free(result_str);
        result_str = nullptr;


        cv::imshow("video-demo", img);
        // 在视频播放期间按键退出
        if (waitKey(1) >= 0)
            break;
    }

    // 释放
    capture.release();
}

int test_damocles_spoofing(void* parser, std::string damocles_guid, Json::FastWriter& writer) {
    // videocapture结构创建一个catture视频对象
    VideoCapture capture(1);
    // 连接视频
    // capture.open("D:/opencv/e8dda5b6c23915758ffcba00753ae2a9.mp4");
    // capture.open("D:/opencv/QQ20220809100238.mp4");
    // capture.open("D:/opencv/49909ccdec3c04b95dddb5b9917b96ed.mp4");

    if (!capture.isOpened()) {
        printf("could not load video data...\n");
        return -1;
    }

    int frames = capture.get(CAP_PROP_FRAME_COUNT); // 获取视频针数目(一帧就是一张图片)
    double fps = capture.get(CAP_PROP_FPS); // 获取每针视频的频率
    // 获取帧的视频宽度，视频高度
    Size size = Size(capture.get(CAP_PROP_FRAME_WIDTH), capture.get(CAP_PROP_FRAME_HEIGHT));
    std::cout << frames << std::endl;
    std::cout << fps << std::endl;
    std::cout << size << std::endl;
    namedWindow("video-demo", WINDOW_AUTOSIZE);
    // 创建视频中每张图片对象
    Mat img;
    while (1) {
        capture >> img;
        if (img.empty())
            break;
        Json::Reader reader(Json::Features::strictMode());
        Json::Value jsonobj_param;
        Json::Value jsonobj_result;

        jsonobj_param.clear();
        jsonobj_param["instance_guid"]  = Json::Value(longinus_guid);
        jsonobj_param["format"]         = Json::Int(1);
        jsonobj_param["height"]         = Json::Int(img.rows);
        jsonobj_param["width"]          = Json::Int(img.cols);
        jsonobj_param["min_size"]       = Json::Value(48);
        jsonobj_param["threshold"]      = Json::Value(0.1);
        jsonobj_param["do_attributing"] = Json::Value(false);
        char* result_str                = parser_parse(parser, "Longinus.detect", writer.write(jsonobj_param).c_str(),
                           reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, results, 0);
        reader.parse(result_str, jsonobj_result);
        Json::Value jsonobj_face;
        int x, y;
        int width, height;
        if (jsonobj_result["status"]["code"].asInt() == 0) {
            int list_size = jsonobj_result["facerectwithfaceinfo_list"].size();
            for (int i = 0; i < list_size; i++) {
                jsonobj_face = jsonobj_result["facerectwithfaceinfo_list"][i];
                x            = jsonobj_face["x"].asInt();
                y            = jsonobj_face["y"].asInt();
                width        = jsonobj_face["width"].asInt();
                height       = jsonobj_face["height"].asInt();
                rectangle(img, Point(x, y), Point(x + width, y + height), Scalar(255, 255, 255), 2);
                std::cout << "face x is:" << x << std::endl;
                std::cout << "face y is:" << y << std::endl;
                std::cout << "face width is:" << width << std::endl;
                std::cout << "face height is:" << height << std::endl;
            }
        }
        parser_free(result_str);
        result_str = nullptr;

        jsonobj_param.clear();
        jsonobj_param["instance_guid"] = Json::Value(damocles_guid);
        // jsonobj_param["action_cmd"] = Json::Int(3);    //// { 0: 眨眼; 1 : 张嘴; 2 : 点头; 3 : 左摇头; 4 : 右摇头}
        jsonobj_param["format"] = Json::Int(1);
        jsonobj_param["height"] = Json::Int(img.rows);
        jsonobj_param["width"]  = Json::Int(img.cols);


        if (jsonobj_result["facerectwithfaceinfo_list"].size() <= 0) {
            cv::imshow("video-demo", img);
            // 在视频播放期间按键退出
            waitKey(1);
            continue;
        }

        if (jsonobj_result["status"]["code"].asInt() == 0) {
            int list_size = jsonobj_result["facerectwithfaceinfo_list"].size();
            for (int i = 0; i < list_size; i++) {
                jsonobj_face = jsonobj_result["facerectwithfaceinfo_list"][i];

                jsonobj_param["facerect_list"][i]["x"]      = jsonobj_face["x"];
                jsonobj_param["facerect_list"][i]["y"]      = jsonobj_face["y"];
                jsonobj_param["facerect_list"][i]["width"]  = jsonobj_face["width"];
                jsonobj_param["facerect_list"][i]["height"] = jsonobj_face["height"];
            }
        }

        result_str = parser_parse(parser, "Damocles.spoofing_detect", writer.write(jsonobj_param).c_str(),
            reinterpret_cast<char*>(img.data), img.channels() * img.cols * img.rows, results, 0);
        reader.parse(result_str, jsonobj_result);
        bool flag = 0;
        if (jsonobj_result["status"]["code"].asInt() == 0) {
            for (int i = 0; i < jsonobj_result["spoofing_result"].size(); ++i) {
                std::cout << "prob [0] = " << jsonobj_result["spoofing_result"][i]["prob"][0].asFloat() << "\n";
                std::cout << "prob [1] = " << jsonobj_result["spoofing_result"][i]["prob"][1].asFloat() << "\n";
                std::cout << "prob [2] = " << jsonobj_result["spoofing_result"][i]["prob"][2].asFloat() << "\n";
            }
            std::cout << "-------------华丽的分割线-----------------\n";
        } else {
            printf("Error info : %s\n", jsonobj_result["status"]["message"].asString().c_str());
            continue;
        }
        parser_free(result_str);
        result_str = nullptr;


        cv::imshow("video-demo", img);
        // 在视频播放期间按键退出
        if (waitKey(1) >= 0)
            break;
    }

    // 释放
    capture.release();
}

std::vector<Json::Value> test_selene(void* parser, std::string selene_guid, Json::FastWriter& writer) {

    std::vector<Json::Value> ans;
    // videocapture结构创建一个catture视频对象

    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_param;
    Json::Value jsonobj_result;
    jsonobj_param.clear();
    jsonobj_param["instance_guid"]  = Json::Value(selene_guid);
    jsonobj_param["format"]         = aligned_images_data["format"];
    jsonobj_param["aligned_images"] = aligned_images_data["aligned_images"];


    // Selene 256维特征提取
    char* result_str =
        parser_parse(parser, "Selene.forward", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);

    // Selene 256维模拟口罩特征提取
    // char* result_str = parser_parse(parser, "Selene.make_mask_forward", writer.write(jsonobj_param).c_str(),
    //     nullptr, 0, results, 0);

    reader.parse(result_str, jsonobj_result);
    if (jsonobj_result["status"]["code"].asInt() == 0) {
        if (jsonobj_result["features"].size()) {
            int list_size = jsonobj_result["features"].size();
            Json::Value jsonobj_gaius;
            jsonobj_gaius.clear();
            for (int i = 0; i < list_size; i++) {
                jsonobj_gaius = jsonobj_result["features"][i];
                ans.push_back(jsonobj_gaius);
            }
        }
        printf("sonobj_result[\"features\"].size= %d\n", jsonobj_result["features"].size());

    } else {
        printf("Error info : %s\n", jsonobj_result["status"]["message"].asString().c_str());
    }
    parser_free(result_str);
    result_str = nullptr;

    return ans;
}

Json::Value test_irisviel_load(
    void* parser, std::string irisviel_guid, Json::FastWriter& writer, Json::Value& jstr_param) // 人员库加载
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    char* result_str =
        parser_parse(parser, "Irisviel.load_databases", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_search(void* parser, std::string irisviel_guid, Json::FastWriter& writer,
    Json::Value& jstr_param, Json::Value temp_feature) // 人员库搜索
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"]  = Json::Value(irisviel_guid);
    jstr_param["top"]            = Json::Value(5);
    jstr_param["min_similarity"] = Json::Value(0.001);
    jstr_param["feature"]        = temp_feature["feature"];
    // for (int i = 0; i < 128; ++i)
    //{
    //     jstr_param["feature"][i] = Json::Value(0.1);
    // }
    char* result_str = parser_parse(parser, "Irisviel.search", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    printf("search ans ==========================\n %s\n", result_str);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_clear(
    void* parser, std::string irisviel_guid, Json::FastWriter& writer, Json::Value& jstr_param) // 人员库清除缓存 清内存
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    char* result_str = parser_parse(parser, "Irisviel.clear", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_removeAll(void* parser, std::string irisviel_guid, Json::FastWriter& writer,
    Json::Value& jstr_param) // 人员库清空  清内存和磁盘
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    char* result_str =
        parser_parse(parser, "Irisviel.remove_all", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_removeRecords(void* parser, std::string irisviel_guid, Json::FastWriter& writer,
    Json::Value& jstr_param, std::vector<std::string> keys) // 人员库批量删除记录
{
    keys.clear();
    keys.push_back("namea");
    keys.push_back("nameb");
    keys.push_back("namec");


    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    for (int i = 0; i < keys.size(); ++i)
        jstr_param["keys"][i] = Json::Value(keys[i]);
    char* result_str =
        parser_parse(parser, "Irisviel.remove_records", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_addRecords(void* parser, std::string irisviel_guid, Json::FastWriter& writer,
    Json::Value& jstr_param, std::vector<Json::Value> temp_features) // 人员库批量添加记录
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    // for (int i = 0; i < temp_features.size(); i++)
    //{
    //     jstr_param["data"][i]["feature"] = temp_features[i]["feature"];
    //     std::string temp = "name"; temp += 'a' + i;
    //     jstr_param["data"][i]["key"] = Json::Value(temp);
    // }
    for (int i = 0; i < 3; i++) {
        jstr_param["data"][i]["feature"] = temp_features[0]["feature"];
        std::string temp                 = "name";
        temp += 'a' + i;
        jstr_param["data"][i]["key"] = Json::Value(temp);
    }

    char* result_str =
        parser_parse(parser, "Irisviel.add_records", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

Json::Value test_irisviel_updateRecords(void* parser, std::string irisviel_guid, Json::FastWriter& writer,
    Json::Value& jstr_param, std::vector<Json::Value> Json_keys) // 人员库批量更新记录
{
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_result;
    jstr_param.clear(); //
    jstr_param["instance_guid"] = Json::Value(irisviel_guid);
    /// 日常
    // for (int i = 0; i < Json_keys.size(); ++i)
    //     jstr_param["data"][i] = Json_keys[i];

    ///  临时
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 512; ++j) {
            jstr_param["data"][i]["feature"][j] = Json::Value(0.1);
        }
        std::string temp = "name";
        temp += 'a' + i;
        jstr_param["data"][i]["key"] = Json::Value(temp);
    }

    char* result_str =
        parser_parse(parser, "Irisviel.update_records", writer.write(jstr_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    parser_free(result_str);
    result_str = nullptr;
    return jsonobj_result;
}

// 融合对齐256维特征提取
std::vector<Json::Value> test_romancia_selene(
    void* parser, std::string romancia_guid, std::string selene_guid, Json::FastWriter& writer) {
    std::vector<Json::Value> ans;
    Json::Reader reader(Json::Features::strictMode());
    Json::Value jsonobj_param;
    Json::Value jsonobj_result;
    // videocapture结构创建一个catture视频对象
    VideoCapture capture;
    // 连接视频
    capture.open("D:/opencv/test/more.jpg");
    if (!capture.isOpened()) {
        printf("could not load video data...\n");
        return ans;
    }
    namedWindow("video-demo", WINDOW_AUTOSIZE);
    // 创建视频中每张图片对象
    Mat img;
    capture >> img;

    jsonobj_param.clear();
    jsonobj_param                           = romancia_data;
    jsonobj_param["romancia_instance_guid"] = Json::Value(romancia_guid);
    jsonobj_param["gaius_instance_guid"]    = Json::Value(selene_guid);
    jsonobj_param["format"]                 = Json::Int(1);
    jsonobj_param["height"]                 = Json::Int(img.rows);
    jsonobj_param["width"]                  = Json::Int(img.cols);

    char* result_str = parser_parse(parser, "Fusion.Romancia.alignFace.Selene.forward",
        writer.write(jsonobj_param).c_str(), nullptr, 0, results, 0);

    reader.parse(result_str, jsonobj_result);
    if (jsonobj_result["status"]["code"].asInt() == 0) {
        if (jsonobj_result["features"].size()) {
            int list_size = jsonobj_result["features"].size();
            Json::Value jsonobj_selene;
            jsonobj_selene.clear();
            for (int i = 0; i < list_size; i++) {
                jsonobj_selene = jsonobj_result["features"][i];
                ans.push_back(jsonobj_selene);
            }
        }
        printf("sonobj_result[\"features\"].size= %d\n", jsonobj_result["features"].size());
    } else {
        printf("Error info : %s\n", jsonobj_result["status"]["message"].asString().c_str());
    }
    parser_free(result_str);
    result_str = nullptr;

    cv::imshow("video-demo", img);
    // 在视频播放期间按键退出
    waitKey(0);
    // 释放
    capture.release();

    return ans;
}


int main() {

    Json::Reader reader(Json::Features::strictMode());
    Json::FastWriter writer;
    Json::Value jsonobj_result;
    Json::Value jsonobj_param;

    const char config_file_path[] = "D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/configure_file/plugin_configure.json";
    void* parser                  = parser_new_instance();
    char* result_str              = parser_init_plugin(parser, config_file_path, "");
    reader.parse(result_str, jsonobj_result);

    if (jsonobj_result["status"]["code"].asInt() == 0)
        printf("Successfully init sdk.\n");
    else {
        printf("Error info : %s \n", jsonobj_result["status"]["message"].asString().c_str());
        exit(-1);
    }

#pragma region
    // 创建Longinus实例
    jsonobj_param.clear();
    jsonobj_param["device"]           = Json::Int(0);
    jsonobj_param["models_directory"] = Json::Value("D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/models");
    result_str = parser_parse(parser, "Longinus.new", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    if (jsonobj_result["status"]["code"].asInt() == 0)
        longinus_guid = jsonobj_result["instance_guid"].asString();
    else {
        printf("Error info :%s\n", jsonobj_result["status"]["message"].asString().c_str());
        exit(-1);
    }
    parser_free(result_str);
    result_str = nullptr;
    // test_longinus(parser, longinus_guid, writer); // 人脸识别 + 追踪
    // longinus___(parser, longinus_guid, writer);

    // 删除Longinus实例
    // jsonobj_param.clear();
    // jsonobj_param["instance_guid"] = Json::Value(longinus_guid);
    // result_str = parser_parse(parser, "Longinus.delete", writer.write(jsonobj_param).c_str(), nullptr, 0, results,
    // 0); parser_free(result_str); result_str = nullptr;
    //

#pragma endregion Longinus Demo

#pragma region
    // 创建Romancia实例
    jsonobj_param.clear();
    jsonobj_param["device"]           = Json::Int(0);
    jsonobj_param["models_directory"] = Json::Value("D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/models");
    result_str = parser_parse(parser, "Romancia.new", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    std::string romancia_guid;
    if (jsonobj_result["status"]["code"].asInt() == 0)
        romancia_guid = jsonobj_result["instance_guid"].asString();
    else {
        printf("Error info :%s\n", jsonobj_result["status"]["message"].asString().c_str());
        exit(-1);
    }
    parser_free(result_str);
    result_str = nullptr;
    // test_romancia(parser, romancia_guid, writer); // 人脸对齐
    /// 删除Romancia实例
    // jsonobj_param.clear();
    // jsonobj_param["instance_guid"] = Json::Value(romancia_guid);
    // result_str = parser_parse(parser, "Romancia.delete", writer.write(jsonobj_param).c_str(), nullptr, 0, results,
    // 0); parser_free(result_str); result_str = nullptr;

#pragma endregion Romancia Demo

#pragma region
    // 创建Damocles实例
    jsonobj_param.clear();
    jsonobj_param["device"]           = Json::Int(-1);
    jsonobj_param["use_int8"]         = Json::Value(false);
    jsonobj_param["models_directory"] = Json::Value("D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/models");
    result_str = parser_parse(parser, "Damocles.new", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    std::string damocles_guid;
    if (jsonobj_result["status"]["code"].asInt() == 0)
        damocles_guid = jsonobj_result["instance_guid"].asString();
    else {
        printf("Error info :%s\n", jsonobj_result["status"]["message"].asString().c_str());
        exit(-1);
    }
    parser_free(result_str);
    result_str = nullptr;
    // test_damocles(parser, damocles_guid, writer); // 活体动作检测
    test_damocles_spoofing(parser, damocles_guid, writer); // 非配合 活体检测
    /// 删除Damocles实例
    jsonobj_param.clear();
    jsonobj_param["instance_guid"] = Json::Value(damocles_guid);
    result_str = parser_parse(parser, "Damocles.delete", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);
    parser_free(result_str);
    result_str = nullptr;

#pragma endregion Damocles Demo

#pragma region
    // 创建Selene实例
    jsonobj_param.clear();
    jsonobj_param["device"]           = Json::Int(-1);
    jsonobj_param["model_type"]       = Json::Int(0);
    jsonobj_param["models_directory"] = Json::Value("D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/models");
    jsonobj_param["use_int8"]         = Json::Value(false);
    result_str = parser_parse(parser, "Selene.new", writer.write(jsonobj_param).c_str(), nullptr, 0, NULL, 0);
    reader.parse(result_str, jsonobj_result);
    std::string selene_guid;
    if (jsonobj_result["status"]["code"].asInt() == 0)
        selene_guid = jsonobj_result["instance_guid"].asString();
    else {
        printf("Error info :%s\n", jsonobj_result["status"]["message"].asString().c_str());
        exit(-1);
    }
    parser_free(result_str);
    result_str = nullptr;
    std::vector<Json::Value> temp_features256;
    // temp_features256 = test_selene(parser, selene_guid, writer);//  256特征提取

    // 删除Selene实例
    // jsonobj_param.clear();
    // jsonobj_param["instance_guid"] = Json::Value(selene_guid);
    // result_str = parser_parse(parser, "Selene.delete", writer.write(jsonobj_param).c_str(), nullptr, 0, results, 0);
    // parser_free(result_str);
    // result_str = nullptr;

#pragma endregion Selene Demo

//#pragma region
//    // 创建Irisviel实例
//    jsonobj_param.clear();
//    jsonobj_param["dimension"]         = Json::Int(512);
//    jsonobj_param["working_directory"] = Json::Value("D:/opencv/test");
//    result_str = parser_parse(parser, "Irisviel.new", writer.write(jsonobj_param).c_str(), nullptr, 0, results, 0);
//    reader.parse(result_str, jsonobj_result);
//    std::string irisviel_guid;
//    if (jsonobj_result["status"]["code"].asInt() == 0)
//        irisviel_guid = jsonobj_result["instance_guid"].asString();
//    else {
//        printf("Error info :%s\n", jsonobj_result["status"]["message"].asString().c_str());
//        exit(-1);
//    }
//    parser_free(result_str);
//    result_str = nullptr;
//
//    Json::Value jstr_param, jstr_result;
//    // 没有
//    int flag = -1;
//    do {
//        printf("Input Irisviel key (0-9), (-1 exit): \n");
//        scanf_s("%d", &flag);
//        std::vector<std::string> keys;
//        std::string key;
//        std::vector<Json::Value> Json_keys;
//        Json::Value Json_key;
//        if (flag == 0)
//            jstr_result = test_irisviel_load(parser, irisviel_guid, writer, jstr_param); // 人员库加载
//        else if (flag == 1)
//            jstr_result =
//                test_irisviel_search(parser, irisviel_guid, writer, jstr_param, temp_features512[0]); // 人员库搜索
//        else if (flag == 2)
//            jstr_result = test_irisviel_clear(parser, irisviel_guid, writer, jstr_param); // 人员库清除缓存  清内存
//        else if (flag == 3)
//            jstr_result = test_irisviel_removeAll(parser, irisviel_guid, writer, jstr_param); // 人员库清空 清内存和磁盘
//        else if (flag == 4)
//            jstr_result =
//                test_irisviel_removeRecords(parser, irisviel_guid, writer, jstr_param, keys); // 人员库批量删除记录
//        else if (flag == 6)
//            jstr_result = test_irisviel_addRecords(
//                parser, irisviel_guid, writer, jstr_param, temp_features512); // 人员库批量添加记录
//        else if (flag == 7)
//            jstr_result = test_irisviel_addRecord(
//                parser, irisviel_guid, writer, jstr_param, temp_features512[0]); // 人员库添加记录
//        else if (flag == 8)
//            jstr_result =
//                test_irisviel_updateRecords(parser, irisviel_guid, writer, jstr_param, Json_keys); // 人员库批量更新记录
//        else
//            break;
//    } while (flag != -1);
//
//
//    // 删除Irisviel实例
//    jsonobj_param.clear();
//    jsonobj_param["instance_guid"] = Json::Value(irisviel_guid);
//    result_str = parser_parse(parser, "Irisviel.delete", writer.write(jsonobj_param).c_str(), nullptr, 0, results, 0);
//    parser_free(result_str);
//    result_str = nullptr;
//
//#pragma endregion Irisviel Demo

    parser_release_instance(parser); //
    parser = nullptr;
    free(results);

    return 0;
}
