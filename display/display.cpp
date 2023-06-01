#include <opencv2/opencv.hpp>
#include "mpp/media.hpp"
#include <thread>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <gx_api.h>
#include <g6/format_remediation.hpp>
#include <fstream>
using namespace glasssix;

namespace {

    std::ofstream ofp;
    constexpr auto make_buffer(const std::uint8_t* buffer, int len) noexcept {
        return std::span<const std::uint8_t>{buffer, static_cast<std::uint32_t>(0+len)};
    }

    std::string get_time() {
        std::time_t t = std::time(nullptr);
        std::tm* local_time = std::localtime(&t);
        return glasssix::format(U8("{}_{}_{}_{}_{}"), (local_time->tm_year + 1900), (local_time->tm_mon + 1),
            local_time->tm_mday, local_time->tm_hour, local_time->tm_min);
    }

} // namespace

namespace glasssix {

    //gx_api* api = new gx_api("/root/test/config");
    gx_api* api = new gx_api();

void data_callback_Track(
    const std::uint8_t* data, std::size_t frame_index, std::int32_t stride, std::int32_t width, std::int32_t height) {
        if (frame_index % 2)
            return;
        gx_img_api mat(make_buffer(data, height * width * 3), height, width);
        nlohmann::json ans = api->track(mat);
        ofp << ans.dump() << "\n";
        ofp.flush();
        printf("frame_index =%lld\n", frame_index);
        cv::Mat img(height, width, CV_8UC3);
        std::memcpy(img.data, data, width * height * img.channels());
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        cv::imshow("video-demo", img);
        cv::waitKey(1);
}
void data_callback_Face_feature(
    const std::uint8_t* data, std::size_t frame_index, std::int32_t stride, std::int32_t width, std::int32_t height) {
        if (frame_index % 2)
            return;
        gx_img_api mat(make_buffer(data, height * width * 3), height, width);
        nlohmann::json ans = api->face_feature(mat, false);
        ofp << ans.dump() << "\n";
        ofp.flush();
        printf("frame_index =%lld\n", frame_index);
        cv::Mat img(height, width, CV_8UC3);
        std::memcpy(img.data, data, width * height * img.channels());
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        cv::imshow("video-demo", img);
        cv::waitKey(1);
}
void data_callback_detect_integration(
    const std::uint8_t* data, std::size_t frame_index, std::int32_t stride, std::int32_t width, std::int32_t height) {
    if (frame_index % 2)
        return;
    gx_img_api mat(make_buffer(data, height * width * 3), height, width);
    nlohmann::json ans = api->detect_integration(mat, 1, 0.0);
    ofp << ans.dump() << "\n";
    ofp.flush();
    printf("frame_index =%lld\n", frame_index);
    cv::Mat img(height, width, CV_8UC3);
    std::memcpy(img.data, data, width * height * img.channels());
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    cv::imshow("video-demo", img);
    cv::waitKey(1);
}
void data_callback_search(
    const std::uint8_t* data, std::size_t frame_index, std::int32_t stride, std::int32_t width, std::int32_t height) {
    if (frame_index % 2)
        return; 
    gx_img_api mat(make_buffer(data, height*width*3), height, width);
    nlohmann::json ans = api->user_search(mat, 1, 0.0);
    ofp << ans.dump() << "\n";
    ofp.flush();
    printf("frame_index =%lld\n", frame_index);
    cv::Mat img(height, width, CV_8UC3);
    std::memcpy(img.data, data, width * height * img.channels());
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    cv::imshow("video-demo", img);
    cv::waitKey(1);
}

void error_callback(const char* message) {
    printf("+++++++ %s\n", message);
}

}

int main() {

    printf("\t1. Track\n");
    printf("\t2. Face_feature\n");
    printf("\t3. Detect_integration\n");
    printf("\t4. Search\n");
    int chose;
    std::cin >> chose;
    
    auto tmp = [&] {
        if (chose == 1) {

            ofp.open("/root/test_log/" + get_time() + "_Track.txt", std::ios::app);
            return g6_start_playback(
                "rtsp://admin:hk123456@192.168.4.140:554/ch1/main/av_stream", &data_callback_Track, &error_callback);

        } else if (chose == 2) {
            ofp.open("/root/test_log/" + get_time() + "_Face_feature.txt", std::ios::app);
            return g6_start_playback("rtsp://admin:hk123456@192.168.4.140:554/ch1/main/av_stream",
                &data_callback_Face_feature, &error_callback);

        } else if (chose == 3) {
            ofp.open("/root/test_log/" + get_time() + "_Detect_integration.txt", std::ios::app);
            return g6_start_playback("rtsp://admin:hk123456@192.168.4.140:554/ch1/main/av_stream",
                &data_callback_detect_integration, &error_callback);

        } else if (chose == 4) {
            ofp.open("/root/test_log/" + get_time() + "_Search.txt", std::ios::app);
            return g6_start_playback(
                "rtsp://admin:hk123456@192.168.4.140:554/ch1/main/av_stream", &data_callback_search, &error_callback);

        } else {
            std::exit(0);
        }
    }();

    for (;;) {
        std::this_thread::yield();
    }

    return 0;
}