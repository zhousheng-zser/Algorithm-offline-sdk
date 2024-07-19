#pragma once

#include <cstdint>
#include <vector>

// 徘徊信息
struct wander_info {
    struct boxes {
        float cosine_similarity; // 相似度   没匹配到人值为0
        int id; // 此人在特征库的id号
        long long last_show_time; // 此人最后一次出现的时间
        long long first_show_time; // 此人第一次出现的时间
        int detection_number; // 被检测到次数
        float score; // 置信度
        int x1; // 检出框体左上坐标x
        int y1; // 检出框体左上坐标y
        int x2; // 检出框体右下坐标x
        int y2; // 检出框体右下坐标y

        long long sum_time; // 出现时长
        double detection_fps; // 每秒大概调用徘徊检测次数
    };
    std::vector<boxes> person_info; //  没在玩手机
};

// 越界信息
struct wander_limit_info : public wander_info {
    wander_limit_info(wander_info& temp) {
        person_info.swap(temp.person_info);
    }
    // 行人轨迹线段
    struct segment {
        std::int32_t x1, y1, x2, y2;
    };
    std::vector<segment> segment_info;
};
