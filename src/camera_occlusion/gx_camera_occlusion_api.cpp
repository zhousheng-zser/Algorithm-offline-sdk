#include "gx_camera_occlusion_api.hpp"
#include "../sdk_share.hpp"
#include <unordered_map>
namespace glasssix {
    
    class algo_ptr {
    public:
        algo_ptr() {
            try {

            } catch (const std::exception& ex) {
                throw std::runtime_error{ex.what()};
            }
        }
        ~algo_ptr() {
        }
    };

    std::unordered_map<std::thread::id, algo_ptr*> thread_algo_ptr;
    gx_camera_occlusion_api::gx_camera_occlusion_api() : impl_{std::make_unique<impl>()} {}
    gx_camera_occlusion_api::gx_camera_occlusion_api(const std::string& config_path) : impl_{std::make_unique<impl>(config_path)} {}
    gx_camera_occlusion_api::~gx_camera_occlusion_api() {}
    gx_camera_occlusion_api::gx_camera_occlusion_api(gx_camera_occlusion_api&&) noexcept            = default;
    gx_camera_occlusion_api& gx_camera_occlusion_api::operator=(gx_camera_occlusion_api&&) noexcept = default;
    class gx_camera_occlusion_api::impl {
    public:
        void init() {
        }
        impl() {
            init();
        }
        impl(const std::string& config_path) {
            if (_config == nullptr) {
                _config = new config(config_path);
                pool    = new thread_pool(_config->thread_pool_val);
            }
            if (api_temp == nullptr) {
                api_temp = new gx_pedestrian_api(config_path);
            }
            init();
        }
        ~impl() {}

        int camera_id = 0; // 摄像头ID
        camera_occlusion_info safe_production_camera_occlusion(const gx_img_api& mat,int device_id) 
            try{
                return ;
            } catch (const std::exception& ex) {
                bool flag = write_dump_img(mat, "_camera_occlusion_dump.jpg", _config->_configure_directory.dump_img_directory);
                throw std::runtime_error{
                    ex.what() + std::string{flag ? "\nSave_picture_successfully" : "\nSave_picture_fail"}};
            }
        }

    };

    //  摄像头遮挡检测
    bool gx_camera_occlusion_api::safe_production_camera_occlusion(
        const gx_img_api& mat, int device_id) {
        if (impl_ == nullptr)
            throw std::runtime_error{"You need to create a new object !\n"};
        return impl_->safe_production_camera_occlusion(mat, device_id);
    }
} // namespace glasssix