#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_sleep(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool sleep_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        sleep_config _sleep_config;
    };

} // namespace glasssix