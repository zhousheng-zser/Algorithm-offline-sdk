#include <struct_json.hpp> 
#include "../protocols_reflection.hpp"

//≈‰÷√Œƒº˛
struct camera_occlusion_config {
    int initial_normal_range_l;
    int initial_normal_range_r;
    int num_frames;
    int frames_interval;
    int repeated_outside_threshold;
    int restart_normal_count;
    int update_interval;
};
DEFINE_STRUCT_SCHEMA(camera_occlusion_config, 
    DEFINE_STRUCT_FIELD(initial_normal_range_l, "initial_normal_range_l"),
    DEFINE_STRUCT_FIELD(initial_normal_range_r, "initial_normal_range_r"), 
    DEFINE_STRUCT_FIELD(num_frames, "num_frames"), 
    DEFINE_STRUCT_FIELD(frames_interval, "frames_interval"),
    DEFINE_STRUCT_FIELD(repeated_outside_threshold, "repeated_outside_threshold"),
    DEFINE_STRUCT_FIELD(restart_normal_count, "restart_normal_count"),
    DEFINE_STRUCT_FIELD(update_interval, "update_interval"));
