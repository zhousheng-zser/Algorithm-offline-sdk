#include <algorithm>
#include <iostream>
#include <optional>

#include <face_info.hpp>
#include <gtest/gtest.h>
#include <gx_face_api_c.hpp>
#include <io.h>
#include <opencv2/opencv.hpp>
using namespace glasssix::face;
using namespace glasssix;


int main(int argc, char** argv) {
    char imgs[][100] = {"D:/test/img/action_live_0.jpg", "D:/test/img/action_live_1.jpg",
        "D:/test/img/action_live_2.jpg", "D:/test/img/action_live_3.jpg", "D:/test/img/action_live_4.jpg"};
    char keys[][50]  = {"action_live_0", "action_live_1", "action_live_2", "action_live_3", "action_live_4"};

    char* k[5];
    k[0] = &keys[0][0];
    k[1] = keys[1];
    k[2] = keys[2];
    k[3] = keys[3];
    k[4] = keys[4];
    char* path[5];
    path[0] = &imgs[0][0];
    path[1] = imgs[1];
    path[2] = imgs[2];
    path[3] = imgs[3];
    path[4] = imgs[4];

    char img[] = "D:/test/img/action_live_5.jpg";

    gx_user_load();
    bool* result = gx_user_add_records(k, 5, path, false); //人员库批量添加
    char* ss     = gx_user_search(img, 5, 0.4f, false); //人员搜索
    std::cout << ss << std::endl;

    ss = gx_detect_integration(img, 5, 0.4f, false); //人脸识别融合
    std::cout << ss << std::endl;

    k[0] = keys[1];
    k[1] = keys[0];
    k[2] = keys[3];
    k[3] = keys[2];
    gx_user_update_records(k, 5, path, false); //人员库批量更新
    ss = gx_user_search(img, 5, 0.4f, false); //人员搜索
    std::cout << ss << std::endl;

    gx_user_remove_records(k, 5, false); //人员库批量删除记录
    ss = gx_user_search(img, 5, 0.4f, false); //人员搜索
    std::cout << ss << std::endl;


    gx_user_clear(false); //人员库清除缓存  清内存
    gx_user_remove_all(false); //人员库清空  清内存和磁盘


    char A[] = "D:/test/img/A/610111200208264510.jpg";
    char B[] = "D:/test/img/B/610111200208264510.jpg";
    std::cout << gx_feature_comparison(A, B) << std::endl;

    return 0;
}
