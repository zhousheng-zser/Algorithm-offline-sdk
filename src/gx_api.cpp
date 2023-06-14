#include "gx_api.hpp"

#include "../src/nessus/protocol.hpp"
#include "../src/nessus/protocols/damocles.hpp"
#include "../src/nessus/protocols/flame.hpp"
#include "../src/nessus/protocols/gungnir.hpp"
#include "../src/nessus/protocols/helmet.hpp"
#include "../src/nessus/protocols/irisviel.hpp"
#include "../src/nessus/protocols/longinus.hpp"
#include "../src/nessus/protocols/refvest.hpp"
#include "../src/nessus/protocols/romancia.hpp"
#include "../src/nessus/protocols/selene.hpp"
#include "../src/nessus/protocols/valklyrs.hpp"
#include "config.hpp"
#include "distance/distance.hpp"
#include "SecretKey_empower.hpp"
#include "decode/decode.hpp"

#include <cmath>
#include <fstream>
#include <mutex>
#include <random>

#include <g6/error_extensions.hpp>

#include <opencv2/opencv.hpp>
namespace glasssix {
    namespace {
        auto&& protocol_ptr = nessus_protocol::instance();
        config* _config     = nullptr;
        damocles damocles_handle;
        gungnir gungnir_handle;
        irisviel irisivel_handle;
        longinus longinus_handle;
        romancia romancia_handle;
        selene selene_handle;
        valklyrs valklyrs_handle;

        refvest refvest_handle; // 安全检测 反光衣
        flame flame_handle; // 安全监测 烟雾火焰
        helmet helmet_handle; // 安全监测 安全帽
        static std::mutex mutex_;

    } // namespace

    std::string getSubstring(const std::string& str64, int pos_t) {
        if (pos_t < 0 || pos_t + 24 > 64) 
            return "";

        std::string substring = str64.substr(pos_t, 24);
        return substring;
    }

    void empower_Callback(void* context, std::string success, const char* message, std::int64_t remaining_seconds) {
        int T=3;
        long long time_ll = std::stoll(get_time_code());
        while (T--) {
            std::string time = glasssix::format(U8("{:016}"), time_ll);
            try {
                std::string ans = getSubstring(success, time_ll % 39);
                ans = empower_time_decode(time, ans);
                if (ans == "Empower_is_True") {
                    return;
                }
            } catch(...) {;}
            time_ll--;
        }
        throw source_code_aware_runtime_error(U8("Error: empower Fail"));
        
    }

    inline float Cosine_distance_AVX256(abi::vector<float>& x, abi::vector<float>& y) {
        float sum, a, b;
        size_t len = x.size();
        float xx[1024], yy[1024];
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

    class gx_img_api::impl {
    public:
        impl(abi::string path, int limit) : img{cv::imread(path.c_str())} {
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
            if (img.cols * img.rows > limit ) {
                img.release();
                throw source_code_aware_runtime_error(U8("Error: The picture has more than maximun limit pixels"));
            }
            data_len = 1llu * img.channels() * img.cols * img.rows;
        }
        impl(std::vector<uchar>& buffer, int limit) {

            type = check_type(buffer, 10);
            if (type == "") {
                throw source_code_aware_runtime_error(U8("Error: The picture is not in the right format"));
            }
            img = cv::imdecode(buffer, cv::IMREAD_COLOR);
            if (img.cols * img.rows > limit) {
                img.release();
                throw source_code_aware_runtime_error(U8("Error: The picture has more than maximun limit pixels"));
            }
            data_len = 1llu * img.channels() * img.cols * img.rows;
        }

        impl(std::span<const uchar> bgr_data, int rows, int cols, int limit)
            : img(rows, cols, CV_8UC3) {
            std::memcpy(img.data, bgr_data.data(), bgr_data.size());

            if (img.empty()) {
                throw source_code_aware_runtime_error(U8("Error: Could not load image"));
            }
            if (img.cols * img.rows > limit) {
                img.release();
                throw source_code_aware_runtime_error(U8("Error: The picture has more than maximun limit pixels"));
            }
            data_len = 1llu * img.channels() * img.cols * img.rows;
        }

        ~impl() {}

        abi::string check_type(std::vector<uchar>& val, size_t len) {
            char s[20], temp[50];
            memset(s, 0, sizeof(s));
            memset(temp, 0, sizeof(temp));
            for (int i = 0; i < len && i < 5; i++) {
#ifdef _WIN32
                sprintf_s(s, "%02X", val[i]);
                strcat_s(temp, s);
#else
                sprintf(s, "%02X", val[i]);
                strcat(temp, s);
#endif
                if (strcmp(temp, "FFD8FF") == 0)
                    return ".jpg";
                else if (strcmp(temp, "89504E47") == 0)
                    return ".png";
                else if (strcmp(temp, "424D") == 0)
                    return ".bmp";
            }
            return "";
        }

        abi::string check_type(uchar* val, size_t len) {
            char s[20], temp[50];
            memset(s, 0, sizeof(s));
            memset(temp, 0, sizeof(temp));
            for (int i = 0; i < len && i < 5; i++) {
#ifdef _WIN32
                sprintf_s(s, "%02X", val[i]);
                strcat_s(temp, s);
#else
                sprintf(s, "%02X", val[i]);
                strcat(temp, s);
#endif
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

    gx_img_api::gx_img_api(abi::string path, int limit) : impl_{std::make_unique<impl>(path,  limit)} {}
    gx_img_api::gx_img_api(std::vector<uchar>& buffer, int limit) : impl_{std::make_unique<impl>(buffer, limit)} {}
    gx_img_api::gx_img_api(std::span<const uchar> bgr_data, int rows, int cols, int limit)
        : impl_{std::make_unique<impl>(bgr_data, rows, cols, limit)} {}
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
    bool gx_img_api::rotate(int deg) {
        if (deg == image_rotation_type::DEG90) {
            cv::rotate(impl_->img, impl_->img, cv::ROTATE_90_CLOCKWISE);
        } else if (deg == image_rotation_type::DEG180) {
            cv::flip(impl_->img, impl_->img, -1);
        } else if (deg == image_rotation_type::DEG270) {
            cv::rotate(impl_->img, impl_->img, cv::ROTATE_90_COUNTERCLOCKWISE);
        } else {
            return false;
        }
        impl_->data_len = 1llu * impl_->img.channels() * impl_->img.cols * impl_->img.rows;
        return true;
    }
    abi::vector<uchar> gx_img_api::cropped(int x1, int x2, int y1, int y2) {
        cv::Mat cropped_face = impl_->img(cv::Range(x1, x2), cv::Range(y1, y2));
        std::vector<uchar> buffer(1024 * 1024);
        cv::imencode(".jpg", cropped_face, buffer);
        abi::vector<uchar> ans(buffer.begin(), buffer.end());
        return ans;
    }

    gx_api::gx_api() : impl_{std::make_unique<impl>()} {}
    gx_api::gx_api(const abi::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_api::~gx_api() {}
    gx_api::gx_api(gx_api&&) noexcept            = default;
    gx_api& gx_api::operator=(gx_api&&) noexcept = default;

    class gx_api::impl {
    public:
        typedef void (impl::*set_protocols_handle)();

        void init() {
            std::fstream log("./log.txt", std::ios::out | std::ios::app);
            log << "license_directory " << _config->_configure_directory.license_directory << "\n";
            empower_key = get_empower_key(_config->_configure_directory.license_directory);
            empower.set_license(empower_key.c_str());
            empower.set_algorithm_id(empower_algorithm_id.c_str());
            empower.evaluate_license(empower_Callback, nullptr);
            cache.index = 0;
            cache.track_history.clear();
            cache.track_history_id.clear();
            set_Function();
            std::ifstream configure(_config->_configure_directory.directory);
            nlohmann::json protocols_list = nlohmann::json::parse(configure);
            
            for (int i = 0; i < protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = protocols_list["plugin_list"][i];
                try {
                    impl::set_protocols_handle fun = this->Function[temp_str];
                    if (fun != nullptr) {
                        log << "begin " << temp_str << "\n";
                        log.flush();
                        (this->*fun)();
                        log << "end " << temp_str << "\n";
                    }
                } catch (const std::exception& ex) {
                    throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                }
            }
            log.close();
        }


        impl() {
            if (_config == nullptr) {
                _config = new config();
                protocol_ptr.init(_config->_configure_directory.directory);
                init();
            }
        }

        impl(const abi::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                protocol_ptr.init(_config->_configure_directory.directory);
                init();
            }
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
        abi::vector<helmet_info> safe_production_helmet(gx_img_api& mat, const abi::vector<detecte_roi>& roi_list) {
            std::scoped_lock lock{mutex_};
            std::cout << "begin()\n";
            abi::vector<helmet_info> ans;
            std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
            for (int i = 0; i < roi_list.size(); ++i) {
                auto result = protocol_ptr.invoke<helmet::detect>(helmet_handle,
                    helmet_detect_param{.instance_guid = "",
                        .format                        = _config->_helemt_config.format,
                        .height                        = mat.get_rows(),
                        .width                         = mat.get_cols(),
                        .roi_x                         = roi_list[i].roi_x,
                        .roi_y                         = roi_list[i].roi_y,
                        .roi_width                     = roi_list[i].roi_width,
                        .roi_height                    = roi_list[i].roi_height,
                        .params =
                            helmet_detect_param::confidence_params{.conf_thres = _config->_flame_config.conf_thres,
                                .iou_thres                                     = _config->_flame_config.iou_thres}},
                    str);
                ans.emplace_back(result.detect_info);
            }
            std::cout << "end()\n";
            return ans;
        }
    

    private:
        SecretKey_empower empower;
        std::string empower_key = "";
        std::string empower_algorithm_id = "RK3588_C++_V1.0.0";
        std::string get_empower_key(std::string& path) {
            std::ifstream key(path, std::ios::in);
            if (!key.is_open()) {
                key.close();
                throw source_code_aware_runtime_error(U8("Error: license_directory :Failed to open file"));
            }
            std::string ans;
            key>>ans;
            return ans;
        }
        std::unordered_map<std::string, set_protocols_handle> Function;
        void set_Function() {
            Function["flame"]    = &impl::set_protocols_handl_flame;
            Function["refvest"]  = &impl::set_protocols_handl_refvest;
            Function["helmet"]   = &impl::set_protocols_handl_helmet;
            Function["selene"]   = &impl::set_protocols_handl_selene;
            Function["longinus"] = &impl::set_protocols_handl_longinus;
            Function["romancia"] = &impl::set_protocols_handl_romancia;
            Function["damocles"] = &impl::set_protocols_handl_damocles;
            Function["irisviel"] = &impl::set_protocols_handl_irisviel;
        }
        void set_protocols_handl_flame() {
            flame_handle = protocol_ptr.make_instance<flame>(
                flame_new_param{_config->_flame_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_refvest() {
            refvest_handle = protocol_ptr.make_instance<refvest>(
                refvest_new_param{_config->_refvest_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_helmet() {
            helmet_handle = protocol_ptr.make_instance<helmet>(
                helmet_new_param{_config->_helemt_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_selene() {
            selene_handle = protocol_ptr.make_instance<selene>(
                selene_new_param{_config->_feature_config.device, _config->_configure_directory.models_directory,
                    _config->_feature_config.model_type, _config->_feature_config.use_int8});
        }
        void set_protocols_handl_longinus() {
            longinus_handle =
                protocol_ptr.make_instance<longinus>(longinus_new_param{.device = _config->_detect_config.device,
                    .models_directory = _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_romancia() {
            romancia_handle = protocol_ptr.make_instance<romancia>(
                romancia_new_param{_config->_blur_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_damocles() {
            damocles_handle =
                protocol_ptr.make_instance<damocles>(damocles_new_param{_config->_action_live_config.device,
                    _config->_action_live_config.model_type, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_irisviel() {
            irisivel_handle = protocol_ptr.make_instance<irisviel>(
                irisviel_new_param{_config->_face_user_config.dimension, _config->_face_user_config.working_directory});
        }
};


    // 人脸检测
    abi::vector<face_info> gx_api::detect(gx_img_api& mat) {
        abi::vector<face_info> ans;
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result = protocol_ptr.invoke<longinus::detect>(longinus_handle,
            longinus_detect_param{.instance_guid = "",
                .format                          = _config->_detect_config.format,
                .height                          = mat.get_rows(),
                .width                           = mat.get_cols(),
                .min_size                        = _config->_detect_config.min_size,
                .threshold                       = _config->_detect_config.threshold,
                .do_attributing                  = _config->_detect_config.do_attributing},
            str);
        ans         = result.facerectwithfaceinfo_list;
        return ans;
    }

    // 人脸追踪
    abi::vector<face_trace_info> gx_api::track(gx_img_api& mat) {
        abi::vector<face_trace_info> ans;
        if (impl_->cache.index % (_config->_track_config.detect_intv_before_track) == 0) {
            abi::vector<face_info> faces = detect(mat);
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
            auto result = protocol_ptr.invoke<longinus::trace>(longinus_handle,
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
    }

    // 清除人脸跟踪历史
    bool gx_api::clear_track_history() {
        impl_->cache.index = 0;
        impl_->cache.track_history.clear();
        impl_->cache.track_history_id.clear();
        return true;
    }

    // 人脸质量(模糊度)检测
    faces_blur gx_api::face_blur(gx_img_api& mat) {
        faces_blur ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result                   = protocol_ptr.invoke<romancia::blur_detect>(romancia_handle,
            romancia_blur_detect_param{.instance_guid = "",
                                  .format                               = _config->_blur_config.format,
                                  .height                               = mat.get_rows(),
                                  .width                                = mat.get_cols(),
                                  .facerect_list                        = faces},
            str);
        ans.facerectwithfaceinfo_list = faces;
        ans.clarity                   = result.clarity;
        return ans;
    }

    // 配合活体检测
    face_info gx_api::face_action_live(action_live_type action_type, bool& action_result, gx_img_api& mat) {
        face_info ans;
        action_result                = 0;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        ans = faces[0];

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result   = protocol_ptr.invoke<damocles::presentation_attack_detect>(damocles_handle,
            damocles_presentation_attack_detect_param{.instance_guid = "",
                  .action_cmd                                          = action_type,
                  .format                                              = _config->_action_live_config.format,
                  .height                                              = mat.get_rows(),
                  .width                                               = mat.get_cols(),
                  .facerect                                            = ans},
            str);
        action_result = result.presentation_attack_result;
        return ans;
    }

    // 静默活体检测
    faces_spoofing gx_api::face_spoofing_live(gx_img_api& mat) {
        faces_spoofing ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto result                   = protocol_ptr.invoke<damocles::spoofing_detect>(damocles_handle,
            damocles_spoofing_detect_param{.instance_guid = "",
                                  .format                                   = _config->_action_live_config.format,
                                  .height                                   = mat.get_rows(),
                                  .width                                    = mat.get_cols(),
                                  .facerect_list                            = faces},
            str);
        ans.facerectwithfaceinfo_list = faces;
        ans.spoofing_result           = result.spoofing_result;

        return ans;
    }

    // 特征提取融合
    faces_feature gx_api::face_feature(gx_img_api& mat, bool is_clip) {

        faces_feature ans;
        abi::vector<face_info> faces = detect(mat);
        if (faces.size() == 0)
            return ans;
        faces.erase(faces.begin() + 1, faces.end()); // 只保留最大人脸

        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto romancia_result = protocol_ptr.invoke<romancia::alignFace>(romancia_handle,
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
        auto selene_result                 = protocol_ptr.invoke<selene::forward>(selene_handle,
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
    }

    // 特征值库加载
    bool gx_api::user_load() {

        std::array<char, 0> arr{};
        protocol_ptr.invoke<irisviel::load_databases>(
            irisivel_handle, irisviel_load_databases_param{.instance_guid = ""}, std::span<char>{arr});
        return true;
    }

    // 特征值库搜索
    faces_search_info gx_api::user_search(gx_img_api& mat, int top, float min_similarity) {
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

        auto result = protocol_ptr.invoke<irisviel::search_nf>(irisivel_handle,
            irisviel_search_nf_param{
                .instance_guid  = "",
                .feature        = faces.features[0].feature,
                .top            = top,
                .min_similarity = min_similarity,
            },
            std::span<char>{arr});
        ans.result  = result.result;


        return ans;
    }


    // 特征值库清空
    bool gx_api::user_remove_all() {

        std::array<char, 0> arr{};
        protocol_ptr.invoke<irisviel::remove_all>(
            irisivel_handle, irisviel_remove_all_param{.instance_guid = ""}, std::span<char>{arr});
        return true;
    }

    // 特征值库批量删除
    abi::vector<face_user_result> gx_api::user_remove_records(abi::vector<abi::string>& keys) {

        abi::vector<face_user_result> ans(keys.size());
        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::remove_records>(irisivel_handle,
            irisviel_remove_records_param{.instance_guid = "", .keys = keys}, std::span<char>{arr});
        for (int i = 0; i < keys.size(); i++) {
            ans[i].key     = keys[i];
            ans[i].success = 0;
            ans[i].img_buffer.clear();
            ans[i].facerectwithfaceinfo = std::nullopt;
        }
        return ans;
    }

    // 特征值库批量添加
    abi::vector<face_user_result> gx_api::user_add_records(
        abi::vector<abi::string>& keys, abi::vector<gx_img_api>& mat, bool is_clip, bool is_faceinfo) {
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

        std::array<char, 0> arr{};
        // 添加
        auto result_A = protocol_ptr.invoke<irisviel::add_records>(irisivel_handle,
            irisviel_add_records_param{.instance_guid = "", .data = faces_A_add}, std::span<char>{arr});
        // 更新
        auto result_B = protocol_ptr.invoke<irisviel::update_records>(irisivel_handle,
            irisviel_update_records_param{.instance_guid = "", .data = faces_A_update}, std::span<char>{arr});
        // TODO  AlgorithmZoo 的返回结果还没改 临时这样
        // 之后根据  ans[i].success 来获取异常状态码
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i].success > 0) {
                ans[i].success = 0;
            }
        }
        return ans;
    }

    // 特征值库批量添加
    abi::vector<face_user_result> gx_api::user_add_records(
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
        // 添加
        auto result_A = protocol_ptr.invoke<irisviel::add_records>(irisivel_handle,
            irisviel_add_records_param{.instance_guid = "", .data = faces_A_add}, std::span<char>{arr});

        // 更新
        auto result_B = protocol_ptr.invoke<irisviel::update_records>(irisivel_handle,
            irisviel_update_records_param{.instance_guid = "", .data = faces_A_update}, std::span<char>{arr});
        // TODO  AlgorithmZoo 的返回结果还没改 临时这样
        // 之后根据  ans[i].success 来获取异常状态码
        for (int i = 0; i < ans.size(); i++) {
            if (ans[i].success > 0) {
                ans[i].success = 0;
            }
        }
        return ans;
    }

    // 特征值库键值查询
    bool gx_api::user_contains_key(abi::string& key) {
        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::contains_key>(
            irisivel_handle, irisviel_contains_key_param{.instance_guid = "", .key = key}, std::span<char>{arr});
        return result.result;
    }

    // 特征值库记录总和
    std::uint64_t gx_api::user_record_count() {
        std::array<char, 0> arr{};
        auto result = protocol_ptr.invoke<irisviel::record_count>(
            irisivel_handle, irisviel_record_count_param{.instance_guid = ""}, std::span<char>{arr});
        return result.result;
    }

    // 人脸识别流程融合
    faces_integration_search_info gx_api::detect_integration(gx_img_api& mat, int top, float min_similarity) {
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

    //多人脸搜索
    abi::vector<faces_search_one_info> gx_api::detect_many_faces_integration(
        gx_img_api& mat, bool is_living, float min_similarity) {
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
            
        } 
        else {
            abi::vector<face_info> faces = detect(mat);
            if (faces.size() == 0)
                return ans;
            for (int i = 0; i < faces.size(); ++i) {
                    faces_search_one_info temp;
                temp.facerectwithfaceinfo = faces_temp[i];
                    ans.emplace_back(temp);
            }
        }

        //人脸对齐
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        auto romancia_result = protocol_ptr.invoke<romancia::alignFace>(romancia_handle,
            romancia_align_face_param{.instance_guid = "",
                .format                              = _config->_feature_config.format,
                .height                              = mat.get_rows(),
                .width                               = mat.get_cols(),
                .facerectwithfaceinfo_list           = faces_temp},
            str);
        if (romancia_result.aligned_images.size() == 0)
            return ans;

        //特征提取
        std::array<char, 0> arr{};
        faces_feature ans_temp;
        auto selene_result                 = protocol_ptr.invoke<selene::forward>(selene_handle,
            selene_forward_param{.instance_guid = "",
                                .aligned_images                 = romancia_result.aligned_images,
                                .format                         = romancia_result.format},
            std::span<char>{arr});
        selene_result.features;
        
        //多人脸搜索
        for (int i = 0; i < selene_result.features.size(); i++) {
            auto result = protocol_ptr.invoke<irisviel::search_nf>(irisivel_handle,
                irisviel_search_nf_param{
                    .instance_guid  = "",
                    .feature        = selene_result.features[i].feature,
                    .top            = 1,
                    .min_similarity = min_similarity,
                },
                std::span<char>{arr});
            if (result.result.size()>0)
                ans[i].result = std::move(result.result[0]);
        }
        return ans;
    }

    // 1:1特征值对比接口
    double gx_api::feature_comparison(gx_img_api& mat_A, gx_img_api& mat_B) {
        double ans = 0;

        abi::vector<face_info> is_mask_A = detect(mat_A);
        abi::vector<face_info> is_mask_B = detect(mat_B);
        if (is_mask_A.size() == 0 || is_mask_B.size() == 0)
            return 0;

        faces_feature faces_A = face_feature(mat_A, false);
        faces_feature faces_B = face_feature(mat_B, false);

        if (faces_A.features.size() == 0 || faces_B.features.size() == 0)
            return 0;

        abi::vector<float> x;
        abi::vector<float> y;


        x = faces_A.features[0].feature;
        y = faces_B.features[0].feature;

        if (x.size() == 0 || y.size() == 0 || x.size() != y.size())
            return 0;
        ans = Cosine_distance_AVX256(x, y);
        return ans;
    }

    //  安全生产 反光衣检测
    abi::vector<std::optional<abi::vector<clothes_info>>> gx_api::safe_production_refvest(
        gx_img_api& mat, const abi::vector<detecte_roi>& roi_list) {

        abi::vector<std::optional<abi::vector<clothes_info>>> ans;
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        for (int i = 0; i < roi_list.size(); ++i) {
            auto result = protocol_ptr.invoke<refvest::detect>(refvest_handle,
                refvest_detect_param{.instance_guid = "",
                    .channels                       = _config->_refvest_config.channels,
                    .height                         = mat.get_rows(),
                    .width                          = mat.get_cols(),
                    .roi_x                          = roi_list[i].roi_x,
                    .roi_y                          = roi_list[i].roi_y,
                    .roi_width                      = roi_list[i].roi_width,
                    .roi_height                     = roi_list[i].roi_height,
                    .format                         = _config->_refvest_config.format,
                    .params = refvest_detect_param::confidence_params{.conf_thres = _config->_refvest_config.conf_thres,
                        .iou_thres = _config->_refvest_config.iou_thres}},
                str);
            ans.emplace_back(result.detect_info);
        }
        return ans;
    }

    //  安全生产 烟雾火焰检测
    abi::vector<flame_info> gx_api::safe_production_flame(gx_img_api& mat, const abi::vector<detecte_roi>& roi_list) {
        abi::vector<flame_info> ans;
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};

        for (int i = 0; i < roi_list.size(); ++i) {
            auto result = protocol_ptr.invoke<flame::detect>(flame_handle,
                flame_detect_param{.instance_guid = "",
                    .format                       = _config->_flame_config.format,
                    .height                       = mat.get_rows(),
                    .width                        = mat.get_cols(),
                    .roi_x                        = roi_list[i].roi_x,
                    .roi_y                        = roi_list[i].roi_y,
                    .roi_width                    = roi_list[i].roi_width,
                    .roi_height                   = roi_list[i].roi_height,
                    .params = flame_detect_param::confidence_params{.conf_thres = _config->_flame_config.conf_thres,
                        .iou_thres                                              = _config->_flame_config.iou_thres}},
                str);
            ans.emplace_back(result.detect_info);
        }
        return ans;
    }

    //  安全生产 安全帽检测
    abi::vector<helmet_info> gx_api::safe_production_helmet(gx_img_api& mat, const  abi::vector<detecte_roi>& roi_list) {
        return impl_->safe_production_helmet(mat, roi_list);
        /*std::cout << "begin()\n";
        abi::vector<helmet_info> ans;
        std::span<char> str{reinterpret_cast<char*>(mat.get_data()), mat.get_data_len()};
        for (int i = 0; i < roi_list.size(); ++i) {
            auto result = protocol_ptr.invoke<helmet::detect>(helmet_handle,
                helmet_detect_param{.instance_guid = "",
                    .format                        = _config->_helemt_config.format,
                    .height                        = mat.get_rows(),
                    .width                         = mat.get_cols(),
                    .roi_x                         = roi_list[i].roi_x,
                    .roi_y                         = roi_list[i].roi_y,
                    .roi_width                     = roi_list[i].roi_width,
                    .roi_height                    = roi_list[i].roi_height,
                    .params = helmet_detect_param::confidence_params{.conf_thres = _config->_flame_config.conf_thres,
                        .iou_thres                                               = _config->_flame_config.iou_thres}},
                str);
            ans.emplace_back(result.detect_info);
        }
        std::cout << "end()\n";
        return ans;*/
    }
    /*
    template <typename T>
    bool update_config(std::mutex& mutex, std::string_view name, std::string_view key, T value) {
        //std::scoped_lock lock{mutex};
        //std::lock_guard<std::mutex> lock(mutex);
        std::cout << "begin()\n";
        sleep(5);
        try {
            nlohmann::json temp;
            if (name == "action_live.json") {
                temp = _config->_action_live_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_action_live_config);
            } else if (name == "blur.json") {
                temp = _config->_blur_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_blur_config);
            } else if (name == "detect.json") {
                temp = _config->_detect_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_detect_config);
            } else if (name == "face_user.json") {
                temp = _config->_face_user_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_face_user_config);
            } else if (name == "feature.json") {
                temp = _config->_feature_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_feature_config);
            } else if (name == "track.json") {
                temp = _config->_track_config;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_track_config);
            } else if (name == "configure_directory.json") {
                temp = _config->_configure_directory;
                if (!temp.contains(key))
                    return false;
                temp[key] = value;
                temp.get_to(_config->_configure_directory);
            } else {
                return false;
            }
            std::string path = _config->_path;
            path += name.data();
            std::ofstream(path.c_str()) << temp;
        } catch (const std::exception& ex) {
            return false;
        }
        std::cout << "end()\n";
        return true;
    }

    bool gx_api::set_config(std::string_view name, std::string_view key, int val) {
        return update_config(impl_->mutex_, name, key, val);
    }
    bool gx_api::set_config(std::string_view name, std::string_view key, float val) {
        return update_config(impl_->mutex_, name, key, val);
    }
    bool gx_api::set_config(std::string_view name, std::string_view key, abi::string val) {
        return update_config(impl_->mutex_, name, key, val);
    }
    bool gx_api::set_config(std::string_view name, std::string_view key, bool val) {
        return update_config(impl_->mutex_, name, key, val);
    }*/
} // namespace glasssix