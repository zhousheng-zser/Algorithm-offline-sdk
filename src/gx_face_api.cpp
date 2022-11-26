#include "gx_face_api.h"

#include <parser_c.hpp>

namespace glasssix::face {

    inline float DotProductAVX256(const std::vector<float>& emb_1, const std::vector<float>& emb_2) {
        const static size_t kBlockWidth = 8; // compute 8 floats in one loop
        const float* a                  = emb_1.data();
        const float* b                  = emb_2.data();
        int k                           = std::min(emb_1.size(), emb_2.size()) / kBlockWidth;
        __m256 ans;
        ans          = _mm256_setzero_ps();
        float tmp[8] = {0};
        for (int i = 0; i < k; i++) {
            __m256 ai = _mm256_loadu_ps(a + i * kBlockWidth);
            __m256 bi = _mm256_loadu_ps(b + i * kBlockWidth);
            ans       = _mm256_add_ps(ans, _mm256_mul_ps(ai, bi));
        }
        _mm256_store_ps(tmp, ans);
        return tmp[0] + tmp[1] + tmp[2] + tmp[3] + tmp[4] + tmp[5] + tmp[6] + tmp[7];
    }

    inline float Cosine_distance_AVX256(std::vector<float>& x, std::vector<float>& y) {
        float sum, a, b;
        a = DotProductAVX256(x, x);
        b = DotProductAVX256(y, y);
        if (a == 0 || b == 0)
            return 0;
        sum       = DotProductAVX256(x, y);
        float ans = sum / (sqrt(a) * sqrt(b));
        ans       = std::min(1.0f, abs(ans));
        return ans;
    }

    gx_face_api::gx_face_api() {
        _config = new config();
        gx_clear_track_history();

        // Temporary manual input
        const char config_file_path[] =
            "D:/Code/Glasssix_CV_SDK_2.9.21.20220811_beta/configure_file/plugin_configure.json";
        parser           = parser_new_instance();
        char* result_str = parser_init_plugin(parser, config_file_path, "");
        json jsonobj_result, jsonobj_param;
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            printf("Successfully init sdk.\n");
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["device"]           = _config->_detect_config.device;
        jsonobj_param["models_directory"] = _config->_detect_config.models_directory;
        result_str     = parser_parse(parser, "Longinus.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::longinus_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["device"]           = _config->_blur_config.device;
        jsonobj_param["models_directory"] = _config->_blur_config.models_directory;
        result_str     = parser_parse(parser, "Romancia.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::romancia_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["device"]           = _config->_action_live_config.device;
        jsonobj_param["models_directory"] = _config->_action_live_config.models_directory;
        jsonobj_param["use_int8"]         = _config->_action_live_config.use_int8;
        result_str     = parser_parse(parser, "Damocles.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::damocles_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["device"]           = _config->_feature_config.device;
        jsonobj_param["models_directory"] = _config->_feature_config.models_directory;
        jsonobj_param["use_int8"]         = _config->_feature_config.use_int8;
        jsonobj_param["model_type"]       = _config->_feature_config.model_type;
        result_str     = parser_parse(parser, "Selene.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::selene_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["dimension"]         = _config->_face_user_config.dimension;
        jsonobj_param["working_directory"] = _config->_face_user_config.working_directory;
        result_str     = parser_parse(parser, "Irisviel.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::irisviel_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);

        jsonobj_param.clear();
        jsonobj_result.clear();
        jsonobj_param["dimension"]         = _config->_face_user_config.dimension;
        jsonobj_param["working_directory"] = _config->_face_user_config.working_directory_mask;
        result_str     = parser_parse(parser, "Irisviel.new", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0)
            guid[guid_type::irisviel_mask_guid] = jsonobj_result["instance_guid"].get<abi::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
    }
    gx_face_api::~gx_face_api() {
        char* result_str = nullptr;
        json jsonobj_param;
        jsonobj_param.clear();

        jsonobj_param["instance_guid"] = guid[guid_type::longinus_guid];
        result_str = parser_parse(parser, "Longinus.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        jsonobj_param["instance_guid"] = guid[guid_type::romancia_guid];
        result_str = parser_parse(parser, "Romancia.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        jsonobj_param["instance_guid"] = guid[guid_type::damocles_guid];
        result_str = parser_parse(parser, "Damocles.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        jsonobj_param["instance_guid"] = guid[guid_type::selene_guid];
        result_str = parser_parse(parser, "Selene.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        result_str = parser_parse(parser, "Irisviel.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        result_str = parser_parse(parser, "Irisviel.delete", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        parser_free(result_str);

        result_str = nullptr;
    }

    //// 获取设备指纹
    // void get_device_id(abi::string& device_id);
    //// 获取版本号
    // void sdk_version(abi::string& version);
    //// sdk初始化
    // int sdk_init(const char* model_path);
    // int log_type();
    // bool is_auth();

    //人脸检测
    std::vector<face_box> gx_face_api::gx_detect(const cv::Mat* mat) {
        std::vector<face_box> ans;

        face_box temp{};
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"]  = guid[guid_type::longinus_guid];
        jsonobj_param["format"]         = _config->_detect_config.format;
        jsonobj_param["height"]         = mat->rows;
        jsonobj_param["width"]          = mat->cols;
        jsonobj_param["min_size"]       = _config->_detect_config.min_size;
        jsonobj_param["threshold"]      = _config->_detect_config.threshold;
        jsonobj_param["do_attributing"] = _config->_detect_config.do_attributing;
        char* result_str                = parser_parse(parser, "Longinus.detect", jsonobj_param.dump().c_str(),
                           reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);
        jsonobj_result                  = json ::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0) {
            int list_size = jsonobj_result["facerectwithfaceinfo_list"].size();
            for (int i = 0; i < list_size; i++) {
                jsonobj_face = jsonobj_result["facerectwithfaceinfo_list"][i];
                jsonobj_face.get_to(temp);
                ans.emplace_back(temp);
            }
        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
        result_str = nullptr;


        return ans;
    }
    //人脸追踪
    std::vector<track_face_box> gx_face_api::gx_track(const cv::Mat* mat) {
        std::vector<track_face_box> ans;

        if (cache.index % (_config->_track_config.detect_intv_before_track) == 0) {
            std::vector<face_box> faces = gx_detect(mat);
            for (int i = 0; i < faces.size(); i++) /// TODO    可以优化加一个判断   重合超过90%的人脸框不入队
                cache.track_history[faces[i].x * 10000 + faces[i].y] = faces[i];
        }

        std::unordered_map<int, face_box>::iterator it;
        std::unordered_map<int, face_box> temp_faces;
        for (it = cache.track_history.begin(); it != cache.track_history.end();) {
            json jsonobj_param, jsonobj_result;
            jsonobj_param.clear();
            jsonobj_param["instance_guid"]  = guid[guid_type::longinus_guid];
            jsonobj_param["format"]         = _config->_detect_config.format;
            jsonobj_param["height"]         = mat->rows;
            jsonobj_param["width"]          = mat->cols;
            jsonobj_param["face"]["x"]      = (it->second).x;
            jsonobj_param["face"]["y"]      = (it->second).y;
            jsonobj_param["face"]["width"]  = (it->second).width;
            jsonobj_param["face"]["height"] = (it->second).height;
            char* result_str                = parser_parse(parser, "Longinus.trace", jsonobj_param.dump().c_str(),
                               reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);
            jsonobj_result                  = json ::parse(result_str);

            if (jsonobj_result["status"]["code"].get<int>() == 0
                && jsonobj_result["trace_success"].get<bool>() == true) {
                //更新追踪坐标
                jsonobj_result["facerectwithfaceinfo"].get_to(it->second);
                track_face_box temp;
                temp._face_box                                      = it->second;
                temp.trace_success                                  = true;
                temp_faces[(it->second).x * 10000 + (it->second).y] = it->second;
                ans.emplace_back(temp);
                cache.track_history.erase(it++);

            } else if (jsonobj_result["trace_success"].get<bool>() == false) {
                ans.emplace_back(track_face_box{it->second, false});
                cache.track_history.erase(it++);
            } else {
                printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
                cache.track_history.erase(it++);
            }
        }
        cache.track_history.clear();
        cache.track_history = temp_faces;

        cache.index++;
        return ans;
    }
    //清除人脸跟踪历史
    void gx_face_api::gx_clear_track_history() {
        cache.index = 0;
        cache.track_history.clear();
        return;
    }
    //人脸质量(模糊度)检测
    std::vector<blur> gx_face_api::gx_face_blur(const cv::Mat* mat) {
        std::vector<blur> ans;
        std::vector<face_box> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;

        json jsonobj_param, jsonobj_result;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"] = guid[guid_type::romancia_guid];
        jsonobj_param["format"]        = _config->_blur_config.format;
        jsonobj_param["height"]        = mat->rows;
        jsonobj_param["width"]         = mat->cols;
        for (int i = 0; i < faces.size(); i++) {
            jsonobj_param["facerect_list"][i]["x"]      = faces[i].x;
            jsonobj_param["facerect_list"][i]["y"]      = faces[i].y;
            jsonobj_param["facerect_list"][i]["width"]  = faces[i].width;
            jsonobj_param["facerect_list"][i]["height"] = faces[i].height;
        }
        char* result_str = parser_parse(parser, "Romancia.blur_detect", jsonobj_param.dump().c_str(),
            reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);
        jsonobj_result   = json ::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0) {
            int list_size = jsonobj_result["clarity"].size();
            for (int i = 0; i < list_size; i++)
                ans.emplace_back(blur{faces[i], jsonobj_result["clarity"][i].get<float>()});

        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
        result_str = nullptr;

        return ans;
    }

    //配合活体检测
    face_box gx_face_api::gx_face_action_live(int action_type, int& action_result, const cv::Mat* mat) {
        face_box ans;
        std::vector<face_box> faces = gx_detect(mat);
        action_result               = 0;
        if (faces.size() == 0)
            return ans;
        ans = faces[0];

        json jsonobj_param, jsonobj_result;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"]      = guid[guid_type::damocles_guid];
        jsonobj_param["action_cmd"]         = action_type;
        jsonobj_param["format"]             = _config->_action_live_config.format;
        jsonobj_param["height"]             = mat->rows;
        jsonobj_param["width"]              = mat->cols;
        jsonobj_param["facerect"]["x"]      = ans.x;
        jsonobj_param["facerect"]["y"]      = ans.y;
        jsonobj_param["facerect"]["width"]  = ans.width;
        jsonobj_param["facerect"]["height"] = ans.height;

        char* result_str = parser_parse(parser, "Damocles.presentation_attack_detect", jsonobj_param.dump().c_str(),
            reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);

        jsonobj_result = json ::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0) {
            action_result = (int) jsonobj_result["presentation_attack_result"].get<bool>();
        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
        result_str = nullptr;


        return ans;
    }
    //静默活体检测
    std::vector<spoofing> gx_face_api::gx_face_spoofing_live(const cv::Mat* mat) {
        std::vector<spoofing> ans;
        std::vector<face_box> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;
        json jsonobj_param, jsonobj_result;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"] = guid[guid_type::damocles_guid];
        jsonobj_param["format"]        = _config->_action_live_config.format;
        jsonobj_param["height"]        = mat->rows;
        jsonobj_param["width"]         = mat->cols;
        for (int i = 0; i < faces.size(); i++) {
            jsonobj_param["facerect_list"][i]["x"]      = faces[i].x;
            jsonobj_param["facerect_list"][i]["y"]      = faces[i].y;
            jsonobj_param["facerect_list"][i]["width"]  = faces[i].width;
            jsonobj_param["facerect_list"][i]["height"] = faces[i].height;
            ans.emplace_back(spoofing{faces[i]});
        }
        char* result_str = parser_parse(parser, "Damocles.spoofing_detect", jsonobj_param.dump().c_str(),
            reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);

        jsonobj_result = json ::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0) {
            for (int i = 0; i < jsonobj_result["spoofing_result"].size() && i < faces.size(); i++) {
                jsonobj_result["spoofing_result"][i]["prob"].get_to(ans[i].prob);
            }
        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
        result_str = nullptr;


        return ans;
    }

    //特征提取融合
    std::vector<face_feature> gx_face_api::gx_face_feature(const cv::Mat* mat) {
        std::vector<face_feature> ans;
        std::vector<face_box> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;

        json jsonobj_param, jsonobj_result;
        jsonobj_param.clear();
        jsonobj_param["romancia_instance_guid"] = guid[guid_type::romancia_guid];
        jsonobj_param["selene_instance_guid"]   = guid[guid_type::selene_guid];
        jsonobj_param["format"]                 = _config->_feature_config.format;
        jsonobj_param["height"]                 = mat->rows;
        jsonobj_param["width"]                  = mat->cols;
        for (int i = 0; i < faces.size(); i++) {
            jsonobj_param["facerectwithfaceinfo_list"][i] = faces[i];
            ans.emplace_back(face_feature{faces[i]});
        }
        char* result_str =
            parser_parse(parser, "Fusion.Romancia.alignFace.Selene.forward", jsonobj_param.dump().c_str(),
                reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);

        jsonobj_result = json ::parse(result_str);
        if (jsonobj_result["status"]["code"].get<int>() == 0) {
            for (int i = 0; i < jsonobj_result["features"].size() && i < faces.size(); i++) {
                jsonobj_result["features"][i]["feature"].get_to(ans[i].feature);
            }
        } else {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            exit(-1);
        }
        parser_free(result_str);
        result_str = nullptr;
        return ans;
    }

    face_box gx_face_api::gx_get_max_face(const std::vector<face_box>& faces) {
        face_box ans;
        if (faces.size() == 0)
            return ans;

        int id = 0;
        for (int i = 1; i < faces.size(); i++) {
            if (1llu * faces[id].width * faces[id].height < 1llu * faces[i].width * faces[i].height)
                id = i;
        }
        ans = faces[id];
        return ans;
    }


    // 特征值库加载
    int gx_face_api::gx_user_load(bool is_mask) {

        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        char* result_str =
            parser_parse(parser, "Irisviel.load_databases", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);
        parser_free(result_str);
        result_str = nullptr;
        return jsonobj_result["status"]["code"].get<int>();
    }
    // 特征值库搜索
    std::vector<face_info> gx_face_api::gx_user_search(
        const cv::Mat* mat, int top, float min_similarity, bool is_mask) {
        std::vector<face_info> ans;
        std::vector<face_feature> faces = gx_face_feature(mat);
        if (faces.size() == 0)
            return ans;
        face_feature max_face = faces[0];

        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        jsonobj_param["top"]            = top;
        jsonobj_param["min_similarity"] = min_similarity;
        jsonobj_param["feature"]        = max_face.feature;


        char* result_str =
            parser_parse(parser, "Irisviel.search", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);
        parser_free(result_str);
        result_str = nullptr;
        int len    = jsonobj_result["result"].size();
        for (int i = 0; i < len; i++) {
            face_info temp;
            jsonobj_result["result"][i].get_to(temp);
            ans.emplace_back(temp);
        }

        return ans;
    }
    //特征值库清除缓存
    int gx_face_api::gx_user_clear(bool is_mask) {
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        char* result_str = parser_parse(parser, "Irisviel.clear", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result   = json ::parse(result_str);
        parser_free(result_str);
        result_str = nullptr;
        return jsonobj_result["status"]["code"].get<int>();
    }
    //特征值库清空
    int gx_face_api::gx_user_remove_all(bool is_mask) {
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        char* result_str =
            parser_parse(parser, "Irisviel.remove_all", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);
        parser_free(result_str);
        result_str = nullptr;
        return jsonobj_result["status"]["code"].get<int>();
    }
    //特征值库批量删除
    int gx_face_api::gx_user_remove_records(std::vector<abi::string>& keys, bool is_mask) {
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        for (int i = 0; i < keys.size(); i++)
            jsonobj_param["keys"][i] = keys[i];
        char* result_str =
            parser_parse(parser, "Irisviel.remove_records", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);
        parser_free(result_str);
        result_str = nullptr;
        return jsonobj_result["status"]["code"].get<int>();
    }
    //特征值库批量添加
    std::vector<bool> gx_face_api::gx_user_add_records(
        std::vector<abi::string>& keys, std::vector<cv::Mat>& mat, bool is_mask) {
        std::vector<bool> ans(mat.size(), false);
        std::vector<face_feature> faces;
        if (keys.size() != mat.size())
            return ans;

        for (int i = 0; i < mat.size(); i++) {
            std::vector<face_feature> temp = gx_face_feature(&mat[i]);
            if (temp.size() == 0 || keys[i] == "") {
                faces.emplace_back(face_feature{});
                ans[i] = false;
            } else {
                faces.emplace_back(temp[0]);
                ans[i] = true;
            }
        }
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        for (int i = 0, id = 0; i < keys.size(); i++) {

            if (ans[i]) {
                jsonobj_param["data"][id]["feature"] = faces[i].feature;
                jsonobj_param["data"][id]["key"]     = keys[i];
                id++;
            }
        }
        char* result_str =
            parser_parse(parser, "Irisviel.add_records", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);

        if (jsonobj_result["status"]["code"].get<int>() != 0) {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            ans.clear();
            ans = std::vector<bool>(mat.size(), false);
        }

        parser_free(result_str);
        result_str = nullptr;
        return ans;
    }
    //特征值库批量更新
    std::vector<bool> gx_face_api::gx_user_update_records(
        std::vector<abi::string>& keys, std::vector<cv::Mat>& mat, bool is_mask) {
        std::vector<bool> ans(mat.size(), false);
        std::vector<face_feature> faces;
        if (keys.size() != mat.size())
            return ans;
        for (int i = 0; i < mat.size(); i++) {
            face_feature temp = gx_face_feature(&mat[i])[0];
            if (temp.feature.size() == 0 || keys[i] == "")
                ans[i] = false;
            else
                ans[i] = true;
            // faces.emplace_back(gx_face_feature(&mat[i]));
            faces.emplace_back(temp);
        }
        json jsonobj_param, jsonobj_result, jsonobj_face;
        jsonobj_param.clear();
        if (is_mask == false)
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_guid];
        else
            jsonobj_param["instance_guid"] = guid[guid_type::irisviel_mask_guid];
        for (int i = 0, id = 0; i < keys.size(); i++) {

            if (ans[i]) {
                jsonobj_param["data"][id]["feature"] = faces[i].feature;
                jsonobj_param["data"][id]["key"]     = keys[i];
                id++;
            }
        }
        char* result_str =
            parser_parse(parser, "Irisviel.update_records", jsonobj_param.dump().c_str(), nullptr, 0, nullptr, 0);
        jsonobj_result = json ::parse(result_str);

        if (jsonobj_result["status"]["code"].get<int>() != 0) {
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<abi::string>().c_str());
            ans.clear();
            ans = std::vector<bool>(mat.size(), false);
        }

        parser_free(result_str);
        result_str = nullptr;
        return ans;
    }

    //人脸识别流程融合
    std::vector<face_info> gx_face_api::gx_detect_integration(
        const cv::Mat* mat, int top, float min_similarity, bool is_mask) {
        std::vector<face_info> ans;
        std::vector<spoofing> faces = gx_face_spoofing_live(mat);
        if (faces.size() == 0) {
            printf("no face!\n");
            return ans;
        } else if (faces[0].prob[1] < 0.5) {
            printf("prob < 0.5 !\n");
            return ans;
        }
        gx_user_load(is_mask);
        ans = gx_user_search(mat, top, min_similarity, is_mask);
        return ans;
    }

    // 1:1特征值对比接口
    double gx_face_api::gx_feature_comparison(const cv::Mat* mat_A, const cv::Mat* mat_B) {
        double ans                        = 0;
        std::vector<face_feature> faces_A = gx_face_feature(mat_A);
        std::vector<face_feature> faces_B = gx_face_feature(mat_B);
        if (faces_A.size() == 0 || faces_B.size() == 0)
            return 0;

        std::vector<float> x = faces_A[0].feature;
        std::vector<float> y = faces_B[0].feature;

        if (x.size() == 0 || y.size() == 0 || x.size() != y.size())
            return 0;
        ans = Cosine_distance_AVX256(x, y);
        return ans;
    }
} // namespace glasssix::face