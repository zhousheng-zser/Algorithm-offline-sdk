#pragma once
#if __has_include(<span>)
#include <span>
#endif
#include <string_view>
#include <vector>

#include <g6/abi/string.hpp>
#include <g6/abi/vector.hpp>
#include <g6/compat.hpp>

typedef unsigned char uchar;
const int IMG_2K               = 2048 * 1080;
const int IMG_4K               = 3840 * 2160;
const int IMG_Full_Aperture_4K = 4096 * 3112;

namespace glasssix {

    // 图片旋转角度枚举
    enum image_rotation_type { DEG90 = 0, DEG180 = 1, DEG270 = 2 };

    class gx_img_api {
    public:
        GX_API(GXOFFLINERECOGNITION) gx_img_api(abi::string path, int limit);
#if __has_include(<span>)
        GX_API(GXOFFLINERECOGNITION) gx_img_api(std::span<const uchar> bgr_data, int cols, int rows, int limit);
#endif
        GX_API(GXOFFLINERECOGNITION) gx_img_api(std::vector<uchar>& buffer, int limit);
        GX_API(GXOFFLINERECOGNITION) ~gx_img_api();
        GX_API(GXOFFLINERECOGNITION) gx_img_api(const gx_img_api&);
        GX_API(GXOFFLINERECOGNITION) gx_img_api(gx_img_api&&) noexcept;
        GX_API(GXOFFLINERECOGNITION) gx_img_api& operator=(const gx_img_api&);
        GX_API(GXOFFLINERECOGNITION) gx_img_api& operator=(gx_img_api&&) noexcept;
        GX_API(GXOFFLINERECOGNITION) int get_rows() const; // 获取图片高
        GX_API(GXOFFLINERECOGNITION) int get_cols() const; // 获取图片
        GX_API(GXOFFLINERECOGNITION) const uchar* get_data() const; // 获取图片data
        GX_API(GXOFFLINERECOGNITION) size_t get_data_len() const; // 获取data长度
        GX_API(GXOFFLINERECOGNITION) abi::string get_type() const; // 获取图片类型
        GX_API(GXOFFLINERECOGNITION) bool rotate(int deg); // 旋转图片
        GX_API(GXOFFLINERECOGNITION) abi::vector<uchar> cropped(int x1, int x2, int y1, int y2) const; // 裁剪人脸

    private:
        class impl;
        std::shared_ptr<impl> impl_;
    };

    class GX_API(GXOFFLINERECOGNITION) gx_config_api {
    public:
        gx_config_api();
        ~gx_config_api();
        gx_config_api(gx_config_api&&) noexcept;
        gx_config_api& operator=(gx_config_api&&) noexcept;

        int set_config(const abi::string& name, const abi::string& key, int val);
        int set_config(const abi::string& name, const abi::string& key, float val);
        int set_config(const abi::string& name, const abi::string& key, abi::string val);
        int set_config(const abi::string& name, const abi::string& key, bool val);

    private:
        class impl;
        std::unique_ptr<impl> impl_;
    };

} // namespace glasssix
