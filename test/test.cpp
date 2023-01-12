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

    char data[] = "[{\"key\":\"action_live_0\",\"imgs\":\"D:/test/img/action_live_0.jpg\"},{\"key\":\"action_live_1\",\"imgs\":\"D:/test/img/action_live_1.jpg\"},{\"key\":\"action_live_2\",\"imgs\":\"D:/test/img/action_live_2.jpg\"},{\"key\":\"action_live_3\",\"imgs\":\"D:/test/img/action_live_3.jpg\"},{\"key\":\"action_live_4\",\"imgs\":\"D:/test/img/action_live_4.jpg\"}]";

    char keys[] = "[\"action_live_0\",\"action_live_1\",\"action_live_2\",\"action_live_3\",\"action_live_4\"]";

    char img[] = "D:/test/img/action_live_5.jpg";

    printf_demo('c', img);

    gx_user_load();
    // char* ss = gx_user_search(img, 5, 0.4f); //人员搜索
    // std::cout << ss << std::endl;

    char* result = gx_user_add_records(data , false , true); //人员库批量添加
    printf("%s\n", result);
    printf("%s\n", get_last_error());

    int count = gx_user_count();
    printf("count =  %d\n", count);


    char path[] = "D:/test/no_mask/LSH_bucket";
    printf("cnt =  %d\n", get_disk_keys_num(path));
    char* ss = gx_user_search(img, 5, 0.4f); //人员搜索
     std::cout << ss << std::endl;

    ss = gx_detect_integration(img, 5, 0.4f); //人脸识别融合
    // std::cout << ss << std::endl;

    ss = gx_user_search(img, 5, 0.4f); //人员搜索
    std::cout << ss << std::endl;

    result = gx_user_remove_records(keys); //人员库批量删除记录
    printf("%s\n", result);

    ss = gx_user_search(img, 5, 0.4f); //人员搜索
    std::cout << ss << std::endl;

    gx_user_remove_all(); //人员库清空  清内存和磁盘


    char A[] = "D:/test/img/A/610111200208264510.jpg";
    char B[] = "D:/test/img/B/610111200208264510.jpg";
    std::cout << gx_feature_comparison(A, B) << std::endl;

    return 0;
}
