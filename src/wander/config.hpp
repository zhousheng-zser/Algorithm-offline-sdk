#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_wander(const std::string& path);
        void set_wander_limit(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool wander_is_load = false;
        bool wander_limit_is_load = false;
        std::string _path;
        configure_directory _configure_directory;
        wander_config _wander_config;
        wander_limit_config _wander_limit_config;
    };

} // namespace glasssix