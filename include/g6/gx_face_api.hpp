#pragma once
#include "gx_api.hpp"
#include "info_face.hpp"

namespace glasssix {

    class GX_API(GXOFFLINERECOGNITION) gx_face_api {
    public:
        gx_face_api();
        gx_face_api(const abi::string& config_path);
        ~gx_face_api();
        gx_face_api(gx_face_api&&) noexcept;
        gx_face_api& operator=(gx_face_api&&) noexcept;

        // 人脸检测
        abi::vector<face_info> detect(const gx_img_api& mat);
        // 人脸追踪
        abi::vector<face_trace_info> track(const gx_img_api& mat);
        // 清除人脸跟踪历史
        bool clear_track_history();
        // 人脸质量(模糊度)检测
        faces_blur face_blur(const gx_img_api& mat);
        // 人脸属性检测
        abi::vector <attributes> face_attributes(const gx_img_api& mat);
        // 配合活体检测
        face_info face_action_live(action_live_type action_type, bool& action_result, const gx_img_api& mat);
        // 静默活体检测
        faces_spoofing face_spoofing_live(const gx_img_api& mat);
        // 特征提取融合
        faces_feature face_feature(const gx_img_api& mat, bool is_clip);
        // 1:1特征值对比接口
        double feature_comparison(const gx_img_api& mat_A, const gx_img_api& mat_B);
        // 特征值库加载
        bool user_load();
        // 特征值库搜索
        faces_search_info user_search(const gx_img_api& mat, int top, float min_similarity);
        // 特征值库清空
        bool user_remove_all();
        // 特征值库批量删除
        abi::vector<face_user_result> user_remove_records(const abi::vector<abi::string>& keys);
        // 特征值库批量添加
        abi::vector<face_user_result> user_add_records(
            const abi::vector<abi::string>& keys, const abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo);
        // 特征值库批量添加
        abi::vector<face_user_result> user_add_records(
            abi::vector<abi::string>& keys, abi::vector<abi::vector<float>>& features);
        // 特征值库键值查询
        bool user_contains_key(const abi::string& key);
        // 特征值库记录总和
        std::uint64_t user_record_count();
        // 人脸识别流程融合
        faces_integration_search_info detect_integration(const gx_img_api& mat, int top, float min_similarity);
        // 多人脸搜索
        abi::vector<faces_search_one_info> detect_many_faces_integration(
            const gx_img_api& mat, bool is_living, float min_similarity);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
