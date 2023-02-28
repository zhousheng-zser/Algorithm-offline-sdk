#include "gx_face_api_c.hpp"

#include "g6/abi/memory.hpp"
#include "gx_face_api.h"

#define NOMINMAX
#include <iostream>

using namespace glasssix;

namespace {
    constexpr auto align_number(std::uint32_t size, std::uint32_t align) noexcept {
        return (((size) + (align) -1) & ~((align) -1));
    }

    constexpr auto make_buffer(const std::uint8_t* buffer, int rows, int cols) noexcept {
        return std::span<const std::uint8_t>{buffer, align_number(static_cast<std::uint32_t>(cols), 4) * rows * 3};
    }
} // namespace

face::gx_face_api* api = new face::gx_face_api();


auto& get_last_error_storage() {
    struct foo {
        std::string what{"OK"};
    };
    thread_local foo storage;
    return storage;
}

void set_last_error(std::string what) {
    auto&& storage = get_last_error_storage();
    storage.what   = what;
}

char* get_last_error() {
    std::string result_ = get_last_error_storage().what;
    std::size_t size    = result_.size() + 1;
    char* result        = new char[size];
    std::memcpy(result, result_.c_str(), size * sizeof(char));
    set_last_error(std::string{"OK"});
    return result;
}


bool gx_clear_track_history() {
    bool ans = 0;
    try {
        ans = api->gx_clear_track_history();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_detect_inplace(const std::uint8_t* mat, int rows, int cols) {
    clock_t be, ed;
    be = clock();
    try {
        glasssix::face::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols);
        printf("%d %d %lld \n", Mat_.get_rows(), Mat_.get_cols(), Mat_.get_data_len());

        abi::vector<face::face_info> faces = api->gx_detect(Mat_);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        ed = clock();
        printf("------------------time= %.4f\n", 1.0 * (ed - be) / CLOCKS_PER_SEC);
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_track_inplace(const std::uint8_t* mat, int rows, int cols) {
    clock_t be, ed;
    be = clock();
    try {
        glasssix::face::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols);
        abi::vector<face::face_trace_info> faces = api->gx_track(Mat_);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        ed = clock();
        printf("------------------time= %.4f\n", 1.0 * (ed - be) / CLOCKS_PER_SEC);
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_face_feature_inplace(const std::uint8_t* mat, int rows, int cols, bool is_clip) {
    clock_t be, ed;
    be = clock();
    try {
        glasssix::face::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols);
        abi::vector<face::faces_feature> faces = api->gx_face_feature(Mat_, is_clip);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        ed = clock();
        printf("------------------time= %.4f\n", 1.0 * (ed - be) / CLOCKS_PER_SEC);
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_user_search_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity) {
    clock_t be, ed;
    be = clock();
    try {
        glasssix::face::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols);
        face::faces_search_info faces = api->gx_user_search(Mat_, top, min_similarity);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        ed = clock();
        printf("------------------time= %.4f\n", 1.0 * (ed - be) / CLOCKS_PER_SEC);
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_detect_integration_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity) {
    clock_t be, ed;
    be = clock();
    try {
        glasssix::face::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols);
        face::faces_integration_search_info faces = api->gx_detect_integration(Mat_, top, min_similarity);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        ed = clock();
        printf("------------------time= %.4f\n", 1.0 * (ed - be) / CLOCKS_PER_SEC);
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}


bool gx_user_load() {
    bool ans = 0;
    try {
        ans = api->gx_user_load();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_user_search(char* mat_path, int top, float min_similarity) {
    try {
        abi::string temp{mat_path};
        glasssix::face::gx_img_api mat(temp);
        face::faces_search_info faces = api->gx_user_search(mat, top, min_similarity);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

int gx_user_count() {
    int ans;
    try {
        ans = (int) api->gx_user_record_count();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}


bool gx_user_remove_all() {
    bool ans;
    try {
        ans = api->gx_user_remove_all();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_user_remove_records(char* keys) {
    char* result = NULL;
    try {

        abi::vector<abi::string> _keys;
        nlohmann::json keys_temp = nlohmann::json::parse(keys);
        for (int i = 0; i < keys_temp.size(); i++) {
            _keys.push_back(abi::string{keys_temp[i].get<std::string>()});
        }
        nlohmann::json val  = api->gx_user_remove_records(_keys);
        std::string result_ = val.dump();

        std::size_t size = result_.size() + 1;
        char* result     = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return result;
}

char* gx_user_add_records(char* data, bool is_clip, bool is_faceinfo) {
    std::string err;
    char* result = NULL;
    try {
        bool flag = 0;
        abi::vector<abi::string> _keys;
        abi::vector<face::gx_img_api> _mat;
        nlohmann::json data_temp = nlohmann::json::parse(data);
        for (int i = 0; i < data_temp.size(); i++) {
            try {
                _mat.push_back(face::gx_img_api{abi::string{data_temp[i]["imgs"].get<std::string>()}});
                _keys.push_back(abi::string{data_temp[i]["key"].get<std::string>()});

            } catch (const std::exception& ex) {
                flag = 1;
                err += ex.what() + data_temp[i]["imgs"].get<std::string>() + " "
                     + data_temp[i]["key"].get<std::string>() + "\n";
            }
        }
        nlohmann::json val  = api->gx_user_add_records(_keys, _mat, is_clip, is_faceinfo);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        if (!flag)
            set_last_error(std::string{"OK"});
        else
            set_last_error(err);
    } catch (const std::exception& ex) {
        err += ex.what();
        set_last_error(err);
    }
    return result;
}

char* gx_detect_integration(char* mat_path, int top, float min_similarity) {
    try {
        glasssix::face::gx_img_api mat(abi::string{mat_path});
        face::faces_integration_search_info faces = api->gx_detect_integration(mat, top, min_similarity);

        nlohmann::json val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

double gx_feature_comparison(char* mat_A, char* mat_B) {
    double ans = 0;
    try {
        face::gx_img_api A(abi::string{mat_A});
        face::gx_img_api B(abi::string{mat_B});
        ans = api->gx_feature_comparison(A, B);
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

bool gx_free(char* ptr) {
    try {
        delete[] ptr;
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return true;
}

void printf_demo(char x, char* y) {
    printf("char  = %c\n", x);
    printf("char* = %s\n", y);
}

int get_disk_keys_num(char* path) {
    int ans = 0;
    for (int i = 0; i < 4096; i++) {
        std::string name = path;
        name += "/" + std::to_string(i) + ".json";
        std::ifstream fp;
        fp.open(name, std::ios::binary);
        std::string result_str;
        nlohmann::json result;
        while (std::getline(fp, result_str)) {
            if (result_str.length() == 0) {
                break;
            }
            result.clear();
            ans++;
        }
        fp.close();
    }
    return ans / 16;
}
