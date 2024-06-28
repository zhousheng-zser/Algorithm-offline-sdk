#include "data_time.hpp"
#include "gx_api.hpp"
#include <chrono>
#include <mutex>
#include <string>
#include <filesystem>
#include <cstdio>
#include <iostream>

namespace glasssix {


    extern void empower_Callback(void* context, std::string success, const char* message, unsigned long long  remaining_seconds);


    std::string empower_time_decode(std::string timestampStr, std::string encode_str) {
        //constexpr glasssix::zstring_view alg{U8("sm4-cbc")};
        //std::string_view key{timestampStr.data(), timestampStr.length()};
        //constexpr std::string_view iv{U8("0000000000000000")};
        //glasssix::crypto::symmetric_cipher_provider encryptor{
        //    alg, glasssix::crypto::cipher_padding_mode::pkcs7, key, iv};
        //glasssix::crypto::symmetric_cipher_provider decryptor{
        //    alg, glasssix::crypto::cipher_padding_mode::pkcs7, key, iv, false};
        //auto plaintext      = decryptor.string_from_base64(encode_str);
        //std::string ret_str = glasssix::abi::to_local_string(plaintext);
        //return ret_str;
        return {};
    }

    std::string get_time_code() {
        auto now                 = std::chrono::system_clock::now();
        auto duration            = now.time_since_epoch();
        auto timestamp           = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        std::string timestampStr = std::to_string(timestamp);
        while (timestampStr.length() < 16)
            timestampStr = "0" + timestampStr;
        return timestampStr;
    }

    std::string getSubstring(const std::string& str64, int pos_t) {
        if (pos_t < 0 || pos_t + 24 > 64)
            return "";
        std::string substring = str64.substr(pos_t, 24);
        return substring;
    }

    std::vector<std::string> find_file(std::filesystem::path folder_path) {
        std::vector<std::string> ans_list;
        for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
            if (entry.is_regular_file()) {
                std::string temp(entry.path().filename());
                ans_list.emplace_back(temp);
            }
        }
        return ans_list;
    }

    bool write_dump_img(const gx_img_api& mat, std::string key, std::string path) {
        const auto timestamp              = date_time::now();
        std::filesystem::path folder_path =path;
        std::string dump_path(path);
        std::vector<std::string> file_list = find_file(folder_path);
        for (int i = 0; i < file_list.size(); i++) {
            if (file_list[i].find(key) == 17) {
                try {
                    std::filesystem::remove(dump_path + "/" + file_list[i]);
                } catch (...) {
                }
            }
        }
        const std::string time_str = timestamp.to_string("yyyyMMddhhmmsszzz");
        return mat.write(dump_path + "/" + time_str + key);

    }
    void empower_Callback(
        void* context, std::string success, const char* message, unsigned long long remaining_seconds) {
        int T             = 3;
        long long time_ll = std::stoll(get_time_code());
        while (T--) {
            std::string time = "";
            long long temp   = time_ll;
            for (int i = 0; i < 16; i++) {
                time = std::to_string(temp % 10) + time;
                temp /= 10;
            }
            try {
                std::string ans = getSubstring(success, time_ll % 39);
                ans             = empower_time_decode(time, ans);
                if (ans == "Empower_is_True") {
                    return;
                }
            } catch (...) {
            }
            time_ll--;
        }
        std::string temp = "Error empower Fail:" + std::string{message};
        printf("%s\n", temp.c_str());
        throw std::runtime_error("Error empower Fail:" + std::string{message});
    }

}