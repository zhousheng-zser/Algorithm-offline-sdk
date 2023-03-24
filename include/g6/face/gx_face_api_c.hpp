#include "g6/compat.hpp"

#include <cstdint>

extern "C" {
GX_API(GXFACEAPIC) bool gx_clear_track_history();
GX_API(GXFACEAPIC) char* gx_detect_inplace(const std::uint8_t* mat, int rows, int cols);
GX_API(GXFACEAPIC) char* gx_track_inplace(const std::uint8_t* mat, int rows, int cols);
GX_API(GXFACEAPIC) char* gx_face_feature_inplace(const std::uint8_t* mat, int rows, int cols, bool is_clip);
GX_API(GXFACEAPIC)
char* gx_user_search_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity);
GX_API(GXFACEAPIC)
char* gx_detect_integration_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity);

GX_API(GXFACEAPIC) char* gx_detect(char* mat_path);
GX_API(GXFACEAPIC) char* gx_track(char* mat_path);
GX_API(GXFACEAPIC) char* gx_face_blur(char* mat_path);
GX_API(GXFACEAPIC) char* gx_face_action_live(int action_type, bool& action_result, char* mat_path);
GX_API(GXFACEAPIC) char* gx_face_spoofing_live(char* mat_path);
GX_API(GXFACEAPIC) char* gx_face_feature(char* mat_path, bool is_clip);
GX_API(GXFACEAPIC) bool gx_user_contains_key(char* key);
GX_API(GXFACEAPIC) bool gx_user_load();
GX_API(GXFACEAPIC) char* gx_user_search(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) int gx_user_count();
GX_API(GXFACEAPIC) bool gx_user_remove_all();
GX_API(GXFACEAPIC) char* gx_user_remove_records(char* keys);
GX_API(GXFACEAPIC) char* gx_user_add_records(char* data, bool is_clip, bool is_faceinfo);
GX_API(GXFACEAPIC) char* gx_detect_integration(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) double gx_feature_comparison(char* mat_A, char* mat_B);
GX_API(GXFACEAPIC) bool gx_free(char* ptr);
GX_API(GXFACEAPIC) void printf_demo(char x, char* y); // 到时会删
GX_API(GXFACEAPIC) int get_disk_keys_num(char* path); // 到时会删
GX_API(GXFACEAPIC) char* get_last_error(); // C接口捕获异常
}
