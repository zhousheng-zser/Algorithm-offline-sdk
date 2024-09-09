#include <g6/gx_api.hpp>
#include <opencv2/opencv.hpp>
#include <fstream>
#include <cstring>
namespace glasssix {
    namespace {
        std::mutex mutex_;
    }
    class gx_img_api::impl {
    public:
        impl(std::string path, int limit) : img{cv::imread(path.c_str())} {
            if (img.empty()) {
                std::runtime_error{std::string("Error: Could not load image")};
            }
            uchar val[105];
            memset(val, 0, sizeof(val));
            std::ifstream in_file(path.c_str(), std::ios::in | std::ios::binary);
            in_file.read((char*) &val, 10);
            type = check_type(val, 10);
            if (type == "") {
                throw std::runtime_error{std::string("Error: The picture is not in the right format")};
            }
            if (img.cols * img.rows > limit) {
                img.release();
                throw std::runtime_error{std::string("Error: The picture has more than maximun limit pixels")};
            }
            data_len    = 1llu * img.channels() * img.cols * img.rows;
            is_infrared = -1;
        }
        impl(std::vector<uchar>& buffer, int limit) {
            type = check_type(buffer, 10);
            if (type == "") {
                throw std::runtime_error{std::string("Error: The picture is not in the right format")};
            }
            img = cv::imdecode(buffer, cv::IMREAD_COLOR);
            if (img.cols * img.rows > limit) {
                img.release();
                throw std::runtime_error{std::string("Error: The picture has more than maximun limit pixels")};
            }
            data_len    = 1llu * img.channels() * img.cols * img.rows;
            is_infrared = -1;
        }
        impl(unsigned char* yuv_data, int rows, int cols, int limit) {
            cv::Mat yuv_img(rows * 3 / 2, cols, CV_8UC1, yuv_data);
            img = cv::Mat(rows, cols, CV_8UC3).clone();
            cvtColor(yuv_img, img, cv::COLOR_YUV2BGR_NV12);

            if (img.cols * img.rows > limit) {
                img.release();
                throw std::runtime_error{std::string("Error: The picture has more than maximun limit pixels")};
            }
            data_len    = 1llu * img.channels() * img.cols * img.rows;
            is_infrared = -1;
        }
        impl(std::span<const uchar> bgr_data, int rows, int cols, int limit, bool ref) {
            if (!ref) {
                img = cv::Mat(rows, cols, CV_8UC3);
                std::memcpy(img.data, bgr_data.data(), bgr_data.size());
            } else {
                img = cv::Mat(rows, cols, CV_8UC3, const_cast<unsigned char*>(bgr_data.data()));
            }
            if (img.empty()) {
                throw std::runtime_error{std::string("Error: Could not load image")};
            }
            if (img.cols * img.rows > limit) {
                img.release();
                throw std::runtime_error{std::string("Error: The picture has more than maximun limit pixels")};
            }
            data_len    = 1llu * img.channels() * img.cols * img.rows;
            is_infrared = -1;
        }
        impl() {}
        ~impl() {}

        std::string check_type(std::vector<uchar>& val, size_t len) {
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
        std::string check_type(uchar* val, size_t len) {
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
        int check_infrared() {
            cv::Mat hsv_frame;
            cv::cvtColor(img, hsv_frame, cv::COLOR_BGR2HSV);
            double sum = 0;
            for (int i = 0; i < hsv_frame.rows; ++i) {
                for (int j = 0; j < hsv_frame.cols; ++j) {
                    // 访问S通道的值
                    sum += hsv_frame.at<cv::Vec3b>(i, j)[1];
                }
            }
            sum /= (hsv_frame.rows * hsv_frame.cols);
            if (sum < 4)
                return 1;
            return 0;
        }
        int is_infrared; // 判断是否为红外图像
        cv::Mat img;
        size_t data_len;
        std::string type;
    };
    gx_img_api::gx_img_api(std::string path, int limit) : impl_{std::make_shared<impl>(path, limit)} {}
    gx_img_api::gx_img_api(std::vector<uchar>& buffer, int limit) : impl_{std::make_shared<impl>(buffer, limit)} {}
    gx_img_api::gx_img_api(unsigned char* yuv_data, int cols, int rows, int limit) // 对外接口是先宽再高
        : impl_{std::make_shared<impl>(yuv_data, rows, cols, limit)} {} // opencv 构造是先高再宽
    gx_img_api::gx_img_api(
        std::span<const uchar> bgr_data, int cols, int rows, int limit, bool ref) // 对外接口是先宽再高
        : impl_{std::make_shared<impl>(bgr_data, rows, cols, limit, ref)} {} // opencv 构造是先高再宽
    gx_img_api::gx_img_api() : impl_{std::make_shared<impl>()} {}
    gx_img_api::~gx_img_api() {}
    gx_img_api::gx_img_api(const gx_img_api&)                = default;
    gx_img_api::gx_img_api(gx_img_api&&) noexcept            = default;
    gx_img_api& gx_img_api::operator=(const gx_img_api&)     = default;
    gx_img_api& gx_img_api::operator=(gx_img_api&&) noexcept = default;
    int gx_img_api::get_rows() const {
        return impl_->img.rows;
    }
    int gx_img_api::get_cols() const {
        return impl_->img.cols;
    }
    const uchar* gx_img_api::get_data() const {
        return impl_->img.data;
    }
    size_t gx_img_api::get_data_len() const {
        return impl_->data_len;
    }
    std::string gx_img_api::get_type() const {
        return impl_->type;
    }
    bool gx_img_api::get_infrared_status() const {
        if (impl_->is_infrared == -1)
            impl_->is_infrared = impl_->check_infrared();
        return impl_->is_infrared;
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
    std::vector<uchar> gx_img_api::cropped(int x1, int x2, int y1, int y2) const {

        x1 = std::max(0, x1);
        y1 = std::max(0, y1);
        x2 = std::min(impl_->img.cols, x2);
        y2 = std::min(impl_->img.rows, y2);
        cv::Mat cropped_face =
            impl_->img(cv::Range(std::min(y1, y2), std::max(y1, y2)), cv::Range(std::min(x1, x2), std::max(x1, x2)))
                .clone();
        std::vector<uchar> buffer(3LL * cropped_face.cols * cropped_face.rows);
        cv::imencode(".jpg", cropped_face, buffer);
        std::vector<uchar> ans(buffer.begin(), buffer.end());
        return ans;
    }
    bool gx_img_api::write(const std::string& path) const {
        return cv::imwrite(path, impl_->img);
    }
    const uchar* gx_img_api::get_row_ptr(int val) const {
        return impl_->img.ptr<uchar>(val);
    }
} // namespace glasssix