#pragma once

#include <string_view>

namespace glasssix {
    enum class video_coding_type { avc, hevc, mpeg4 };

    enum class demuxing_media_type {
        unknown = -1,
        video,
        audio,
        data,
        subtitle,
        attachment,
        nb
    };

    enum class pixel_format_type {
        yuv420sp, /* YYYY... UV... (NV12)     */

        yuv420sp_10bit,
        yuv422sp, // YYYY... UVUV... (NV16)
        yuv422sp_10bit, // < Not part of ABI
        yuv420p, // YYYY... U...V...  (I420)
        yuv420sp_vu, // YYYY... VUVUVU... (NV21)
        yuv422p, // YYYY... UU...VV...(422P)
        yuv422sp_vu, // YYYY... VUVUVU... (NV61)
        yuv422_yuyv, // YUYVYUYV... (YUY2)
        yuv422_yvyu, // YVYUYVYU... (YVY2)
        yuv422_uyvy, // UYVYUYVY... (UYVY)
        yuv422_vyuy, // VYUYVYUY... (VYUY)
        yuv400, // YYYY...
        yuv440sp, // YYYY... UVUV...
        yuv411sp, // YYYY... UV...
        yuv444sp, // YYYY... UVUVUVUV...
        yuv444p, // YYYY... UUUU... VVVV...

        rgb565 = 65536, // 16-bit RGB
        bgr565, // 16-bit RGB
        rgb555, // 15-bit RGB
        bgr555, // 15-bit RGB
        rgb444, // 12-bit RGB
        bgr444, // 12-bit RGB
        rgb888, // 24-bit RGB
        bgr888, // 24-bit RGB
        rgb101010, // 30-bit RGB
        bgr101010, // 30-bit RGB
        argb8888, // 32-bit RGB
        abgr8888, // 32-bit RGB
        bgra8888, // 32-bit RGB
        rgba8888 // 32-bit RGB
    };
} // namespace glasssix
