#include "gx_face_api.h"

#include "../src/nessus/protocol.hpp"
#include "../src/nessus/protocols/damocles.hpp"
#include "../src/nessus/protocols/gungnir.hpp"
#include "../src/nessus/protocols/irisviel.hpp"
#include "../src/nessus/protocols/longinus.hpp"
#include "../src/nessus/protocols/romancia.hpp"
#include "../src/nessus/protocols/selene.hpp"
#include "../src/nessus/protocols/valklyrs.hpp"
#include "config.hpp"

#include <random>

#include <g6/error_extensions.hpp>

#include <opencv2/opencv.hpp>

namespace glasssix::face {
    namespace {
        auto&& protocol_ptr = nessus_protocol::instance();
    }

    abi::string get_random_string(size_t len) {
        abi::string ans;
        std::random_device rd; // 将用于为随机数引擎获得种子
        std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
        std::uniform_int_distribution<> dis(0, 61);
        for (int i = 0; i < len; i++) {
            int temp = dis(gen);
            if (temp < 26)
                ans += ('a' + temp);
            else if (temp < 52)
                ans += ('A' + temp - 26);
            else
                ans += ('0' + temp - 52);
        }
        return ans;
    }

    inline int ComputeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int x = std::max(0, std::min(ax2, bx2) - std::max(ax1, bx1));
        int y = std::max(0, std::min(ay2, by2) - std::max(ay1, by1));
        return x * y;
    }

    class gx_img_api::impl {
    public:
        impl(abi::string path) {

            img = cv::imread(path.c_str());
            if (img.empty()) {
                throw source_code_aware_runtime_error(U8("Error: Could not load image"));
            }
            uchar val[105];
            memset(val, 0, sizeof(val));
            std::ifstream in_file(path.c_str(), std::ios::in | std::ios::binary);
            in_file.read((char*) &val, 10);
            type = check_type(val, 10);
            if (type == "") {
                throw source_code_aware_runtime_error(U8("Error: The picture is not in the right format"));
            }
            data_len = 1llu * img.channels() * img.cols * img.rows;
        }
        impl(std::vector<uchar>& buffer) {

            type = check_type(buffer, 10);
            if (type == "") {
                throw source_code_aware_runtime_error(U8("Error: The picture is not in the right format"));
            }
            img      = cv::imdecode(buffer, cv::IMREAD_COLOR);
            data_len = 1llu * img.channels() * img.cols * img.rows;
        }
        ~impl() {}

        abi::string check_type(std::vector<uchar>& val, int len) {
            char s[20], temp[50];
            memset(s, 0, sizeof(s));
            memset(temp, 0, sizeof(temp));
            for (int i = 0; i < len && i < 5; i++) {
                sprintf(s, "%02X", val[i]);
                strcat(temp, s);
                if (strcmp(temp, "FFD8FF") == 0)
                    return ".jpg";
                else if (strcmp(temp, "89504E47") == 0)
                    return ".png";
                else if (strcmp(temp, "424D") == 0)
                    return ".bmp";
            }
            return "";
        }

        abi::string check_type(uchar* val, int len) {
            char s[20], temp[50];
            memset(s, 0, sizeof(s));
            memset(temp, 0, sizeof(temp));
            for (int i = 0; i < len && i < 5; i++) {
                sprintf(s, "%02X", val[i]);
                strcat(temp, s);
                if (strcmp(temp, "FFD8FF") == 0)
                    return ".jpg";
                else if (strcmp(temp, "89504E47") == 0)
                    return ".png";
                else if (strcmp(temp, "424D") == 0)
                    return ".bmp";
            }
            return "";
        }

        cv::Mat img;
        size_t data_len;
        abi::string type;
    };

    gx_img_api::gx_img_api(abi::string path) : impl_{std::make_unique<impl>(path)} {}
    gx_img_api::gx_img_api(std::vector<uchar>& buffer) : impl_{std::make_unique<impl>(buffer)} {}
    gx_img_api::~gx_img_api() {}
    gx_img_api::gx_img_api(gx_img_api&&) noexcept            = default;
    gx_img_api& gx_img_api::operator=(gx_img_api&&) noexcept = default;

    int gx_img_api::get_rows() {
        return impl_->img.rows;
    }
    int gx_img_api::get_cols() {
        return impl_->img.cols;
    }
    uchar* gx_img_api::get_data() {
        return impl_->img.data;
    }
    size_t gx_img_api::get_data_len() {
        return impl_->data_len;
    }
    abi::string gx_img_api::get_type() {
        return impl_->type;
    }

    inline float DotProductAVX256(const abi::vector<float>& emb_1, const abi::vector<float>& emb_2) {
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

    inline float Cosine_distance_AVX256(abi::vector<float>& x, abi::vector<float>& y) {
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

    gx_face_api::gx_face_api() : impl_{std::make_unique<impl>()} {}
    gx_face_api::~gx_face_api() {}
    gx_face_api::gx_face_api(gx_face_api&&) noexcept            = default;
    gx_face_api& gx_face_api::operator=(gx_face_api&&) noexcept = default;

    class gx_face_api::impl {
    public:
        impl() {
            _config     = new config();
            cache.index = 0;
            cache.track_history.clear();
            cache.track_history_id.clear();
            protocol_ptr.init(_config->_configure_directory.directory);

            longinus_handle =
                protocol_ptr.make_instance<longinus>(longinus_new_param{.device = _config->_detect_config.device,
                    .models_directory = _config->_detect_config.models_directory});
            damocles_handle =
                protocol_ptr.make_instance<damocles>(damocles_new_param{_config->_action_live_config.device,
                    _config->_action_live_config.use_int8, _config->_action_live_config.models_directory});
            irisivel_handle = protocol_ptr.make_instance<irisviel>(
                irisviel_new_param{_config->_face_user_config.dimension, _config->_face_user_config.working_directory});
            irisivel_mask_handle = protocol_ptr.make_instance<irisviel>(irisviel_new_param{
                _config->_face_user_config.dimension, _config->_face_user_config.working_directory_mask});
            romancia_handle      = protocol_ptr.make_instance<romancia>(
                romancia_new_param{_config->_blur_config.device, _config->_blur_config.models_directory});
            selene_handle = protocol_ptr.make_instance<selene>(
                selene_new_param{_config->_feature_config.device, _config->_feature_config.models_directory,
                    _config->_feature_config.model_type, _config->_feature_config.use_int8});
            gungnir_handle; //人头检测预留
            valklyrs_handle; //车辆行人预留
        }
        ~impl() {}

        bool track_check(face_info& face) {
            std::unordered_map<int, face_info>::iterator it;
            for (it = cache.track_history.begin(); it != cache.track_history.end(); it++) {
                if (1.0
                        * ComputeArea(face.x, face.y, face.x + face.width, face.y + face.height, it->second.x,
                            it->second.y, it->second.x + it->second.width, it->second.y + it->second.height)
                        / std::min(face.width * face.height, it->second.width * it->second.height)
                    >= 0.60) {
                    return true;
                }
            }
            return false;
        }
        struct track_cache {
            std::unordered_map<int, face_info> track_history;
            std::unordered_map<int, abi::string> track_history_id;
            int index = 0;
        } cache;
        config* _config;
        damocles damocles_handle;
        gungnir gungnir_handle;
        irisviel irisivel_mask_handle;
        irisviel irisivel_handle;
        longinus longinus_handle;
        romancia romancia_handle;
        selene selene_handle;
        valklyrs valklyrs_handle;
    };


    //人脸检测
    abi::vector<face_info> gx_face_api::gx_detect(gx_img_api& mat) {
        abi::vector<face_info> ans;
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result = protocol_ptr.invoke<longinus::detect>(impl_->longinus_handle,
            longinus_detect_param{.instance_guid = "",
                .format                          = impl_->_config->_detect_config.format,
                .height                          = mat.get_rows(),
                .width                           = mat.get_cols(),
                .min_size                        = impl_->_config->_detect_config.min_size,
                .threshold                       = impl_->_config->_detect_config.threshold,
                .do_attributing                  = impl_->_config->_detect_config.do_attributing},
            str);
        ans         = result.facerectwithfaceinfo_list;
        return ans;
    }

    //人脸追踪
    abi::vector<face_trace_info> gx_face_api::gx_track(gx_img_api& mat) {
        abi::vector<face_trace_info> ans;
        if (impl_->cache.index % (impl_->_config->_track_config.detect_intv_before_track) == 0) {
            abi::vector<face_info> faces = gx_detect(mat);
            for (int i = 0; i < faces.size(); i++) {
                if (!impl_->track_check(faces[i])) {
                    impl_->cache.track_history[faces[i].x * 10000 + faces[i].y]    = faces[i];
                    impl_->cache.track_history_id[faces[i].x * 10000 + faces[i].y] = get_random_string(32);
                }
            }
        }

        std::unordered_map<int, face_info>::iterator it;
        std::unordered_map<int, face_info> temp_faces;
        std::unordered_map<int, abi::string> temp_faces_id;
        for (it = impl_->cache.track_history.begin(); it != impl_->cache.track_history.end(); it++) {
            std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
            auto result = protocol_ptr.invoke<longinus::trace>(impl_->longinus_handle,
                longinus_trace_param{
                    .instance_guid = "",
                    .format        = impl_->_config->_detect_config.format,
                    .height        = mat.get_rows(),
                    .width         = mat.get_cols(),
                    .face          = it->second,
                },
                str);
            if (result.trace_success == true) {
                //更新追踪坐标
                temp_faces[it->second.x * 10000 + it->second.y]    = result.facerectwithfaceinfo.value();
                temp_faces_id[it->second.x * 10000 + it->second.y] = impl_->cache.track_history_id[it->first];
                ans.emplace_back(face_trace_info{.trace_success = result.trace_success,
                    .facerectwithfaceinfo                       = result.facerectwithfaceinfo,
                    .trace_id                                   = impl_->cache.track_history_id[it->first]});
            }
        }
        impl_->cache.track_history.clear();
        impl_->cache.track_history = std::move(temp_faces);
        impl_->cache.track_history_id.clear();
        impl_->cache.track_history_id = std::move(temp_faces_id);
        impl_->cache.index++;
        return ans;
    }

    //清除人脸跟踪历史
    void gx_face_api::gx_clear_track_history() {
        impl_->cache.index = 0;
        impl_->cache.track_history.clear();
        impl_->cache.track_history_id.clear();
        return;
    }

    //人脸质量(模糊度)检测
    faces_blur gx_face_api::gx_face_blur(gx_img_api& mat) {
        faces_blur ans;
        abi::vector<face_info> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result                   = protocol_ptr.invoke<romancia::blur_detect>(impl_->romancia_handle,
            romancia_blur_detect_param{.instance_guid = "",
                                  .format                               = impl_->_config->_blur_config.format,
                                  .height                               = mat.get_rows(),
                                  .width                                = mat.get_cols(),
                                  .facerect_list                        = faces},
            str);
        ans.facerectwithfaceinfo_list = faces;
        ans.clarity                   = result.clarity;
        return ans;
    }

    //配合活体检测
    face_info gx_face_api::gx_face_action_live(int action_type, bool& action_result, gx_img_api& mat) {
        face_info ans;
        action_result                = 0;
        abi::vector<face_info> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;
        ans = faces[0];

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result   = protocol_ptr.invoke<damocles::presentation_attack_detect>(impl_->damocles_handle,
            damocles_presentation_attack_detect_param{.instance_guid = "",
                  .action_cmd                                          = action_type,
                  .format                                              = impl_->_config->_action_live_config.format,
                  .height                                              = mat.get_rows(),
                  .width                                               = mat.get_cols(),
                  .facerect                                            = ans},
            str);
        action_result = result.presentation_attack_result;
        return ans;
    }

    //静默活体检测
    faces_spoofing gx_face_api::gx_face_spoofing_live(gx_img_api& mat) {
        faces_spoofing ans;
        abi::vector<face_info> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result                   = protocol_ptr.invoke<damocles::spoofing_detect>(impl_->damocles_handle,
            damocles_spoofing_detect_param{.instance_guid = "",
                                  .format                                   = impl_->_config->_action_live_config.format,
                                  .height                                   = mat.get_rows(),
                                  .width                                    = mat.get_cols(),
                                  .facerect_list                            = faces},
            str);
        ans.facerectwithfaceinfo_list = faces;
        ans.spoofing_result           = result.spoofing_result;

        return ans;
    }

    //特征提取融合
    faces_feature gx_face_api::gx_face_feature(gx_img_api& mat) {
        faces_feature ans;
        abi::vector<face_info> faces = gx_detect(mat);
        if (faces.size() == 0)
            return ans;

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto romancia_result = protocol_ptr.invoke<romancia::alignFace>(impl_->romancia_handle,
            romancia_align_face_param{.instance_guid = "",
                .format                              = impl_->_config->_feature_config.format,
                .height                              = mat.get_rows(),
                .width                               = mat.get_cols(),
                .facerectwithfaceinfo_list           = faces},
            str);
        if (romancia_result.aligned_images.size() == 0) {
            return ans;
        }

        std::array<char, 0> arr{};
        auto selene_result = protocol_ptr.invoke<selene::forward>(impl_->selene_handle,
            selene_forward_param{.instance_guid = "",
                .aligned_images                 = romancia_result.aligned_images,
                .format                         = romancia_result.format},
            std::span<char>{arr});

        ans.facerectwithfaceinfo_list = faces;
        ans.features                  = selene_result.features;

        return ans;
    }

    // 特征值库加载
    void gx_face_api::gx_user_load(bool is_mask) {

        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::load_databases>(
            is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
            irisviel_load_databases_param{.instance_guid = ""}, std::span<char>{arr});
    }

    // 特征值库搜索
    faces_search_info gx_face_api::gx_user_search(gx_img_api& mat, int top, float min_similarity, bool is_mask) {
        faces_search_info ans;
        faces_feature faces = gx_face_feature(mat);
        if (faces.facerectwithfaceinfo_list.size() == 0 || faces.features.size() == 0)
            return ans;

        std::array<char, 0> arr{};
        auto result =
            protocol_ptr.invoke<irisviel::search>(is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
                irisviel_search_param{
                    .instance_guid  = "",
                    .feature        = faces.features[0].feature,
                    .top            = top,
                    .min_similarity = min_similarity,
                },
                std::span<char>{arr});
        ans.result = result.result;

        return ans;
    }

    //特征值库清除缓存
    void gx_face_api::gx_user_clear(bool is_mask) {
        std::array<char, 0> arr{};
        auto result =
            protocol_ptr.invoke<irisviel::clear>(is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
                irisviel_clear_param{.instance_guid = ""}, std::span<char>{arr});
    }

    //特征值库清空
    void gx_face_api::gx_user_remove_all(bool is_mask) {

        std::array<char, 0> arr{};
        auto result =
            protocol_ptr.invoke<irisviel::remove_all>(is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
                irisviel_remove_all_param{.instance_guid = ""}, std::span<char>{arr});
    }

    //特征值库批量删除
    void gx_face_api::gx_user_remove_records(abi::vector<abi::string>& keys, bool is_mask) {

        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::remove_records>(
            is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
            irisviel_remove_records_param{.instance_guid = "", .keys = keys}, std::span<char>{arr});
    }

    //特征值库批量添加
    abi::vector<bool> gx_face_api::gx_user_add_records(
        abi::vector<abi::string>& keys, abi::vector<gx_img_api>& mat, bool is_mask) {
        abi::vector<bool> ans(mat.size(), false);
        abi::vector<database_record> faces;
        if (keys.size() != mat.size())
            return ans;

        for (int i = 0; i < mat.size(); i++) {
            faces_feature temp = gx_face_feature(mat[i]);
            if (temp.features.size() == 0 || keys[i] == "") {
                ans[i] = false;
            } else {
                faces.emplace_back(database_record{.feature = temp.features[0].feature, .key = keys[i]});
                ans[i] = true;
            }
            // 批量入库就可以释放掉gx_img_api
        }
        std::array<char, 0> arr{};
        auto result =
            protocol_ptr.invoke<irisviel::add_records>(is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
                irisviel_add_records_param{.instance_guid = "", .data = faces}, std::span<char>{arr});

        return ans;
    }

    //特征值库批量更新
    abi::vector<bool> gx_face_api::gx_user_update_records(
        abi::vector<abi::string>& keys, abi::vector<gx_img_api>& mat, bool is_mask) {

        abi::vector<bool> ans(mat.size(), false);
        abi::vector<database_record> faces;
        if (keys.size() != mat.size())
            return ans;

        for (int i = 0; i < mat.size(); i++) {
            faces_feature temp = gx_face_feature(mat[i]);
            if (temp.features.size() == 0 || keys[i] == "") {
                ans[i] = false;
            } else {
                faces.emplace_back(database_record{.feature = temp.features[0].feature, .key = keys[i]});
                ans[i] = true;
            }
            // 批量更新就可以释放掉gx_img_api
        }
        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::update_records>(
            is_mask ? impl_->irisivel_mask_handle : impl_->irisivel_handle,
            irisviel_update_records_param{.instance_guid = "", .data = faces}, std::span<char>{arr});

        return ans;
    }

    //人脸识别流程融合
    faces_search_info gx_face_api::gx_detect_integration(gx_img_api& mat, int top, float min_similarity, bool is_mask) {
        faces_search_info ans;
        faces_spoofing faces = gx_face_spoofing_live(mat);
        if (faces.spoofing_result.size() == 0) {
            printf("no face!\n");
            return ans;
        } else if (faces.spoofing_result[0].prob[1] < 0.5) {
            printf("prob < 0.5 !\n");
            return ans;
        }
        gx_user_load(is_mask);
        ans = gx_user_search(mat, top, min_similarity, is_mask);
        return ans;
    }

    // 1:1特征值对比接口
    double gx_face_api::gx_feature_comparison(gx_img_api& mat_A, gx_img_api& mat_B) {
        double ans            = 0;
        faces_feature faces_A = gx_face_feature(mat_A);
        faces_feature faces_B = gx_face_feature(mat_B);
        if (faces_A.features.size() == 0 || faces_B.features.size() == 0)
            return 0;

        abi::vector<float> x = faces_A.features[0].feature;
        abi::vector<float> y = faces_B.features[0].feature;

        if (x.size() == 0 || y.size() == 0 || x.size() != y.size())
            return 0;
        ans = Cosine_distance_AVX256(x, y);
        return ans;
    }

} // namespace glasssix::face