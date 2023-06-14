#include <g6/cryptography.hpp>
#include <g6/char8_t_remediation.hpp>
#include <g6/detail/cipher.hpp>
#include <chrono>


std::string empower_time_decode(std::string timestampStr, std::string encode_str) {
    constexpr std::string_view alg{U8("sm4-cbc")};
    std::string_view key{timestampStr.data(), timestampStr.length()};
    constexpr std::string_view iv{U8("0000000000000000")};
    glasssix::cipher_provider decryptor{alg, glasssix::cipher_padding_mode::pkcs7, key, iv, false};
    auto plaintext      = decryptor.process_as_string_from_base64(encode_str);
    std::string ret_str = glasssix::abi::to_local_string(plaintext);
    return ret_str;
}

std::string get_time_code() {
    auto now       = std::chrono::system_clock::now();
    auto duration  = now.time_since_epoch();
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
    std::string timestampStr = std::to_string(timestamp);
    return glasssix::format(U8("{:016}"), timestamp);
}
