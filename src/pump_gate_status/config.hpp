#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_pump_gate_status(const std::string& path);
        void set_thread_pool_num(const std::string& path);
        int thread_pool_val = 1;
        bool pump_gate_status_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        pump_gate_status_config _pump_gate_status_config;
    };

} // namespace glasssix