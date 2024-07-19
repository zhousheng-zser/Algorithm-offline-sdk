#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_vehicle(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool vehicle_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        vehicle_config _vehicle_config;
    };

} // namespace glasssix