#include "gx_face_api.hpp"

#include "distance/distance.hpp"
#include "sdk_share.hpp"

#include <cmath>
#include <fstream>
#include <random>

#include <g6/json_extensions.hpp>

namespace glasssix {

    thread_pool pool_irisviel(1);
    inline float Cosine_distance_AVX256(abi::vector<float>& x, abi::vector<float>& y) {
        float sum, a, b;
        size_t len     = x.size();
        float xx[1024] = {0}, yy[1024] = {0};
        for (int i = 0; i < x.size(); i++)
            xx[i] = x[i], yy[i] = y[i];
        a = distance_inner_product::compare(xx, xx, (uint32_t) x.size());
        b = distance_inner_product::compare(yy, yy, (uint32_t) y.size());
        if (a == 0 || b == 0)
            return 0;
        sum       = distance_inner_product::compare(xx, yy, (uint32_t) x.size());
        float ans = sum / (sqrt(a) * sqrt(b));
        ans       = std::min(1.0f, static_cast<float>(fabs(ans)));
        return ans;
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

    gx_face_api::gx_face_api() : impl_{std::make_unique<impl>()} {}
    gx_face_api::gx_face_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_face_api::~gx_face_api() {}
    gx_face_api::gx_face_api(gx_face_api&&) noexcept            = default;
    gx_face_api& gx_face_api::operator=(gx_face_api&&) noexcept = default;
    class gx_face_api::impl {
    public:
        void init() {
            empower_key = get_empower_key(_config->_configure_directory.license_directory);
            empower.set_serial_number(_config->_configure_directory.empower_serial_number);
            empower.set_algorithm_id(empower_algorithm_id);
            empower.set_license(empower_key.c_str());
            empower.evaluate_license(empower_Callback, nullptr);
            cache.index = 0;
            cache.track_history.clear();
            cache.track_history_id.clear();
        }
        impl() {
            if (_config == nullptr) {
                _config = new config();
                pool    = new thread_pool(_config->_configure_directory.thread_pool_num);
            }
            init();
        }
        impl(const abi::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                pool    = new thread_pool(_config->_configure_directory.thread_pool_num);
            }
            init();
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

    private:
        secret_key_empower empower;
        std::string empower_key          = "";
        std::string empower_algorithm_id = share_platform_name + "_" + share_empower_language + "_FACE_V1.2.0";
        std::string get_empower_key(std::string& path) {
            std::ifstream key(path, std::ios::in);
            if (!key.is_open()) {
                key.close();
                if (!empower_warning_flag) {
                    printf("Warning: license_directory :Failed to open file\n");
                    empower_warning_flag = true;
                }
                return "";
            }
            std::string ans;
            key >> ans;
            return ans;
        }
    };

    // 人脸检测
    abi::vector<face_info> gx_face_api::detect(const gx_img_api& mat) {
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            abi::vector<face_info> ans;
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result = ptr->protocol_ptr.invoke<longinus::detect>(ptr->longinus_handle,
                longinus_detect_param{.instance_guid = "",
                    .format                          = _config->_detect_config.format,
                    .height                          = mat.get_rows(),
                    .width                           = mat.get_cols(),
                    .min_size                        = _config->_detect_config.min_size,
                    .threshold                       = _config->_detect_config.threshold,
                    .do_attributing                  = _config->_detect_config.do_attributing},
                str);
            ans         = result.facerectwithfaceinfo_list;
            for (int i = 0; i < ans.size(); ++i) {
                if (ans[i].height * ans[i].width
                    < _config->_detect_config.min_face
                          * _config->_detect_config.min_face) // 不处理小于min_face * min_face的人脸
                {
                    ans.erase(ans.begin() + i, ans.end());
                    break;
                }
            }
            return ans;
        });
        return result_pool.get();
    }

    // 人脸追踪
    abi::vector<face_trace_info> gx_face_api::track(const gx_img_api& mat) {
        abi::vector<face_trace_info> ans;
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            // 人脸检测-------
            abi::vector<face_info> faces;
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result = ptr->protocol_ptr.invoke<longinus::detect>(ptr->longinus_handle,
                longinus_detect_param{.instance_guid = "",
                    .format                          = _config->_detect_config.format,
                    .height                          = mat.get_rows(),
                    .width                           = mat.get_cols(),
                    .min_size                        = _config->_detect_config.min_size,
                    .threshold                       = _config->_detect_config.threshold,
                    .do_attributing                  = _config->_detect_config.do_attributing},
                str);
            faces       = result.facerectwithfaceinfo_list;
            for (int i = 0; i < faces.size(); ++i) {
                if (faces[i].height * faces[i].width
                    < _config->_detect_config.min_face
                          * _config->_detect_config.min_face) // 不处理小于min_face * min_face的人脸
                {
                    faces.erase(faces.begin() + i, faces.end());
                    break;
                }
            }
            // abi::vector<face_info> faces得到 人脸检测结果
            for (int i = 0; i < faces.size(); i++) {
                if (!impl_->track_check(faces[i])) {
                    impl_->cache.track_history[faces[i].x * 10000 + faces[i].y]    = faces[i];
                    impl_->cache.track_history_id[faces[i].x * 10000 + faces[i].y] = get_random_string(32);
                }
            }

            std::unordered_map<int, face_info>::iterator it;
            std::unordered_map<int, face_info> temp_faces;
            std::unordered_map<int, abi::string> temp_faces_id;
            for (it = impl_->cache.track_history.begin(); it != impl_->cache.track_history.end(); it++) {
                auto result = ptr->protocol_ptr.invoke<longinus::trace>(ptr->longinus_handle,
                    longinus_trace_param{
                        .instance_guid = "",
                        .format        = _config->_detect_config.format,
                        .height        = mat.get_rows(),
                        .width         = mat.get_cols(),
                        .face          = it->second,
                    },
                    str);
                if (result.trace_success == true) {
                    // 更新追踪坐标
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
        });
        return result_pool.get();
    }

    // 清除人脸跟踪历史
    bool gx_face_api::clear_track_history() {
        impl_->cache.index = 0;
        impl_->cache.track_history.clear();
        impl_->cache.track_history_id.clear();
        return true;
    }

    // 人脸质量(模糊度)检测
    faces_blur gx_face_api::face_blur(const gx_img_api& mat) {
        faces_blur ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result                   = ptr->protocol_ptr.invoke<romancia::blur_detect>(ptr->romancia_handle,
                romancia_blur_detect_param{.instance_guid = "",
                                      .format                               = _config->_blur_config.format,
                                      .height                               = mat.get_rows(),
                                      .width                                = mat.get_cols(),
                                      .facerect_list                        = faces},
                str);
            ans.facerectwithfaceinfo_list = faces;
            ans.clarity                   = result.clarity;
            return ans;
        });
        return result_pool.get();
    }

    // 配合活体检测
    face_info gx_face_api::face_action_live(action_live_type action_type, bool& action_result, const gx_img_api& mat) {
        face_info ans;
        action_result                = 0;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        ans              = faces[0];
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result   = ptr->protocol_ptr.invoke<damocles::presentation_attack_detect>(ptr->damocles_handle,
                damocles_presentation_attack_detect_param{.instance_guid = "",
                      .action_cmd                                          = action_type,
                      .format                                              = _config->_action_live_config.format,
                      .height                                              = mat.get_rows(),
                      .width                                               = mat.get_cols(),
                      .facerect                                            = ans},
                str);
            action_result = result.presentation_attack_result;
            return ans;
        });
        return result_pool.get();
    }

    // 静默活体检测
    faces_spoofing gx_face_api::face_spoofing_live(const gx_img_api& mat) {
        faces_spoofing ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto result                   = ptr->protocol_ptr.invoke<damocles::spoofing_detect>(ptr->damocles_handle,
                damocles_spoofing_detect_param{.instance_guid = "",
                                      .format                                   = _config->_action_live_config.format,
                                      .height                                   = mat.get_rows(),
                                      .width                                    = mat.get_cols(),
                                      .facerect_list                            = faces},
                str);
            ans.facerectwithfaceinfo_list = faces;
            ans.spoofing_result           = result.spoofing_result;

            return ans;
        });
        return result_pool.get();
    }

    // 特征提取融合
    faces_feature gx_face_api::face_feature(const gx_img_api& mat, bool is_clip) {
        faces_feature ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        faces.erase(faces.begin() + 1, faces.end()); // 只保留最大人脸
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();
            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto romancia_result = ptr->protocol_ptr.invoke<romancia::alignFace>(ptr->romancia_handle,
                romancia_align_face_param{.instance_guid = "",
                    .format                              = _config->_feature_config.format,
                    .height                              = mat.get_rows(),
                    .width                               = mat.get_cols(),
                    .facerectwithfaceinfo_list           = faces},
                str);
            if (romancia_result.aligned_images.size() == 0)
                return ans;
            std::array<char, 0> arr{};
            faces_feature ans_temp;
            auto selene_result                 = ptr->protocol_ptr.invoke<selene::forward>(ptr->selene_handle,
                selene_forward_param{.instance_guid = "",
                                    .aligned_images                 = romancia_result.aligned_images,
                                    .format                         = romancia_result.format},
                std::span<char>{arr});
            ans_temp.features                  = selene_result.features;
            ans_temp.facerectwithfaceinfo_list = faces;
            int y1, x1, y2, x2;
            y1 = faces[0].y - faces[0].height * 2 / 10;
            x1 = faces[0].x - faces[0].width * 2 / 10;
            y2 = std::min(mat.get_rows(), y1 + faces[0].height * 14 / 10);
            x2 = std::min(mat.get_cols(), x1 + faces[0].width * 14 / 10);
            if (is_clip)
                ans_temp.img_buffer = mat.cropped(std::max(y1, 0), y2, std::max(x1, 0), x2);
            else
                ans_temp.img_buffer.clear();
            ans = std::move(ans_temp);
            return ans;
        });
        return result_pool.get();
    }

    // 特征值库加载
    bool gx_face_api::user_load() {
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            std::array<char, 0> arr{};
            ptr->protocol_ptr.invoke<irisviel::load_databases>(
                ptr->irisivel_handle, irisviel_load_databases_param{.instance_guid = ""}, std::span<char>{arr});
            return true;
        });
        return result_pool.get();
    }

    // 特征值库搜索
    faces_search_info gx_face_api::user_search(const gx_img_api& mat, int top, float min_similarity) {
        faces_search_info ans;
        if (top <= 0)
            throw source_code_aware_runtime_error(U8("Error: Invalid parameter: top <= 0."));
        if (top > 50)
            throw source_code_aware_runtime_error(U8("Error: Invalid parameter: top > 50."));
        if (std::signbit(min_similarity) || min_similarity > 1.001)
            throw source_code_aware_runtime_error(
                U8("Error: Invalid parameter: min_similarity < 0 || min_similarity > 1."));
        faces_feature faces = face_feature(mat, false);
        if (faces.facerectwithfaceinfo_list.size() == 0 || faces.features.size() == 0)
            return ans;
        std::array<char, 0> arr{};
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr    = thread_algo_irisviel_ptr;
            auto result = ptr->protocol_ptr.invoke<irisviel::search_nf>(ptr->irisivel_handle,
                irisviel_search_nf_param{
                    .instance_guid  = "",
                    .feature        = faces.features[0].feature,
                    .top            = top,
                    .min_similarity = min_similarity,
                },
                std::span<char>{arr});
            ans.result  = result.result;
            return ans;
        });
        return result_pool.get();
    }

    // 特征值库清空
    bool gx_face_api::user_remove_all() {
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            std::array<char, 0> arr{};
            ptr->protocol_ptr.invoke<irisviel::remove_all>(
                ptr->irisivel_handle, irisviel_remove_all_param{.instance_guid = ""}, std::span<char>{arr});
            return true;
        });
        return result_pool.get();
    }

    // 特征值库批量删除
    abi::vector<face_user_result> gx_face_api::user_remove_records(const abi::vector<abi::string>& keys) {
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            abi::vector<face_user_result> ans(keys.size());
            std::array<char, 0> arr{};
            auto result = ptr->protocol_ptr.invoke<irisviel::remove_records>(ptr->irisivel_handle,
                irisviel_remove_records_param{.instance_guid = "", .keys = keys}, std::span<char>{arr});
            for (int i = 0; i < keys.size(); i++) {
                ans[i].key     = keys[i];
                ans[i].success = 0;
                ans[i].img_buffer.clear();
                ans[i].facerectwithfaceinfo = std::nullopt;
            }
            return ans;
        });
        return result_pool.get();
    }

    // 特征值库批量添加
    abi::vector<face_user_result> gx_face_api::user_add_records(
        const abi::vector<abi::string>& keys, const abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo) {
        abi::vector<face_user_result> ans(mat.size());
        abi::vector<database_record> faces_A_add;
        abi::vector<database_record> faces_A_update;
        if (keys.size() != mat.size())
            throw source_code_aware_runtime_error(U8("Error: keys.size != mat.size"));
        if (mat.size() > 1000)
            throw source_code_aware_runtime_error(U8("Error: mat.size > 1000"));
        if (mat.size() == 0)
            throw source_code_aware_runtime_error(U8("Error: mat.size == 0"));
        for (int i = 0; i < mat.size(); i++) {
            if (keys[i] == "") {
                ans[i].key     = "";
                ans[i].success = -1;
                ans[i].img_buffer.clear();
                ans[i].facerectwithfaceinfo = std::nullopt;
                continue;
            }
            faces_feature temp = face_feature(mat[i], is_clip);
            if (temp.features.size() == 0) {
                ans[i].key     = keys[i];
                ans[i].success = -2;
                ans[i].img_buffer.clear();
                ans[i].facerectwithfaceinfo = std::nullopt;
            } else if (user_contains_key(keys[i]) == false) {
                ans[i].key        = keys[i];
                ans[i].success    = 1;
                ans[i].img_buffer = temp.img_buffer;
                if (is_faceinfo)
                    ans[i].facerectwithfaceinfo = temp.facerectwithfaceinfo_list[0];
                else
                    ans[i].facerectwithfaceinfo = std::nullopt;
                faces_A_add.emplace_back(database_record{.feature = temp.features[0].feature, .key = keys[i]});
            } else {
                ans[i].key        = keys[i];
                ans[i].success    = 2;
                ans[i].img_buffer = temp.img_buffer;
                if (is_faceinfo)
                    ans[i].facerectwithfaceinfo = temp.facerectwithfaceinfo_list[0];
                else
                    ans[i].facerectwithfaceinfo = std::nullopt;
                faces_A_update.emplace_back(database_record{.feature = temp.features[0].feature, .key = keys[i]});
            }
            // 批量入库就可以释放掉gx_img_api
        }
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            std::array<char, 0> arr{};
            // 添加
            auto result_A = ptr->protocol_ptr.invoke<irisviel::add_records>(ptr->irisivel_handle,
                irisviel_add_records_param{.instance_guid = "", .data = faces_A_add}, std::span<char>{arr});
            // 更新
            auto result_B = ptr->protocol_ptr.invoke<irisviel::update_records>(ptr->irisivel_handle,
                irisviel_update_records_param{.instance_guid = "", .data = faces_A_update}, std::span<char>{arr});
            // TODO  AlgorithmZoo 的返回结果还没改 临时这样
            // 之后根据  ans[i].success 来获取异常状态码
            for (int i = 0; i < ans.size(); i++) {
                if (ans[i].success > 0) {
                    ans[i].success = 0;
                }
            }
            return ans;
        });
        return result_pool.get();
    }

    // 特征值库批量添加
    abi::vector<face_user_result> gx_face_api::user_add_records(
        abi::vector<abi::string>& keys, abi::vector<abi::vector<float>>& features) {
        abi::vector<face_user_result> ans(features.size());
        abi::vector<database_record> faces_A_add;
        abi::vector<database_record> faces_A_update;
        if (keys.size() != features.size())
            throw source_code_aware_runtime_error(U8("Error: keys.size != features.size"));
        if (features.size() > 1000)
            throw source_code_aware_runtime_error(U8("Error: features.size > 1000"));
        if (features.size() == 0)
            throw source_code_aware_runtime_error(U8("Error: features.size == 0"));
        for (int i = 0; i < features.size(); i++) {
            ans[i].img_buffer.clear();
            ans[i].facerectwithfaceinfo = std::nullopt;
            if (keys[i] == "") {
                ans[i].key     = "";
                ans[i].success = -1;
            } else if (features[i].size() != _config->_face_user_config.dimension) {
                ans[i].key     = keys[i];
                ans[i].success = -3;
            } else if (user_contains_key(keys[i]) == false) {
                ans[i].key     = keys[i];
                ans[i].success = 1;
                faces_A_add.emplace_back(database_record{.feature = features[i], .key = keys[i]});
            } else {
                ans[i].key     = keys[i];
                ans[i].success = 2;
                faces_A_update.emplace_back(database_record{.feature = features[i], .key = keys[i]});
            }
            // 批量入库就可以释放掉gx_img_api
        }
        std::array<char, 0> arr{};

        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            // 添加
            auto result_A = ptr->protocol_ptr.invoke<irisviel::add_records>(ptr->irisivel_handle,
                irisviel_add_records_param{.instance_guid = "", .data = faces_A_add}, std::span<char>{arr});
            // 更新
            auto result_B = ptr->protocol_ptr.invoke<irisviel::update_records>(ptr->irisivel_handle,
                irisviel_update_records_param{.instance_guid = "", .data = faces_A_update}, std::span<char>{arr});
            // TODO  AlgorithmZoo 的返回结果还没改 临时这样
            // 之后根据  ans[i].success 来获取异常状态码
            for (int i = 0; i < ans.size(); i++) {
                if (ans[i].success > 0) {
                    ans[i].success = 0;
                }
            }
            return ans;
        });
        return result_pool.get();
    }

    // 特征值库键值查询
    bool gx_face_api::user_contains_key(const abi::string& key) {
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            std::array<char, 0> arr{};
            auto result = ptr->protocol_ptr.invoke<irisviel::contains_key>(ptr->irisivel_handle,
                irisviel_contains_key_param{.instance_guid = "", .key = key}, std::span<char>{arr});
            return result.result;
        });
        return result_pool.get();
    }

    // 特征值库记录总和
    std::uint64_t gx_face_api::user_record_count() {
        auto result_pool = pool_irisviel.enqueue([&] {
            if (thread_algo_irisviel_ptr == nullptr) {
                thread_algo_irisviel_ptr = new algo_irisviel_ptr();
            }
            auto ptr = thread_algo_irisviel_ptr;
            std::array<char, 0> arr{};
            auto result = ptr->protocol_ptr.invoke<irisviel::record_count>(
                ptr->irisivel_handle, irisviel_record_count_param{.instance_guid = ""}, std::span<char>{arr});
            return result.result;
        });
        return result_pool.get();
    }

    // 人脸识别流程融合
    faces_integration_search_info gx_face_api::detect_integration(
        const gx_img_api& mat, int top, float min_similarity) {
        faces_integration_search_info ans;
        faces_spoofing faces = face_spoofing_live(mat);
        if (faces.spoofing_result.size() == 0) {
            return ans;
        } else {
            ans.prob = faces.spoofing_result[0].prob[1];
            if (ans.prob < 0.75)
                return ans;
        }
        auto result = user_search(mat, top, min_similarity);
        ans.result  = result.result;
        return ans;
    }

    // 多人脸搜索
    abi::vector<faces_search_one_info> gx_face_api::detect_many_faces_integration(
        const gx_img_api& mat, bool is_living, float min_similarity) {
        abi::vector<faces_search_one_info> ans;
        abi::vector<face_info> faces_temp;
        if (is_living) {
            faces_spoofing spoofing = face_spoofing_live(mat);
            if (spoofing.spoofing_result.size() == 0)
                return ans;
            faces_temp = spoofing.facerectwithfaceinfo_list;
            for (int i = 0; i < spoofing.spoofing_result.size(); ++i) {
                faces_search_one_info temp;
                temp.prob                 = spoofing.spoofing_result[i].prob[1];
                temp.facerectwithfaceinfo = faces_temp[i];
                ans.emplace_back(temp);
            }

        } else {
            faces_temp = detect(mat);
            if (faces_temp.size() == 0)
                return ans;
            for (int i = 0; i < faces_temp.size(); ++i) {
                faces_search_one_info temp;
                temp.prob                 = std::nullopt;
                temp.facerectwithfaceinfo = faces_temp[i];
                ans.emplace_back(temp);
            }
        }
        auto result_pool = pool->enqueue([&] {
            std::thread::id id_ = std::this_thread::get_id();

            if (all_thread_algo_ptr[id_] == nullptr) {
                all_thread_algo_ptr[id_] = new algo_ptr();
            }
            auto ptr = all_thread_algo_ptr[id_];

            // 人脸对齐
            std::span<char> str{reinterpret_cast<char*>(const_cast<uchar*>(mat.get_data())), mat.get_data_len()};
            auto romancia_result = ptr->protocol_ptr.invoke<romancia::alignFace>(ptr->romancia_handle,
                romancia_align_face_param{.instance_guid = "",
                    .format                              = _config->_feature_config.format,
                    .height                              = mat.get_rows(),
                    .width                               = mat.get_cols(),
                    .facerectwithfaceinfo_list           = faces_temp},
                str);
            if (romancia_result.aligned_images.size() == 0)
                return ans;

            // 特征提取
            std::array<char, 0> arr{};
            faces_feature ans_temp;
            auto selene_result = ptr->protocol_ptr.invoke<selene::forward>(ptr->selene_handle,
                selene_forward_param{.instance_guid = "",
                    .aligned_images                 = romancia_result.aligned_images,
                    .format                         = romancia_result.format},
                std::span<char>{arr});

            auto result_pool_irisviel = pool_irisviel.enqueue([&] {
                if (thread_algo_irisviel_ptr == nullptr) {
                    thread_algo_irisviel_ptr = new algo_irisviel_ptr();
                }
                auto ptr_ = thread_algo_irisviel_ptr;
                // 多人脸搜索
                for (int i = 0; i < selene_result.features.size(); i++) {
                    auto result = ptr_->protocol_ptr.invoke<irisviel::search_nf>(ptr_->irisivel_handle,
                        irisviel_search_nf_param{
                            .instance_guid  = "",
                            .feature        = selene_result.features[i].feature,
                            .top            = 1,
                            .min_similarity = min_similarity,
                        },
                        std::span<char>{arr});
                    if (result.result.size() > 0)
                        ans[i].result = std::move(result.result[0]);
                }
                return ans;
            });
            return result_pool_irisviel.get();
        });
        return result_pool.get();
    }

    // 1:1特征值对比接口
    double gx_face_api::feature_comparison(const gx_img_api& mat_A, const gx_img_api& mat_B) {
        double ans                       = 0;
        abi::vector<face_info> is_mask_A = detect(mat_A);
        abi::vector<face_info> is_mask_B = detect(mat_B);
        if (is_mask_A.size() == 0 || is_mask_B.size() == 0)
            return ans;
        faces_feature faces_A = face_feature(mat_A, false);
        faces_feature faces_B = face_feature(mat_B, false);
        if (faces_A.features.size() == 0 || faces_B.features.size() == 0)
            return ans;
        abi::vector<float> x;
        abi::vector<float> y;
        x = faces_A.features[0].feature;
        y = faces_B.features[0].feature;
        if (x.size() == 0 || y.size() == 0 || x.size() != y.size())
            return ans;
        ans = Cosine_distance_AVX256(x, y);
        return ans;
    }

} // namespace glasssix