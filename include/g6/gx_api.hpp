#pragma once
#include <string_view>
#include <string>
#include <vector>
#include <memory>
#include <span>
#include "compat.hpp"

typedef unsigned char uchar;
const int IMG_2K               = 2048 * 1080;
const int IMG_4K               = 3840 * 2160;
const int IMG_Full_Aperture_4K = 4096 * 3112;

namespace glasssix {

    // 图片旋转角度枚举
    enum image_rotation_type { DEG90 = 0, DEG180 = 1, DEG270 = 2 };

    class gx_img_api {
    public:
        GX_API(GXAPI) gx_img_api();
        GX_API(GXAPI) gx_img_api(std::string path, int limit);
        GX_API(GXAPI)
        gx_img_api(std::span<const uchar> bgr_data, int cols, int rows, int limit, bool ref = false);
        GX_API(GXAPI) gx_img_api(std::vector<uchar>& buffer, int limit);
        GX_API(GXAPI) gx_img_api(unsigned char* yuv_data, int cols, int rows, int limit);
        GX_API(GXAPI) ~gx_img_api();
        GX_API(GXAPI) gx_img_api(const gx_img_api&);
        GX_API(GXAPI) gx_img_api(gx_img_api&&) noexcept;
        GX_API(GXAPI) gx_img_api& operator=(const gx_img_api&);
        GX_API(GXAPI) gx_img_api& operator=(gx_img_api&&) noexcept;
        GX_API(GXAPI) int get_rows() const; // 获取图片高
        GX_API(GXAPI) int get_cols() const; // 获取图片宽
        GX_API(GXAPI) const uchar* get_data() const; // 获取图片data
        GX_API(GXAPI) size_t get_data_len() const; // 获取data长度
        GX_API(GXAPI) std::string get_type() const; // 获取图片类型
        GX_API(GXAPI) bool get_infrared_status() const; // 是否是红外图片
        GX_API(GXAPI) bool rotate(int deg); // 旋转图片
        GX_API(GXAPI) std::vector<uchar> cropped(int x1, int x2, int y1, int y2) const; // 裁剪
        GX_API(GXAPI) bool write(const std::string& path) const; // 保存图片到本地
        GX_API(GXAPI) const uchar* get_row_ptr(int val) const; // 获取图片第val行指针

    private:
        class impl;
        std::shared_ptr<impl> impl_;
    };
} // namespace glasssix
