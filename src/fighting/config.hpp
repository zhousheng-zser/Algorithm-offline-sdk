#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_fighting(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool fighting_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        fighting_config _fighting_config;
    };

} // namespace glasssix