#pragma once
#include <string>
#include <vector>

#include <g6/char8_t_remediation.hpp>
#include <g6/face/struct_info.h>
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>

#include <config.h>
#include <license.hpp>
#include <opencv2/opencv.hpp>
#include <parser_c.hpp>

namespace glasssix::face {
    /*
    struct baz {
        GX_BEGIN_FIELDS(baz);
        GX_FIELD(int, a);
        GX_FIELD(std::string, b);
        GX_FIELD(std::vector<int>, c);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE_DEFAULT;
    };

    void foo() {
        constexpr auto xstr = U8("123");
        const char* x= xstr;

        auto str= glasssix::format("Hello {}{}", 123, xstr);
        auto&& logger = glasssix::get_screen_logger();

        logger.line(U8("Hello"));
        logger.json(glasssix::json(baz{.a{123}, .b{U8("hello")}, .c{1, 2, 3, 4, 5}}));
        glasssix::json j;

        auto value = j.get<baz>();
    }
    GX_API(GXOFFLINEFACERECOGNITION) void gx_free_tomcat(void* ptr) {
        free(ptr);
    }
    */


    // 图片类   传路径  传buff
    // 让用户不用安装opencv
    //  缩放  旋转  裁剪


    class GX_API(GXOFFLINEFACERECOGNITION) gx_face_api {
    public:
        gx_face_api();
        ~gx_face_api();

        //// 获取设备指纹
        // void get_device_id(std::string& device_id);
        //// 获取版本号
        // void sdk_version(std::string& version);
        //// sdk初始化
        // int sdk_init(const char* model_path);
        // int log_type();
        // bool is_auth();

        //人脸检测
        std::vector<face_box> gx_detect(const cv::Mat* mat);
        //人脸追踪
        std::vector<track_face_box> gx_track(const cv::Mat* mat);
        //清除人脸跟踪历史
        void gx_clear_track_history();
        //人脸质量(模糊度)检测
        std::vector<blur> gx_face_blur(const cv::Mat* mat);
        //配合活体检测
        face_box gx_face_action_live(int action_type, int& action_result, const cv::Mat* mat);
        //静默活体检测
        std::vector<spoofing> gx_face_spoofing_live(const cv::Mat* mat);
        //特征提取融合
        std::vector<face_feature> gx_face_feature(const cv::Mat* mat);

        // 特征值库加载
        int gx_user_load(bool is_mask = false);
        // 特征值库搜索
        std::vector<face_info> gx_user_search(
            const cv::Mat* mat, int top = 1, float min_similarity = 0.4, bool is_mask = false);
        //特征值库清除缓存
        int gx_user_clear(bool is_mask = false);
        //特征值库清空
        int gx_user_remove_all(bool is_mask = false);
        //特征值库批量删除
        int gx_user_remove_records(std::vector<std::string>& keys, bool is_mask = false);
        //特征值库批量添加
        std::vector<bool> gx_user_add_records(
            std::vector<std::string>& keys, std::vector<cv::Mat>& mat, bool is_mask = false);
        //特征值库批量更新
        std::vector<bool> gx_user_update_records(
            std::vector<std::string>& keys, std::vector<cv::Mat>& mat, bool is_mask = false);

        //人脸识别流程融合
        std::vector<face_info> gx_detect_integration(
            const cv::Mat* mat, int top = 1, float min_similarity = 0.4, bool is_mask = false);
        // 1:1特征值对比接口
        double gx_feature_comparison(const cv::Mat* mat_A, const cv::Mat* mat_B);

    private:
        config* _config;
        std::string guid[6]; // guid_type  sum = 6 (longinus_guid romancia_guid damocles_guid selene_guid irisviel_guid
                             // irisviel_mask_guid)
        void* parser;
        track_cache cache;
        face_box gx_get_max_face(const std::vector<face_box>& faces);
    };
} // namespace glasssix::face