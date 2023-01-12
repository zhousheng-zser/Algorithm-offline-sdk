#pragma once

#include <vector>

#include <face_info.hpp>
#include <string_view>
typedef unsigned char uchar;

namespace glasssix::face {
    class GX_API(GXOFFLINEFACERECOGNITION) gx_img_api {
    public:
        gx_img_api(abi::string path);
        gx_img_api(std::vector<uchar>& buffer);
        ~gx_img_api();
        gx_img_api(gx_img_api&&) noexcept;
        gx_img_api& operator=(gx_img_api&&) noexcept;
        int get_rows();    //获取图片高
        int get_cols();    //获取图片
        uchar* get_data(); //获取图片data 
        size_t get_data_len();  //获取data长度
        abi::string get_type(); //获取图片类型
        bool rotate(int deg);   // 旋转图片
        abi::vector<uchar> cropped(int x1, int x2, int y1, int y2); //裁剪人脸

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
        bool gx_clear_track_history();
        //人脸质量(模糊度)检测
        faces_blur gx_face_blur(gx_img_api& mat);
        //配合活体检测
        face_info gx_face_action_live(int action_type, bool& action_result, gx_img_api& mat);
        //静默活体检测
        faces_spoofing gx_face_spoofing_live(gx_img_api& mat);
        //特征提取融合
        abi::vector<faces_feature> gx_face_feature(gx_img_api& mat, bool is_clip);
        // 1:1特征值对比接口
        double gx_feature_comparison(gx_img_api& mat_A, gx_img_api& mat_B);
        // 特征值库加载
        bool gx_user_load();
        // 特征值库搜索
        faces_search_info gx_user_search(gx_img_api& mat, int top, float min_similarity);
        //特征值库清空
        bool gx_user_remove_all();
        //特征值库批量删除
        abi::vector<face_user_result> gx_user_remove_records(abi::vector<abi::string>& keys);
        //特征值库批量添加
        abi::vector<face_user_result> gx_user_add_records(
            abi::vector<abi::string>& keys, abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo);
        //特征值库批量添加
        abi::vector<face_user_result> gx_user_add_records(
            abi::vector<abi::string>& keys, abi::vector<abi::vector<float>>& features);
        //特征值库键值查询
        bool gx_user_contains_key(abi::string& key);
        //特征值库记录总和
        std::uint64_t gx_user_record_count();

        //人脸识别流程融合
        faces_integration_search_info gx_detect_integration(gx_img_api& mat, int top, float min_similarity);

        bool set_config(std::string_view name, std::string_view key, int val);
        bool set_config(std::string_view name, std::string_view key, float val);
        bool set_config(std::string_view name, std::string_view key, abi::string val);
        bool set_config(std::string_view name, std::string_view key, bool val);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
        // track_cache cache;
    };
} // namespace glasssix::face
