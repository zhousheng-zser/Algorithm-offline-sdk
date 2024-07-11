#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_helmet(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool helmet_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        helmet_config _helmet_config;
    };

} // namespace glasssix