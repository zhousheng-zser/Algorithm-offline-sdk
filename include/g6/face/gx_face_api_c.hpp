
#include "g6/compat.hpp"
extern "C" {

GX_API(GXFACEAPIC) void gx_user_load(bool is_mask = false);

GX_API(GXFACEAPIC) char* gx_user_search(char* mat_path, int top = 1, float min_similarity = 0.4, bool is_mask = false);

GX_API(GXFACEAPIC) void gx_user_clear(bool is_mask = false);

GX_API(GXFACEAPIC) void gx_user_remove_all(bool is_mask = false);

GX_API(GXFACEAPIC) void gx_user_remove_records(char** keys, int key_number, bool is_mask = false);

GX_API(GXFACEAPIC) bool* gx_user_add_records(char** keys, int key_number, char** mat_path, bool is_mask = false);

GX_API(GXFACEAPIC) bool* gx_user_update_records(char** keys, int key_number, char** mat_path, bool is_mask = false);

GX_API(GXFACEAPIC)
char* gx_detect_integration(char* mat_path, int top = 1, float min_similarity = 0.4, bool is_mask = false);

GX_API(GXFACEAPIC) double gx_feature_comparison(char* mat_A, char* mat_B);

GX_API(GXFACEAPIC) void gx_free(void* ptr, size_t size);

}
