#include "gx_api_c.hpp"

#include "g6/abi/memory.hpp"
#include "gx_api.hpp"

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

gx_api api_instance;
const auto api = &api_instance;

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
        ans = api->clear_track_history();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_detect_inplace(const std::uint8_t* mat, int rows, int cols) {
    try {
        glasssix::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols, IMG_2K);
        abi::vector<face_info> faces = api->detect(Mat_);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_track_inplace(const std::uint8_t* mat, int rows, int cols) {
    try {
        glasssix::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols, IMG_2K);
        abi::vector<face_trace_info> faces = api->track(Mat_);

        auto val = faces;
        for (int i = 0; i < faces.size(); i++)
            val[i]["trace_id"] = faces[0].trace_id;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_face_feature_inplace(const std::uint8_t* mat, int rows, int cols, bool is_clip) {
    try {
        glasssix::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols, IMG_2K);
        faces_feature faces = api->face_feature(Mat_, is_clip);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_user_search_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity) {
    try {
        glasssix::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols, IMG_2K);
        faces_search_info faces = api->user_search(Mat_, top, min_similarity);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_detect_integration_inplace(const std::uint8_t* mat, int rows, int cols, int top, float min_similarity) {
    try {
        glasssix::gx_img_api Mat_(make_buffer(mat, rows, cols), rows, cols, IMG_2K);
        faces_integration_search_info faces = api->detect_integration(Mat_, top, min_similarity);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}


char* gx_detect(char* mat_path) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        abi::vector<face_info> faces = api->detect(mat);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_track(char* mat_path) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        abi::vector<face_trace_info> faces = api->track(mat);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_face_blur(char* mat_path) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        faces_blur faces = api->face_blur(mat);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_face_action_live(int action_type, bool& action_result, char* mat_path) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        glasssix::action_live_type type = static_cast<glasssix::action_live_type>(action_type);
        face_info faces                 = api->face_action_live(type, action_result, mat);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_face_spoofing_live(char* mat_path) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        faces_spoofing faces = api->face_spoofing_live(mat);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_face_feature(char* mat_path, bool is_clip) {
    try {
        abi::string temp{mat_path};
        glasssix::gx_img_api mat(temp, IMG_2K);
        faces_feature faces = api->face_feature(mat, is_clip);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

bool gx_user_contains_key(char* key) {
    bool ans = 0;
    try {
        abi::string temp{key};
        ans = api->user_contains_key(temp);
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

bool gx_user_load() {
    bool ans = 0;
    try {
        ans = api->user_load();
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
        glasssix::gx_img_api mat(temp, IMG_2K);
        faces_search_info faces = api->user_search(mat, top, min_similarity);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

int gx_user_count() {
    int ans;
    try {
        ans = (int) api->user_record_count();
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
        ans = api->user_remove_all();
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_user_remove_records(char* keys) {
    try {

        abi::vector<abi::string> _keys;
        auto keys_temp = auto::parse(keys);
        for (int i = 0; i < keys_temp.size(); i++) {
            _keys.push_back(abi::string{keys_temp[i].get<std::string>()});
        }
        auto val  = api->user_remove_records(_keys);
        std::string result_ = val.dump();

        std::size_t size = result_.size() + 1;
        char* result     = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_user_add_records(char* data, bool is_clip, bool is_faceinfo) {
    std::string err;
    try {
        bool flag = 0;
        abi::vector<abi::string> _keys;
        abi::vector<gx_img_api> _mat;
        auto data_temp = auto::parse(data);
        for (int i = 0; i < data_temp.size(); i++) {
            try {
                _mat.push_back(gx_img_api{abi::string{data_temp[i]["imgs"].get<std::string>()}});
                _keys.push_back(abi::string{data_temp[i]["key"].get<std::string>()});

            } catch (const std::exception& ex) {
                flag = 1;
                err += ex.what() + data_temp[i]["imgs"].get<std::string>() + " "
                     + data_temp[i]["key"].get<std::string>() + "\n";
            }
        }
        auto val  = api->user_add_records(_keys, _mat, is_clip, is_faceinfo);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        if (!flag)
            set_last_error(std::string{"OK"});
        else
            set_last_error(err);
        return result;
    } catch (const std::exception& ex) {
        err += ex.what();
        set_last_error(err);
        return nullptr;
    }
}

char* gx_detect_integration(char* mat_path, int top, float min_similarity) {
    try {
        glasssix::gx_img_api mat(abi::string{mat_path}, IMG_2K);
        faces_integration_search_info faces = api->detect_integration(mat, top, min_similarity);

        auto val  = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
        return nullptr;
    }
}

double gx_feature_comparison(char* mat_A, char* mat_B) {
    double ans = 0;
    try {
        gx_img_api A(abi::string{mat_A}, IMG_2K);
        gx_img_api B(abi::string{mat_B}, IMG_2K);
        ans = api->feature_comparison(A, B);
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_safe_production_refvest(char* mat, char* data) {
    try {
        gx_img_api _mat(abi::string{mat}, IMG_2K);
        abi::vector<detecte_roi> roi_list;

        auto data_temp = auto::parse(data);
        for (int i = 0; i < data_temp.size(); i++) {
            roi_list.push_back(detecte_roi{
                data_temp[i]["roi_x"], data_temp[i]["roi_y"], data_temp[i]["roi_width"], data_temp[i]["roi_height"]});
        }

        auto val  = api->safe_production_refvest(_mat, roi_list);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_safe_production_flame(char* mat, char* data) {
    try {
        gx_img_api _mat(abi::string{mat}, IMG_2K);
        abi::vector<detecte_roi> roi_list;

        auto data_temp = auto::parse(data);
        for (int i = 0; i < data_temp.size(); i++) {
            roi_list.push_back(detecte_roi{
                data_temp[i]["roi_x"], data_temp[i]["roi_y"], data_temp[i]["roi_width"], data_temp[i]["roi_height"]});
        }

        auto val  = api->safe_production_flame(_mat, roi_list);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
    return ans;
}

char* gx_safe_production_helmet(char* mat, char* data) {
    try {
        gx_img_api _mat(abi::string{mat}, IMG_2K);
        abi::vector<detecte_roi> roi_list;

        auto data_temp = auto::parse(data);
        for (int i = 0; i < data_temp.size(); i++) {
            roi_list.push_back(detecte_roi{
                data_temp[i]["roi_x"], data_temp[i]["roi_y"], data_temp[i]["roi_width"], data_temp[i]["roi_height"]});
        }

        auto val  = api->safe_production_helmet(_mat, roi_list);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = new char[size];
        std::memcpy(result, result_.c_str(), size * sizeof(char));
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
        auto result;
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
