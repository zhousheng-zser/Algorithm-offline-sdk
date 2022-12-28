#include "g6/compat.hpp"

extern "C" {

GX_API(GXFACEAPIC) bool gx_user_load();
GX_API(GXFACEAPIC) char* gx_user_search(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) bool gx_user_clear();
GX_API(GXFACEAPIC) bool gx_user_remove_all();
GX_API(GXFACEAPIC) bool gx_user_remove_records(char* keys);
GX_API(GXFACEAPIC) bool* gx_user_add_records(char* keys, char* mat_path);
GX_API(GXFACEAPIC) bool* gx_user_update_records(char* keys, char* mat_path);
GX_API(GXFACEAPIC) char* gx_detect_integration(char* mat_path, int top, float min_similarity);
GX_API(GXFACEAPIC) double gx_feature_comparison(char* mat_A, char* mat_B);
GX_API(GXFACEAPIC) bool gx_free(void* ptr, size_t size);
GX_API(GXFACEAPIC) void printf_demo(char x, char* y);
// GX_API(GXFACEAPIC) int get_last_error(const char** what);
}
