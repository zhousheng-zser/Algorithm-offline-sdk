#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_flame(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool flame_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        flame_config _flame_config;
    };

} // namespace glasssix