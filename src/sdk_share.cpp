#include "sdk_share.hpp"
namespace glasssix {
    config* _config                             = nullptr;
    bool empower_warning_flag                   = false;
    algo_irisviel_ptr* thread_algo_irisviel_ptr = nullptr;
    std::unordered_map<std::thread::id, algo_ptr*> all_thread_algo_ptr;
    thread_pool* pool = nullptr;

    void empower_Callback(void* context, std::string success, const char* message, std::int64_t remaining_seconds) {
        int T             = 3;
        long long time_ll = std::stoll(get_time_code());
        while (T--) {
            std::string time = glasssix::format(U8("{:016}"), time_ll);
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
        printf("%s\n",temp.c_str() );
        throw source_code_aware_runtime_error("Error empower Fail:" + std::string{message} );
    }

    std::string empower_time_decode(std::string timestampStr, std::string encode_str) {
        constexpr glasssix::zstring_view alg{U8("sm4-cbc")};
        std::string_view key{timestampStr.data(), timestampStr.length()};
        constexpr std::string_view iv{U8("0000000000000000")};
        glasssix::crypto::symmetric_cipher_provider decryptor{
            alg, glasssix::crypto::cipher_padding_mode::pkcs7, key, iv, false};
        auto plaintext      = decryptor.string_from_base64(encode_str);
        std::string ret_str = glasssix::abi::to_local_string(plaintext);
        return ret_str;
    }

    std::string get_time_code() {
        auto now                 = std::chrono::system_clock::now();
        auto duration            = now.time_since_epoch();
        auto timestamp           = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        std::string timestampStr = std::to_string(timestamp);
        return glasssix::format(U8("{:016}"), timestamp);
    }


    std::string getSubstring(const std::string& str64, int pos_t) {
        if (pos_t < 0 || pos_t + 24 > 64)
            return "";
        std::string substring = str64.substr(pos_t, 24);
        return substring;
    }
} // namespace glasssix