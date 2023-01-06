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

    get_memory_usage_info();
    char imgs[] = "{\"imgs\":[\"D:/test/img/action_live_0.jpg\",\"D:/test/img/action_live_1.jpg\",\"D:/test/img/"
                  "action_live_2.jpg\",\"D:/test/img/action_live_3.jpg\",\"D:/test/img/action_live_4.jpg\"]}";
    // char imgs[] = "{\"imgs\":[\"D:/test/img/a165_0.jpg\",\"D:/test/img/acti\",\"D:/test/img/"
    //               "action_live_2.jpg\",\"D:/test/img/ac9844live_3.jpg\",\"D:/test/img/action_live_4.jpg\"]}";

    char keys[] =
        "{\"keys\":[\"action_live_0\",\"action_live_1\",\"action_live_2\",\"action_live_3\",\"action_live_4\"]}";

    char img[] = "D:/test/img/action_live_5.jpg";


    printf_demo('c', img);

    gx_user_load();
    // char* ss = gx_user_search(img, 5, 0.4f); //人员搜索
    // std::cout << ss << std::endl;

    char* result = gx_user_add_records(keys, imgs); //人员库批量添加

    printf("%s\n", result);
    printf("%s\n", get_last_error());

    char path[] = "D:/test/no_mask/LSH_bucket";
    printf("cnt =  %d\n", get_disk_keys_num(path));
    char* ss = gx_user_search(img, 5, 0.4f); //人员搜索
    // std::cout << ss << std::endl;

    ss = gx_detect_integration(img, 5, 0.4f); //人脸识别融合
    // std::cout << ss << std::endl;

    result = gx_user_update_records(keys, imgs); //人员库批量更新
    printf("%s\n", result);
    printf("%s\n", get_last_error());

    ss = gx_user_search(img, 5, 0.4f); //人员搜索
    std::cout << ss << std::endl;

    result = gx_user_remove_records(keys); //人员库批量删除记录
    printf("%s\n", result);
    ss = gx_user_search(img, 5, 0.4f); //人员搜索
    std::cout << ss << std::endl;


    gx_user_clear(); //人员库清除缓存  清内存
    gx_user_remove_all(); //人员库清空  清内存和磁盘


    char A[] = "D:/test/img/A/610111200208264510.jpg";
    char B[] = "D:/test/img/B/610111200208264510.jpg";
    std::cout << gx_feature_comparison(A, B) << std::endl;

    return 0;
}
