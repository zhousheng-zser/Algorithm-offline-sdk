#pragma once
#include <g6/json_extensions.hpp>

#include <span>
#include <string_view>
#include <vector>
typedef unsigned char uchar;
const int IMG_2K               = 2048 * 1080;
const int IMG_4K               = 3840 * 2160;
const int IMG_Full_Aperture_4K = 4096 * 3112;

namespace glasssix {
    
    // 图片旋转角度枚举
    enum image_rotation_type { DEG90 = 0, DEG180 = 1, DEG270 = 2 };

    class GX_API(GXOFFLINERECOGNITION) gx_img_api {
    public:
        gx_img_api(abi::string path, int limit);
        gx_img_api(std::span<const uchar> bgr_data, int cols, int rows, int limit);
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
} // namespace glasssix
