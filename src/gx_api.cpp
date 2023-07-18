#include "gx_api.hpp"

#include "sdk_share.hpp"

#include <g6/error_extensions.hpp>

#include <opencv2/opencv.hpp>
namespace glasssix {
    namespace {
        std::mutex mutex_;
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
            if (img.cols * img.rows > limit) {
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
#if __has_include(<span>)
        impl(std::span<const uchar> bgr_data, int rows, int cols, int limit) : img(rows, cols, CV_8UC3) {
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
#endif
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
    gx_img_api::gx_img_api(abi::string path, int limit) : impl_{std::make_unique<impl>(path, limit)} {}
#if __has_include(<span>)
    gx_img_api::gx_img_api(std::vector<uchar>& buffer, int limit) : impl_{std::make_unique<impl>(buffer, limit)} {}
#endif
    gx_img_api::gx_img_api(std::span<const uchar> bgr_data, int cols, int rows, int limit) // 对外接口是先宽再高
        : impl_{std::make_unique<impl>(bgr_data, rows, cols, limit)} {} // opencv 构造是先高再宽
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


    class gx_config_api::impl {
    public:
        impl() {}
        ~impl() {}

        nlohmann::json init() {
            nlohmann::json name_config;
            name_config["action_live.json"]         = _config->_action_live_config;
            name_config["blur.json"]                = _config->_blur_config;
            name_config["configure_directory.json"] = _config->_configure_directory;
            name_config["detect.json"]              = _config->_detect_config;
            name_config["face_user.json"]           = _config->_face_user_config;
            name_config["feature.json"]             = _config->_feature_config;
            name_config["flame.json"]               = _config->_flame_config;
            name_config["helmet.json"]              = _config->_helmet_config;
            name_config["refvest.json"]             = _config->_refvest_config;
            name_config["track.json"]               = _config->_track_config;
            name_config["sleep.json"]               = _config->_sleep_config;
            name_config["smoke.json"]               = _config->_smoke_config;
            name_config["leavepost.json"]           = _config->_leavepost_config;
            name_config["playphone.json"]           = _config->_playphone_config;
            name_config["onphone.json"]             = _config->_onphone_config;
            name_config["workcloth.json"]             = _config->_workcloth_config;
            return name_config;
        }


        template <typename T>
        int update_config(const abi::string& name, const abi::string& key, T value) {
            std::scoped_lock lock{mutex_};
            try {
                nlohmann::json temp;
                nlohmann::json name_config;
                // 没有config指针就报错
                // 有config指针没这个文件也报错(没有这个文件或者没有这个算法对象或者没有这个键值),这个文件不属于项目
                if (_config == nullptr)
                    return -1; // 文件对应的算法未构建实例
                name_config = init();
                if (!name_config.contains(std::string{name}))
                    return -2; // 这个文件不属于项目
                temp = name_config[std::string{name}];
                if (!temp.contains(std::string{key}))
                    return -4; // 没有这个键值

                temp[std::string{key}] = value;
                abi::string path       = _config->_path + "/" + name;
                std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);

                if (name == "action_live.json" && _config->action_live_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_action_live_config);
                } else if (name == "blur.json" && _config->blur_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_blur_config);
                } else if (name == "detect.json" && _config->detect_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_detect_config);
                } else if (name == "face_user.json" && _config->face_user_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_face_user_config);
                } else if (name == "feature.json" && _config->feature_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_feature_config);
                } else if (name == "track.json" && _config->track_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_track_config);
                } else if (name == "configure_directory.json" && _config->configure_directory_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_configure_directory);
                } else if (name == "flame.json" && _config->flame_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_flame_config);
                } else if (name == "helmet.json" && _config->helmet_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_helmet_config);
                } else if (name == "refvest.json" && _config->refvest_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_refvest_config);
                } else if (name == "sleep.json" && _config->sleep_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_sleep_config);
                } else if (name == "smoke.json" && _config->smoke_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_smoke_config);
                } else if (name == "leavepost.json" && _config->leavepost_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_leavepost_config);
                } else if (name == "playphone.json" && _config->playphone_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_playphone_config);
                } else if (name == "onphone.json" && _config->onphone_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_onphone_config);
                } else if (name == "workcloth.json" && _config->workcloth_is_load) {
                    std::ofstream(path.c_str(), std::ios::trunc) << temp.dump(4);
                    temp.get_to(_config->_workcloth_config);
                } else {
                    return -1; // 文件对应的算法未构建实例
                }
            } catch (const std::exception& ex) {
                std::cout << ex.what() << "\n";
                return -3; // 写文件失败 或者 类型错误
            }
            return 0;
        }
    };

    gx_config_api::gx_config_api() {}
    gx_config_api::~gx_config_api() {}
    gx_config_api::gx_config_api(gx_config_api&&) noexcept            = default;
    gx_config_api& gx_config_api::operator=(gx_config_api&&) noexcept = default;
    int gx_config_api::set_config(const abi::string& name, const abi::string& key, int val) {
        return impl_->update_config(name, key, val);
    }
    int gx_config_api::set_config(const abi::string& name, const abi::string& key, float val) {
        return impl_->update_config(name, key, val);
    }
    int gx_config_api::set_config(const abi::string& name, const abi::string& key, abi::string val) {
        return impl_->update_config(name, key, val);
    }
    int gx_config_api::set_config(const abi::string& name, const abi::string& key, bool val) {
        return impl_->update_config(name, key, val);
    }

} // namespace glasssix