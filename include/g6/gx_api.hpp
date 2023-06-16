#pragma once
#include "info.hpp"

#include <span>
#include <string_view>
#include <vector>
typedef unsigned char uchar;
const int IMG_2K               = 2048 * 1080;
const int IMG_4K               = 3840 * 2160;
const int IMG_Full_Aperture_4K = 4096 * 3112;

namespace glasssix {
    class GX_API(GXOFFLINERECOGNITION) gx_img_api {
    public:
        gx_img_api(abi::string path, int limit);
        gx_img_api(std::span<const uchar> bgr_data, int rows, int cols, int limit);
        gx_img_api(std::vector<uchar>& buffer, int limit);
        ~gx_img_api();
        gx_img_api(gx_img_api&&) noexcept;
        gx_img_api& operator=(gx_img_api&&) noexcept;
        int get_rows(); // 获取图片高
        int get_cols(); // 获取图片
        uchar* get_data(); // 获取图片data
        size_t get_data_len(); // 获取data长度
        abi::string get_type(); // 获取图片类型
        bool rotate(int deg); // 旋转图片
        abi::vector<uchar> cropped(int x1, int x2, int y1, int y2); // 裁剪人脸

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };


    class GX_API(GXOFFLINERECOGNITION) gx_api {
    public:
        gx_api();
        gx_api(const abi::string& config_path);
        ~gx_api();
        gx_api(gx_api&&) noexcept;
        gx_api& operator=(gx_api&&) noexcept;

        // 人脸检测
        abi::vector<face_info> detect(gx_img_api& mat);
        // 人脸追踪
        abi::vector<face_trace_info> track(gx_img_api& mat);
        // 清除人脸跟踪历史
        bool clear_track_history();
        // 人脸质量(模糊度)检测
        faces_blur face_blur(gx_img_api& mat);
        // 配合活体检测
        face_info face_action_live(action_live_type action_type, bool& action_result, gx_img_api& mat);
        // 静默活体检测
        faces_spoofing face_spoofing_live(gx_img_api& mat);
        // 特征提取融合
        faces_feature face_feature(gx_img_api& mat, bool is_clip);
        // 1:1特征值对比接口
        double feature_comparison(gx_img_api& mat_A, gx_img_api& mat_B);
        // 特征值库加载
        bool user_load();
        // 特征值库搜索
        faces_search_info user_search(gx_img_api& mat, int top, float min_similarity);
        // 特征值库清空
        bool user_remove_all();
        // 特征值库批量删除
        abi::vector<face_user_result> user_remove_records(abi::vector<abi::string>& keys);
        // 特征值库批量添加
        abi::vector<face_user_result> user_add_records(
            abi::vector<abi::string>& keys, abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo);
        // 特征值库批量添加
        abi::vector<face_user_result> user_add_records(
            abi::vector<abi::string>& keys, abi::vector<abi::vector<float>>& features);
        // 特征值库键值查询
        bool user_contains_key(abi::string& key);
        // 特征值库记录总和
        std::uint64_t user_record_count();
        // 人脸识别流程融合
        faces_integration_search_info detect_integration(gx_img_api& mat, int top, float min_similarity);
        // 多人脸搜索
        abi::vector<faces_search_one_info> detect_many_faces_integration(
            gx_img_api& mat, bool is_living, float min_similarity);
        //  安全生产 反光衣检测
        abi::vector<std::optional<abi::vector<clothes_info>>> safe_production_refvest(
            gx_img_api& mat, const abi::vector<detecte_roi>& roi_list);
        //  安全生产 烟雾火焰检测
        abi::vector<flame_info> safe_production_flame(gx_img_api& mat, const abi::vector<detecte_roi>& roi_list);
        //  安全生产 安全帽检测
        abi::vector<helmet_info> safe_production_helmet(gx_img_api& mat, const abi::vector<detecte_roi>& roi_list);
        /*
        bool set_config(std::string_view name, std::string_view key, int val);
        bool set_config(std::string_view name, std::string_view key, float val);
        bool set_config(std::string_view name, std::string_view key, abi::string val);
        bool set_config(std::string_view name, std::string_view key, bool val);
        */
    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
