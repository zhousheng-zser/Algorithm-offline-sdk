#include "../protocols_reflection.hpp"
#include "struct_reflection.hpp"
namespace glasssix {
    class config {
    public:
        config();
        config(const std::string& path);
        void set_configure_directory(std::string& path);
        void set_camera_occlusion(const std::string& path);
        int thread_pool_val = 1;
        bool camera_occlusion_is_load   = false;
        std::string _path;
        configure_directory _configure_directory;
        camera_occlusion_config _camera_occlusion_config;
    };

} // namespace glasssix