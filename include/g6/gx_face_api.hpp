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

        // �������
        abi::vector<face_info> detect(const gx_img_api& mat);
        // ����׷��
        abi::vector<face_trace_info> track(const gx_img_api& mat);
        // �������������ʷ
        bool clear_track_history();
        // ��������(ģ����)���
        faces_blur face_blur(const gx_img_api& mat);
        // �������Լ��
        abi::vector <attributes> face_attributes(const gx_img_api& mat);
        // ��ϻ�����
        face_info face_action_live(action_live_type action_type, bool& action_result, const gx_img_api& mat);
        // ��Ĭ������
        faces_spoofing face_spoofing_live(const gx_img_api& mat);
        // ������ȡ�ں�
        faces_feature face_feature(const gx_img_api& mat, bool is_clip);
        // 1:1����ֵ�ԱȽӿ�
        double feature_comparison(const gx_img_api& mat_A, const gx_img_api& mat_B);
        // ����ֵ�����
        bool user_load();
        // ����ֵ������
        faces_search_info user_search(const gx_img_api& mat, int top, float min_similarity);
        // ����ֵ�����
        bool user_remove_all();
        // ����ֵ������ɾ��
        abi::vector<face_user_result> user_remove_records(const abi::vector<abi::string>& keys);
        // ����ֵ���������
        abi::vector<face_user_result> user_add_records(
            const abi::vector<abi::string>& keys, const abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo);
        // ����ֵ���������
        abi::vector<face_user_result> user_add_records(
            abi::vector<abi::string>& keys, abi::vector<abi::vector<float>>& features);
        // ����ֵ���ֵ��ѯ
        bool user_contains_key(const abi::string& key);
        // ����ֵ���¼�ܺ�
        std::uint64_t user_record_count();
        // ����ʶ�������ں�
        faces_integration_search_info detect_integration(const gx_img_api& mat, int top, float min_similarity);
        // ����������
        abi::vector<faces_search_one_info> detect_many_faces_integration(
            const gx_img_api& mat, bool is_living, float min_similarity);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };
} // namespace glasssix
