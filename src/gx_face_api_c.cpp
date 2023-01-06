#include "gx_face_api_c.hpp"

#include "g6/abi/memory.hpp"
#include "gx_face_api.h"

#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <psapi.h>

using namespace glasssix;

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
    char* result        = (char*) gx_alloc(size * sizeof(char));
    std::memcpy(result, result_.c_str(), size * sizeof(char));
    set_last_error(std::string{"OK"});
    return result;
}


bool gx_user_load() {
    try {
        bool ans = api->gx_user_load();
        set_last_error(std::string{"OK"});
        return ans;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_user_search(char* mat_path, int top, float min_similarity) {
    try {
        abi::string temp{mat_path};
        printf("path = %s\n", temp.c_str());
        glasssix::face::gx_img_api mat(temp);
        face::faces_search_info faces = api->gx_user_search(mat, top, min_similarity);

        json val            = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = (char*) gx_alloc(size * sizeof(char));
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

bool gx_user_clear() {
    try {
        bool ans = api->gx_user_clear();
        set_last_error(std::string{"OK"});
        return ans;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

bool gx_user_remove_all() {
    try {
        bool ans = api->gx_user_remove_all();
        set_last_error(std::string{"OK"});
        return ans;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_user_remove_records(char* keys) {
    try {

        abi::vector<abi::string> _keys;
        json keys_temp = json::parse(keys);
        for (int i = 0; i < keys_temp["keys"].size(); i++) {
            printf("keys[%d]=%s \n", i, keys_temp["keys"][i].get<std::string>().c_str());
            _keys.push_back(abi::string{keys_temp["keys"][i].get<std::string>()});
        }

        json val            = api->gx_user_remove_records(_keys);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = (char*) gx_alloc(size * sizeof(char));
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

char* gx_user_add_records(char* keys, char* mat_path) {
    std::string err;
    try {
        bool flag = 0;
        abi::vector<abi::string> _keys;
        abi::vector<face::gx_img_api> _mat;
        json keys_temp     = json::parse(keys);
        json mat_path_temp = json::parse(mat_path);
        if (keys_temp["keys"].size() != mat_path_temp["imgs"].size())
            throw source_code_aware_runtime_error(U8("Error: keys.size != mat.size"));
        for (int i = 0; i < keys_temp["keys"].size(); i++) {
            try {
                printf("mat_path[%d]=%s \n", i, mat_path_temp["imgs"][i].get<std::string>().c_str());
                _mat.push_back(face::gx_img_api{abi::string{mat_path_temp["imgs"][i].get<std::string>()}});
                _mat[i].rotate(1);
                _mat[i].rotate(3);
                _mat[i].rotate(2);
                _mat[i].rotate(2);

                printf("keys[%d]=%s \n", i, keys_temp["keys"][i].get<std::string>().c_str());
                _keys.push_back(abi::string{keys_temp["keys"][i].get<std::string>()});

            } catch (const std::exception& ex) {
                flag = 1;
                err += ex.what() + mat_path_temp["imgs"][i].get<std::string>() + " "
                     + keys_temp["keys"][i].get<std::string>() + "\n";
            }
        }
        json val            = api->gx_user_add_records(_keys, _mat);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = (char*) gx_alloc(size * sizeof(char));
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        if (!flag)
            set_last_error(std::string{"OK"});
        else
            set_last_error(err);
        return result;
    } catch (const std::exception& ex) {
        err += ex.what();
        set_last_error(err);
    }
}

char* gx_user_update_records(char* keys, char* mat_path) {
    std::string err;
    try {
        bool flag = 0;
        abi::vector<abi::string> _keys;
        abi::vector<face::gx_img_api> _mat;
        json keys_temp     = json::parse(keys);
        json mat_path_temp = json::parse(mat_path);
        if (keys_temp["keys"].size() != mat_path_temp["imgs"].size())
            throw source_code_aware_runtime_error(U8("Error: keys.size != mat.size"));
        for (int i = 0; i < keys_temp["keys"].size(); i++) {
            try {
                printf("mat_path[%d]=%s \n", i, mat_path_temp["imgs"][i].get<std::string>().c_str());
                _mat.push_back(face::gx_img_api{abi::string{mat_path_temp["imgs"][i].get<std::string>()}});

                printf("keys[%d]=%s \n", i, keys_temp["keys"][i].get<std::string>().c_str());
                _keys.push_back(abi::string{keys_temp["keys"][i].get<std::string>()});

            } catch (const std::exception& ex) {
                flag = 1;
                err += ex.what() + mat_path_temp["imgs"][i].get<std::string>() + " "
                     + keys_temp["keys"][i].get<std::string>() + "\n";
            }
        }
        json val            = api->gx_user_update_records(_keys, _mat);
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = (char*) gx_alloc(size * sizeof(char));
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        if (!flag)
            set_last_error(std::string{"OK"});
        else
            set_last_error(err);
        return result;
    } catch (const std::exception& ex) {
        err += ex.what();
        set_last_error(err);
    }
}

char* gx_detect_integration(char* mat_path, int top, float min_similarity) {
    try {
        glasssix::face::gx_img_api mat(abi::string{mat_path});
        face::faces_search_info faces = api->gx_detect_integration(mat, top, min_similarity);

        json val            = faces;
        std::string result_ = val.dump();
        std::size_t size    = result_.size() + 1;
        char* result        = (char*) gx_alloc(size * sizeof(char));
        std::memcpy(result, result_.c_str(), size * sizeof(char));
        set_last_error(std::string{"OK"});
        return result;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}

double gx_feature_comparison(char* mat_A, char* mat_B) {
    try {
        face::gx_img_api A(abi::string{mat_A});
        face::gx_img_api B(abi::string{mat_B});
        set_last_error(std::string{"OK"});
        return api->gx_feature_comparison(A, B);
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
}


bool gx_free(void* ptr, size_t size) {
    try {
        gx_dealloc(ptr, size);
        set_last_error(std::string{"OK"});
        return true;
    } catch (const std::exception& ex) {
        std::string err = ex.what();
        set_last_error(err);
    }
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

float get_memory_usage_info() {
    HANDLE handle = GetCurrentProcess();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
    float memoryUsage_M = pmc.WorkingSetSize / (1024.0 * 1024.0);
    float memoryUsage_K = pmc.WorkingSetSize / 1024.0;

    std::cout << std::fixed << std::setprecision(2) << "Memory = " << memoryUsage_K << "K " << memoryUsage_M << "M"
              << std::endl;
    return memoryUsage_K;
}
