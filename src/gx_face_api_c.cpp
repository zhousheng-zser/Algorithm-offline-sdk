#include "gx_face_api_c.hpp"

#include "g6/abi/memory.hpp"
#include "gx_face_api.h"

using namespace glasssix;

face::gx_face_api* api = new face::gx_face_api();


void gx_user_load(bool is_mask) {
    api->gx_user_load(is_mask);
}

char* gx_user_search(char* mat_path, int top, float min_similarity, bool is_mask) {
    glasssix::face::gx_img_api mat(abi::string{mat_path});
    face::faces_search_info faces = api->gx_user_search(mat, top, min_similarity, is_mask);

    json val            = faces;
    std::string result_ = val.dump();
    std::size_t size    = result_.size() + 1;
    char* result        = (char*) gx_alloc(size * sizeof(char));
    std::memcpy(result, result_.c_str(), size * sizeof(char));
    return result;
}

void gx_user_clear(bool is_mask) {
    api->gx_user_clear(is_mask);
}

void gx_user_remove_all(bool is_mask) {
    api->gx_user_remove_all(is_mask);
}

void gx_user_remove_records(char** keys, int key_number, bool is_mask) {
    abi::vector<abi::string> _keys;
    for (int i = 0; i < key_number; i++)
        _keys.push_back(abi::string{keys[i]});

    api->gx_user_remove_records(_keys, is_mask);
}

bool* gx_user_add_records(char** keys, int key_number, char** mat_path, bool is_mask) {
    abi::vector<bool> result_;
    abi::vector<abi::string> _keys;
    for (int i = 0; i < key_number; i++)
        _keys.push_back(abi::string{keys[i]});
    abi::vector<face::gx_img_api> _mat;
    for (int i = 0; i < key_number; i++)
        _mat.push_back(face::gx_img_api{abi::string{mat_path[i]}});
    result_ = api->gx_user_add_records(_keys, _mat, is_mask);

    std::size_t size = result_.size();
    bool* result     = (bool*) gx_alloc(size * sizeof(bool));
    for (int i = 0; i < result_.size(); i++)
        result[i] = result_[i];
    return result;
}

bool* gx_user_update_records(char** keys, int key_number, char** mat_path, bool is_mask) {
    abi::vector<bool> result_;
    abi::vector<abi::string> _keys;
    for (int i = 0; i < key_number; i++)
        _keys.push_back(abi::string{keys[i]});
    abi::vector<face::gx_img_api> _mat;
    for (int i = 0; i < key_number; i++)
        _mat.push_back(face::gx_img_api{abi::string{mat_path[i]}});
    result_ = api->gx_user_update_records(_keys, _mat, is_mask);

    std::size_t size = result_.size();
    bool* result     = (bool*) gx_alloc(size * sizeof(bool));
    for (int i = 0; i < result_.size(); i++)
        result[i] = result_[i];
    return result;
}

char* gx_detect_integration(char* mat_path, int top, float min_similarity, bool is_mask) {

    glasssix::face::gx_img_api mat(abi::string{mat_path});
    face::faces_search_info faces = api->gx_detect_integration(mat, top, min_similarity, is_mask);

    json val            = faces;
    std::string result_ = val.dump();
    std::size_t size    = result_.size() + 1;
    char* result        = (char*) gx_alloc(size * sizeof(char));
    std::memcpy(result, result_.c_str(), size * sizeof(char));
    return result;
}

double gx_feature_comparison(char* mat_A, char* mat_B) {
    face::gx_img_api A(abi::string{mat_A});
    face::gx_img_api B(abi::string{mat_B});
    return api->gx_feature_comparison(A, B);
}


void gx_free(void* ptr, size_t size) {
    gx_dealloc(ptr, size);
}
