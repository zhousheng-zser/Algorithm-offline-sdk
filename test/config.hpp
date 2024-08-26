#pragma once
#include <g6/format_remediation.hpp>
#include <g6/json_compat.hpp>
#include <g6/json_extensions.hpp>
#include <g6/logger.hpp>

namespace glasssix {
    struct configure_directory {
        GX_BEGIN_FIELDS(configure_directory);
        GX_FIELD(abi::string, models_directory);
        GX_FIELD(abi::string, directory);
        GX_FIELD(abi::string, license_directory);
        GX_FIELD(abi::string, empower_serial_number);
        GX_FIELD(int, thread_pool_num);
        GX_FIELD(int, thread_pool_num_batterypilferers);
        GX_FIELD(int, thread_pool_num_fighting);
        GX_FIELD(int, thread_pool_num_tumble);
        GX_FIELD(int, thread_pool_num_climb);
        GX_FIELD(int, thread_pool_num_climb_tumble_pedestrian);
        GX_FIELD(int, thread_pool_num_flame);
        GX_FIELD(int, thread_pool_num_smog);
        GX_FIELD(int, thread_pool_num_smoke);
        GX_FIELD(int, thread_pool_num_playphone);
        GX_FIELD(int, thread_pool_num_sleep);
        GX_FIELD(int, thread_pool_num_helmet);
        GX_FIELD(int, thread_pool_num_leavepost);
        GX_FIELD(int, thread_pool_num_pump_weld_hoisting);
        GX_FIELD(abi::string, dump_img_directory);
        GX_FIELD(int, cycle_num);
        GX_END_FIELDS;

        GX_JSON_SERIALIZABLE(naming_convention::lower_case_with_underscores);
    };

    class config {
    public:
        config();
        config(const abi::string& path);
        abi::string _path;
        nlohmann::json protocols_list;
        configure_directory _configure_directory;

        void set_configure_directory(abi::string& path);
        bool configure_directory_is_load = false;

    private:
        glasssix::json read_json_file(const abi::string& path);
    };
}