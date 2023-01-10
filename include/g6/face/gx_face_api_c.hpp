#include "g6/compat.hpp"

extern "C" {

GX_API(GXFACEAPIC) bool gx_user_load();
GX_API(GXFACEAPIC) char* gx_user_search(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) int gx_user_count();
GX_API(GXFACEAPIC) bool gx_user_clear();
GX_API(GXFACEAPIC) bool gx_user_remove_all();
GX_API(GXFACEAPIC) char* gx_user_remove_records(char* keys);
GX_API(GXFACEAPIC) char* gx_user_add_records(char* data, bool is_clip, bool is_faceinfo);
//GX_API(GXFACEAPIC) char* gx_user_update_records(char* keys, char* mat_path);
GX_API(GXFACEAPIC) char* gx_detect_integration(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) double gx_feature_comparison(char* mat_A, char* mat_B);
GX_API(GXFACEAPIC) bool gx_free(void* ptr, size_t size);
GX_API(GXFACEAPIC) void printf_demo(char x, char* y); //到时会删
GX_API(GXFACEAPIC) int get_disk_keys_num(char* path); //到时会删
GX_API(GXFACEAPIC) char* get_last_error(); // C接口捕获异常
GX_API(GXFACEAPIC) float get_memory_usage_info();
}
