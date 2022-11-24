#include <g6/face/gx_face_api.h>


namespace glasssix::face {
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
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::longinus_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::romancia_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::damocles_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::selene_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::irisviel_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
            guid[guid_type::irisviel_mask_guid] = jsonobj_result["instance_guid"].get<std::string>();
        else {
            printf("Error info : %s \n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
    // void get_device_id(std::string& device_id);
    //// 获取版本号
    // void sdk_version(std::string& version);
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
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
                printf("Error info : % s\n", jsonobj_result["status"]["message"].get<std::string>().c_str());
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
            printf("Error info : % s\n", jsonobj_result["status"]["message"].get<std::string>().c_str());
            getchar();
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
        for (int i = 1; i < faces.size(); i++) {
            if (1llu * ans.height * ans.width < 1llu * faces[i].width * faces[i].height)
                ans = faces[i];
        }

        json jsonobj_param,jsonobj_result;
        jsonobj_param.clear();
        jsonobj_param["instance_guid"]           = guid[guid_type::damocles_guid];
        jsonobj_param["action_cmd"]              = action_type;
        jsonobj_param["format"]                  = _config->_action_live_config.format;
        jsonobj_param["height"]                  = mat->rows;
        jsonobj_param["width"]                   = mat->cols;
        jsonobj_param["facerect"]["x"]      = ans.x;
        jsonobj_param["facerect"]["y"]      = ans.y;
        jsonobj_param["facerect"]["width"]  = ans.width;
        jsonobj_param["facerect"]["height"] = ans.height;

    char* result_str = parser_parse(parser, "Damocles.presentation_attack_detect", jsonobj_param.dump().c_str(),
        reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);

    jsonobj_result = json ::parse(result_str);
    if (jsonobj_result["status"]["code"].get<int>() == 0) {
        action_result = (int) jsonobj_result["presentation_attack_result"].get<bool>();
    } 
    else {
        printf("Error info : % s\n", jsonobj_result["status"]["message"].get<std::string>().c_str());
        getchar();
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
    jsonobj_param["instance_guid"]      = guid[guid_type::damocles_guid];
    jsonobj_param["format"]             = _config->_action_live_config.format;
    jsonobj_param["height"]             = mat->rows;
    jsonobj_param["width"]              = mat->cols;
    for (int i=0;i<faces.size() ;i++) {
    jsonobj_param["facerect_list"][i]["x"]      = faces[i].x;
    jsonobj_param["facerect_list"][i]["y"]      = faces[i].y;
    jsonobj_param["facerect_list"][i]["width"]  = faces[i].width;
    jsonobj_param["facerect_list"][i]["height"] = faces[i].height;
    spoofing temp;
    temp._face_box = faces[i];
    ans.emplace_back(temp);
    }
    char* result_str = parser_parse(parser, "Damocles.spoofing_detect", jsonobj_param.dump().c_str(),
        reinterpret_cast<char*>(mat->data), 1llu * mat->channels() * mat->cols * mat->rows, nullptr, 0);

    jsonobj_result = json ::parse(result_str);
    if (jsonobj_result["status"]["code"].get<int>() == 0) {
        for (int i = 0; i < jsonobj_result["spoofing_result"].size() && i <faces.size(); i++) {
            jsonobj_result["spoofing_result"][i]["prob"].get_to(ans[i].prob);
        }
    } else {
        printf("Error info : % s\n", jsonobj_result["status"]["message"].get<std::string>().c_str());
        getchar();
        exit(-1);
    }
    parser_free(result_str);
    result_str = nullptr;


    return ans;
}
//特征提取融合
std::vector<feature> gx_face_api::gx_face_feature(const cv::Mat* mat) {
    std::vector<feature> ans;
    return ans;
}

// 特征值库加载
int gx_face_api::gx_user_load(bool is_mask = false) {
    return 1;
}
// 特征值库搜索
std::vector<face_info> gx_face_api::gx_user_removeRecords(
    const cv::Mat* mat, int top = 1, float min_similarity = 0.6, bool is_mask = false) {
    std::vector<face_info> ans;
    return ans;
}
//特征值库清除缓存
int gx_face_api::gx_user_clear(bool is_mask = false) {
    return 2;
}
//特征值库清空
int gx_face_api::gx_user_removeAll(bool is_mask = false) {
    return 3;
}
//特征值库批量删除
int gx_face_api::gx_user_removeRecords(std::vector<std::string>& keys, bool is_mask = false) {
    return 4;
}
//特征值库批量添加
std::vector<bool> gx_face_api::gx_user_addRecords(
    std::vector<std::string>& keys, std::vector<const cv::Mat*>& mat, bool is_mask = false) {
    std::vector<bool> ans;
    return ans;
}
//特征值库批量更新
std::vector<bool> gx_face_api::gx_user_updateRecords(
    std::vector<std::string>& keys, std::vector<const cv::Mat*>& mat, bool is_mask = false) {
    std::vector<bool> ans;
    return ans;
}

//人脸识别流程融合
std::vector<face_info> gx_face_api::gx_detect_integration(const cv::Mat* mat, int top = 1, bool is_mask = false) {

    std::vector<face_info> ans;
    return ans;
}
// 1:1特征值对比接口
double gx_face_api::gx_feature_comparison(const cv::Mat* mat_A, const cv::Mat* mat_B) {
    return 5;
}
} // namespace glasssix::face