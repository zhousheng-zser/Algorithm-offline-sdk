#include <algorithm>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <random>
#include <thread>

#include <g6/gx_api.hpp>
#include <g6/gx_face_api.hpp>
#include <g6/json.hpp>


// #include <gx_api_c.hpp>
#include <g6/json_extensions.hpp>

using namespace glasssix;

// 配置。
static const abi::string CONFIG_PATH = "/root/install/glasssix-offline-sdk/config";

// 入库。
static const abi::string ADD_SRC = "/userdata/img-jan/base-10000/";
static const std::string ADD_TXT = "/userdata/img-jan/base-10000/base-10000.txt";
static const std::string ADD_LOG = "/userdata/results/face_result/add_1w.log";

// 搜索。
static const abi::string SEARCH_SRC = "/userdata/img-jan/search_and_living-p1w/";
static const std::string SEARCH_TXT = "/userdata/img-jan/search_and_living-p1w/search_and_living-p1w.txt";
static const std::string SEARCH_LOG = "/userdata/results/face_result/search_24hour.log";
static const bool SEARCH_POSITIVE   = false;

// 活体。
static const abi::string LIVING_SRC = "/userdata/img-jan/search_and_living-p1w/";
static const std::string LIVING_TXT = "/userdata/img-jan/search_and_living-p1w/search_and_living-p1w.txt";
static const std::string LIVING_LOG = "/userdata/results/face_result/living_24hour.log";

// 比对。
static const abi::string COMPARE_SRC = "/userdata/img-jan/compare-p1w/";
static const std::string COMPARE_TXT = "/userdata/img-jan/compare-p1w/compare-p1w.txt";
static const std::string COMPARE_LOG = "/userdata/results/face_result/compare_24hour.log";


// 帮测试写的测试工具
namespace glasssix {

    static std::string getCurrentTime() {
        auto now     = std::chrono::system_clock::now();
        auto current = std::chrono::system_clock::to_time_t(now);
        char format_time[80];
        std::strftime(format_time, sizeof(format_time), "%Y-%m-%d %H:%M:%S", std::localtime(&current));
        return {format_time};
    }

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

    // 人脸入库
    void test_add_face_all() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        _api->user_load();
        _api->user_remove_all();
        printf(" const = %d \n", _api->user_record_count());
        auto start = std::chrono::high_resolution_clock::now();
        std::ifstream path_file(ADD_TXT, std::ios::in);
        std::ofstream log_file(ADD_LOG, std::ios::out | std::ios::trunc);
        abi::string path, key;
        std::cout << "adding ..." << std::endl;
        while (1) {
            abi::vector<abi::string> keys;
            abi::vector<gx_img_api> mat;
            // 控制入库批次。（rv1106、rv1109建议设置不超过300，其他平台设置1000）
            int T = 100;
            while ((path_file >> path >> key) && (T--)) {
                try {
                    mat.emplace_back(gx_img_api{ADD_SRC + path, static_cast<int>(1e9)});
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
        std::cout << "add finished" << std::endl;
    }

    // 人脸1:1。
    void test_face_compare() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::fstream path_file(COMPARE_TXT, std::ios::in);
        std::ofstream log_file(COMPARE_LOG, std::ios::out | std::ios::trunc);
        abi::string path1, path2;
        printf("compare testing...");
        while (path_file >> path1 >> path2) {
            json data;
            data["compare"] = path1 + " " + path2;

            gx_img_api img1(COMPARE_SRC + path1, 1e9);
            gx_img_api img2(COMPARE_SRC + path2, 1e9);
            // 统计接口耗时。
            auto start         = std::chrono::high_resolution_clock::now();
            auto similarity    = _api->feature_comparison(img1, img2);
            auto end           = std::chrono::high_resolution_clock::now();
            auto duration      = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            data["cost"]       = duration.count();
            data["similarity"] = similarity;
            if (similarity > 0.0f) {
                data["result"] = "success";
            } else {
                data["result"] = "fail";
            }

            log_file << data << std::endl;
        }
        printf("compare completed!");
        delete _api;
    }

    // 比对稳定性。
    static void test_face_compare_24hour() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::ofstream log_file(COMPARE_LOG, std::ios::out | std::ios::trunc);
        std::fstream path_file(COMPARE_TXT, std::ios::in);
        abi::string path1, path2;
        printf("compare 24hour testing...");
        // 持续执行 24 小时。
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time   = start_time + std::chrono::hours(24);
        while (std::chrono::high_resolution_clock::now() < end_time) {

            // 重置文件指针到开头。
            path_file.clear();
            path_file.seekg(0, std::ios::beg);

            while (path_file >> path1 >> path2) {

                // 文件未读完但超过了结束时间，也终止程序运行。
                if (std::chrono::high_resolution_clock::now() > end_time) {
                    break;
                }

                json data;
                // 记录当前系统时间。
                std::string currentTime = glasssix::getCurrentTime();
                data["date"]            = currentTime.c_str();
                data["compare"]         = path1 + " " + path2;
                gx_img_api img1(COMPARE_SRC + path1, 1e9);
                gx_img_api img2(COMPARE_SRC + path2, 1e9);

                // 统计接口耗时。
                auto start         = std::chrono::high_resolution_clock::now();
                auto similarity    = _api->feature_comparison(img1, img2);
                auto end           = std::chrono::high_resolution_clock::now();
                auto duration      = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                data["cost"]       = duration.count();
                data["similarity"] = similarity;
                if (similarity > 0.0f) {
                    data["result"] = "success";
                } else {
                    data["result"] = "fail";
                }

                log_file << data << std::endl;

                // 线程睡眠 100 毫秒。
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        printf("compare 24hour completed!");
        delete _api;
    }

    // 人脸活体。
    void test_face_liveness() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::fstream path_file(LIVING_TXT, std::ios::in);
        std::ofstream log_file(LIVING_LOG, std::ios::out | std::ios::trunc);
        abi::string path, key;
        printf("live testing...");
        while (path_file >> path >> key) {
            json data;
            data["predicted_key"] = path + " " + key;
            gx_img_api img(LIVING_SRC + path, IMG_2K);
            // 统计接口耗时。
            auto start    = std::chrono::high_resolution_clock::now();
            auto val      = _api->face_spoofing_live(img);
            auto end      = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            data["cost"]  = duration.count();
            if (val.spoofing_result.size() > 0) {
                data["prob"]   = val.spoofing_result[0].prob[1];
                data["result"] = "success";
                log_file << data << std::endl;
            } else {
                data["prob"]   = 0.0f;
                data["result"] = "fail";
                log_file << data << std::endl;
            }
        }
        printf("live completed!");
        delete _api;
    }

    // 活体稳定性
    static void test_face_liveness_24hour() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::ofstream log_file(LIVING_LOG, std::ios::out | std::ios::app);
        std::fstream path_file(LIVING_TXT, std::ios::in);
        abi::string path, key;
        printf("living 24hour testing...");
        // 持续执行 24 小时。
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time   = start_time + std::chrono::hours(24);
        while (std::chrono::high_resolution_clock::now() < end_time) {

            // 重置文件指针到开头。
            path_file.clear();
            path_file.seekg(0, std::ios::beg);

            while (path_file >> path >> key) {

                // 文件未读完但超过了结束时间，也终止程序运行。
                if (std::chrono::high_resolution_clock::now() > end_time) {
                    break;
                }

                json data;
                // 记录当前系统时间。
                std::string currentTime = glasssix::getCurrentTime();
                data["date"]            = currentTime.c_str();
                data["predicted_key"]   = path + " " + key;
                gx_img_api img(LIVING_SRC + path, IMG_2K);
                // 统计接口耗时。
                auto start    = std::chrono::high_resolution_clock::now();
                auto val      = _api->face_spoofing_live(img);
                auto end      = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                data["cost"]  = duration.count();
                if (val.spoofing_result.size() > 0) {
                    data["prob"]   = val.spoofing_result[0].prob[1];
                    data["result"] = "success";
                    log_file << data << std::endl;
                } else {
                    data["prob"]   = 0.0f;
                    data["result"] = "fail";
                    log_file << data << std::endl;
                }

                // 线程睡眠 100 毫秒。
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        printf("living 24hour completed!");
        delete _api;
    }


    // 人脸搜索
    static void test_face_search() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::ofstream log_file(SEARCH_LOG, std::ios::out | std::ios::trunc);
        std::fstream path_file(SEARCH_TXT, std::ios::in);
        abi::string path, key;
        _api->user_load();
        printf("search testing...");
        while (path_file >> path >> key) {
            json data;
            data["predicted_key"] = path + " " + key;
            gx_img_api img(SEARCH_SRC + path, IMG_2K);

            // 正样本处理逻辑：
            if (SEARCH_POSITIVE) {
                // 特征库能查到。
                if (_api->user_contains_key(key)) {
                    // 统计接口耗时。
                    auto start    = std::chrono::high_resolution_clock::now();
                    auto val      = _api->user_search(img, 1, 0.1);
                    auto end      = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    data["cost"]  = duration.count();
                    // 有结果返回。
                    if (val.result.size()) {
                        data["similarity"] = val.result[0].similarity;
                        data["actual_key"] = val.result[0].data.key;
                        data["result"]     = "success";
                        log_file << data << std::endl;

                    } else {
                        data["result"] = "fail:no result!";
                        log_file << data << std::endl;
                    }

                } else {
                    data["result"] = "fail:not in database!";
                    log_file << data << std::endl;
                }
            } else {
                // 负样本处理逻辑：
                // 统计接口耗时。
                auto start    = std::chrono::high_resolution_clock::now();
                auto val      = _api->user_search(img, 1, 0.1);
                auto end      = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                data["cost"]  = duration.count();
                // 有结果返回。
                if (val.result.size()) {
                    data["similarity"] = val.result[0].similarity;
                    data["actual_key"] = val.result[0].data.key;
                    data["result"]     = "success";
                    log_file << data << std::endl;

                } else {
                    data["result"] = "fail:no result!";
                    log_file << data << std::endl;
                }
            }
        }
        printf("search completed!");
        delete _api;
    }

    // 人脸搜索稳定性
    static void test_face_search_24hour() {
        gx_face_api* _api = new gx_face_api(CONFIG_PATH);
        std::ofstream log_file(SEARCH_LOG, std::ios::out | std::ios::app);
        std::fstream path_file(SEARCH_TXT, std::ios::in);
        abi::string path, key;
        _api->user_load();
        printf("search 24hour testing...");
        // 持续执行 24 小时。
        auto start_time = std::chrono::high_resolution_clock::now();
        auto end_time   = start_time + std::chrono::hours(24);
        while (std::chrono::high_resolution_clock::now() < end_time) {

            // 重置文件指针到开头。
            path_file.clear();
            path_file.seekg(0, std::ios::beg);

            while (path_file >> path >> key) {

                // 文件未读完但超过了结束时间，也终止程序运行。
                if (std::chrono::high_resolution_clock::now() > end_time) {
                    break;
                }

                json data;
                // 记录当前系统时间。
                std::string currentTime = glasssix::getCurrentTime();
                data["date"]            = currentTime.c_str();
                data["predicted_key"]   = path + " " + key;
                gx_img_api img(SEARCH_SRC + path, IMG_2K);

                // 特征库能查到。
                if (_api->user_contains_key(key)) {
                    // 统计接口耗时。
                    auto start    = std::chrono::high_resolution_clock::now();
                    auto val      = _api->user_search(img, 1, 0.1);
                    auto end      = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                    data["cost"]  = duration.count();
                    // 有结果返回。
                    if (val.result.size()) {
                        data["similarity"] = val.result[0].similarity;
                        data["actual_key"] = val.result[0].data.key;
                        data["result"]     = "success";
                        log_file << data << std::endl;

                    } else {
                        data["result"] = "fail:no result!";
                        log_file << data << std::endl;
                    }

                } else {
                    data["result"] = "fail:not in database!";
                    log_file << data << std::endl;
                }

                // 线程睡眠 100 毫秒。
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }

        printf("search 24hour completed!");
        delete _api;
    }

} // namespace glasssix


int main(int argc, char** argv) {
    /* C++ 接口测试*/

    try {

        // test_add_face_all();
        // test_face_search();
        // test_face_liveness();
        // test_face_compare();

        // 稳定性测试。（人脸需要多线程调用）
        std::thread t[3];
        t[0] = std::thread(test_face_search_24hour);
        t[1] = std::thread(test_face_liveness_24hour);
        t[2] = std::thread(test_face_compare_24hour);
        t[0].join();
        t[1].join();
        t[2].join();

    } catch (const std::exception& ex) {
        printf("%s\n", ex.what());
    }
    std::getchar();
    return 0;
}
