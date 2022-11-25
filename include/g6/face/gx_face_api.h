#pragma once
#include <string>
#include <vector>

#include <g6/char8_t_remediation.hpp>
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>
#include <g6/face/struct_info.h>
#include <config.h>

#include <license.hpp>
#include <parser_c.hpp>
#include <opencv2/opencv.hpp>

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


    // ͼƬ��   ��·��  ��buff   
    // ���û����ð�װopencv   
    //  ����  ��ת  �ü�

    
class GX_API(GXOFFLINEFACERECOGNITION) gx_face_api {
    public:
        gx_face_api();
        ~gx_face_api();

        //// ��ȡ�豸ָ��
        // void get_device_id(std::string& device_id);
        //// ��ȡ�汾��
        // void sdk_version(std::string& version);
        //// sdk��ʼ��
        // int sdk_init(const char* model_path);
        // int log_type();
        // bool is_auth();

        //�������
        std::vector<face_box> gx_detect(const cv::Mat* mat);
        //����׷��
        std::vector<track_face_box> gx_track(const cv::Mat* mat);
        //�������������ʷ
        void gx_clear_track_history();
        //��������(ģ����)���
        std::vector<blur> gx_face_blur(const cv::Mat* mat);
        //��ϻ�����
        face_box gx_face_action_live(int action_type, int& action_result, const cv::Mat* mat);
        //��Ĭ������
        std::vector<spoofing> gx_face_spoofing_live(const cv::Mat* mat);
        //������ȡ�ں�
        std::vector<feature> gx_face_feature(const cv::Mat* mat);

        // ����ֵ�����
        int gx_user_load(bool is_mask);
        // ����ֵ������
        std::vector<face_info> gx_user_removeRecords(const cv::Mat* mat, int top, float min_similarity, bool is_mask);
        //����ֵ���������
        int gx_user_clear(bool is_mask);
        //����ֵ�����
        int gx_user_removeAll(bool is_mask);
        //����ֵ������ɾ��
        int gx_user_removeRecords(std::vector<std::string>& keys, bool is_mask);
        //����ֵ���������
        std::vector<bool> gx_user_addRecords(
            std::vector<std::string>& keys, std::vector<const cv::Mat*>& mat, bool is_mask);
        //����ֵ����������
        std::vector<bool> gx_user_updateRecords(
            std::vector<std::string>& keys, std::vector<const cv::Mat*>& mat, bool is_mask);

        //����ʶ�������ں�
        std::vector<face_info> gx_detect_integration(const cv::Mat* mat, int top, bool is_mask);
        // 1:1����ֵ�ԱȽӿ�
        double gx_feature_comparison(const cv::Mat* mat_A, const cv::Mat* mat_B);

    private:
        config *_config;
        std::string guid[6];    // guid_type  sum = 5 (longinus_guid romancia_guid damocles_guid selene_guid irisviel_guid irisviel_mask_guid)
        void* parser; 
        track_cache cache;
    };
} // namespace glasssix::face