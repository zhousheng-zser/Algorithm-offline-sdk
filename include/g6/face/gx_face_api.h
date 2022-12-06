#pragma once
#include <string>
#include <vector>

#include <g6/char8_t_remediation.hpp>
#include <g6/format_remediation.hpp>
#include <../src/nessus/protocols/face_info.hpp>
#include <g6/logger.hpp>

#include <config.h>
#include <license.hpp>
#include <parser_c.hpp>
typedef unsigned char uchar;

//#include <opencv2/opencv.hpp>
namespace glasssix::face {

    // 图片类   传路径  传buff
    // 让用户不用安装opencv
    class GX_API(GXOFFLINEFACERECOGNITION) gx_img_api {
    public:
        gx_img_api(abi::string path);
        gx_img_api(std::vector<uchar> &buffer);
        ~gx_img_api();
        gx_img_api(gx_img_api&&) noexcept;
        gx_img_api& operator=(gx_img_api&&) noexcept;
        int get_rows();
        int get_cols();
        uchar* get_data();
        size_t get_data_len();
        abi::string get_type();

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };


    class GX_API(GXOFFLINEFACERECOGNITION) gx_face_api {
    public:
        gx_face_api();
        ~gx_face_api();
        gx_face_api(gx_face_api&&) noexcept;
        gx_face_api& operator=(gx_face_api&&) noexcept;

        //人脸检测
        abi::vector<face_info> gx_detect(gx_img_api& mat);
        //人脸追踪
        abi::vector<face_trace_info> gx_track(gx_img_api& mat);
        //清除人脸跟踪历史
        void gx_clear_track_history();
        //人脸质量(模糊度)检测
        faces_blur gx_face_blur(gx_img_api& mat);
        //配合活体检测
        face_info gx_face_action_live(int action_type, bool& action_result, gx_img_api& mat);
        //静默活体检测
        faces_spoofing gx_face_spoofing_live(gx_img_api& mat);
        //特征提取融合
        faces_feature gx_face_feature(gx_img_api& mat);        
        // 1:1特征值对比接口
        double gx_feature_comparison(gx_img_api& mat_A, gx_img_api& mat_B);
        // 特征值库加载
        int gx_user_load(bool is_mask = false);
        // 特征值库搜索
        faces_search_info gx_user_search(
            gx_img_api& mat, int top = 1, float min_similarity = 0.4, bool is_mask = false);
        //特征值库清除缓存
        int gx_user_clear(bool is_mask = false);
        //特征值库清空
        int gx_user_remove_all(bool is_mask = false);
        //特征值库批量删除
        int gx_user_remove_records(abi::vector<abi::string>& keys, bool is_mask = false);
        //特征值库批量添加
        abi::vector<bool> gx_user_add_records(
            abi::vector<abi::string>& keys, std::vector<gx_img_api>& mat, bool is_mask = false);
        //特征值库批量更新
        abi::vector<bool> gx_user_update_records(
            abi::vector<abi::string>& keys, std::vector<gx_img_api>& mat, bool is_mask = false);

        //人脸识别流程融合
        faces_search_info gx_detect_integration(
            gx_img_api& mat, int top = 1, float min_similarity = 0.4, bool is_mask = false);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
        //track_cache cache;
    };
} // namespace glasssix::face
