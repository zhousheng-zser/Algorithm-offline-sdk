#pragma once
#include "../src/nessus/protocol.hpp"
#include "../src/nessus/protocols/batterypilferers.hpp"
#include "../src/nessus/protocols/cassius.hpp"
#include "../src/nessus/protocols/climb.hpp"
#include "../src/nessus/protocols/climb_pedestrian.hpp"
#include "../src/nessus/protocols/crossing.hpp"
#include "../src/nessus/protocols/crowd.hpp"
#include "../src/nessus/protocols/damocles.hpp"
#include "../src/nessus/protocols/face_attributes.hpp"
#include "../src/nessus/protocols/fighting.hpp"
#include "../src/nessus/protocols/flame.hpp"
#include "../src/nessus/protocols/head.hpp"
#include "../src/nessus/protocols/helmet.hpp"
#include "../src/nessus/protocols/irisviel.hpp"
#include "../src/nessus/protocols/leavepost.hpp"
#include "../src/nessus/protocols/longinus.hpp"
#include "../src/nessus/protocols/onphone.hpp"
#include "../src/nessus/protocols/pedestrian.hpp"
#include "../src/nessus/protocols/pedestrian_min.hpp"
#include "../src/nessus/protocols/playphone.hpp"
#include "../src/nessus/protocols/posture.hpp"
#include "../src/nessus/protocols/pump_gate_status.hpp"
#include "../src/nessus/protocols/pump_hoisting.hpp"
#include "../src/nessus/protocols/pump_light.hpp"
#include "../src/nessus/protocols/pump_mask.hpp"
#include "../src/nessus/protocols/pump_pumptop_person.hpp"
#include "../src/nessus/protocols/pump_vesthelmet.hpp"
#include "../src/nessus/protocols/pump_weld.hpp"
#include "../src/nessus/protocols/pump_work_status.hpp"
#include "../src/nessus/protocols/pumptop_helmet.hpp"
#include "../src/nessus/protocols/refvest.hpp"
#include "../src/nessus/protocols/romancia.hpp"
#include "../src/nessus/protocols/selene.hpp"
#include "../src/nessus/protocols/sleep.hpp"
#include "../src/nessus/protocols/smog.hpp"
#include "../src/nessus/protocols/smoke.hpp"
#include "../src/nessus/protocols/tumble.hpp"
#include "../src/nessus/protocols/tumble_pedestrian.hpp"
#include "../src/nessus/protocols/vehicle.hpp"
#include "../src/nessus/protocols/wander.hpp"
#include "../src/nessus/protocols/workcloth.hpp"
#include "config.hpp"
#include "data_time.hpp"
#if (GX_EMPOWER_FLAG)
#include "glass6/secret_key_empower.hpp"
#endif
#include "gx_api.hpp"
#include "thread_pool.hpp"

#include <chrono>
#include <mutex>

#include <g6/char8_t_remediation.hpp>
#include <g6/crypto/symmetric_cipher_provider.hpp>
namespace glasssix {
    namespace {
#if (GX_PLATFORM_NAME == 0)
        std::string share_platform_name = "WINDOWS";
#elif (GX_PLATFORM_NAME == 1)
        std::string share_platform_name = "RK3588";
#elif (GX_PLATFORM_NAME == 2)
        std::string share_platform_name = "RK3399";
#elif (GX_PLATFORM_NAME == 3)
        std::string share_platform_name = "RK3566";
#elif (GX_PLATFORM_NAME == 4)
        std::string share_platform_name = "RV1109";
#elif (GX_PLATFORM_NAME == 5)
        std::string share_platform_name = "CENTOS";
#elif (GX_PLATFORM_NAME == 6)
        std::string share_platform_name = "UBUNTU";
#elif (GX_PLATFORM_NAME == 7)
        std::string share_platform_name = "RV1106";
#elif (GX_PLATFORM_NAME == 8)
        std::string share_platform_name = "SOPHON";
#endif

#if (EMPOWER_LANGUAGE == 0)
        std::string share_empower_language = "C++";
#elif (EMPOWER_LANGUAGE == 1)
        std::string share_empower_language = "JAVA";
#endif


        // GX_PLATFORM_NAME
    } // namespace
    extern config* _config;
    extern bool empower_warning_flag;
    class algo_irisviel_ptr {
    public:
        algo_irisviel_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "irisviel") {
                    try {
                        _config->set_face_user(_config->_path);
                        irisivel_handle = protocol_ptr.make_instance<irisviel>(irisviel_new_param{
                            _config->_face_user_config.dimension, _config->_face_user_config.working_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        irisviel irisivel_handle;
    };
    class algo_crowd_ptr {
    public:
        algo_crowd_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "crowd") {
                    try {
                        _config->set_crowd(_config->_path);
                        crowd_handle = protocol_ptr.make_instance<crowd>(crowd_new_param{
                            _config->_crowd_config.device, _config->_configure_directory.models_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        crowd crowd_handle;
    };
    class algo_batterypilferers_ptr {
    public:
        algo_batterypilferers_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "batterypilferers") {
                    try {
                        _config->set_batterypilferers(_config->_path);
                        batterypilferers_handle = protocol_ptr.make_instance<batterypilferers>(
                            batterypilferers_new_param{_config->_batterypilferers_config.device,
                                _config->_configure_directory.models_directory, 3});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        batterypilferers batterypilferers_handle;
    };
    class algo_fighting_ptr {
    public:
        algo_fighting_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "fighting") {
                    try {
                        _config->set_fighting(_config->_path);
                        fighting_handle =
                            protocol_ptr.make_instance<fighting>(fighting_new_param{_config->_fighting_config.device,
                                _config->_configure_directory.models_directory, _config->_fighting_config.batch});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        fighting fighting_handle;
    };
    class algo_tumble_ptr {
    public:
        algo_tumble_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "tumble") {
                    try {
                        _config->set_tumble(_config->_path);
                        tumble_handle = protocol_ptr.make_instance<tumble>(tumble_new_param{
                            _config->_tumble_config.device, _config->_configure_directory.models_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
                else if (temp_str == "tumble_pedestrian") {
                    try {
                        _config->set_tumble_pedestrian(_config->_path);
                        tumble_pedestrian_handle = protocol_ptr.make_instance<tumble_pedestrian>(
                            tumble_pedestrian_new_param{
                            _config->_tumble_pedestrian_config.device, _config->_configure_directory.models_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        tumble tumble_handle;
        tumble_pedestrian tumble_pedestrian_handle;
    };
    class algo_climb_ptr {
    public:
        algo_climb_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                if (temp_str == "climb") {
                    try {
                        _config->set_climb(_config->_path);
                        climb_handle = protocol_ptr.make_instance<climb>(climb_new_param{
                            _config->_climb_config.device, _config->_configure_directory.models_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
                else if (temp_str == "climb_pedestrian") {
                    try {
                        _config->set_climb_pedestrian(_config->_path);
                        climb_pedestrian_handle = protocol_ptr.make_instance<climb_pedestrian>(climb_pedestrian_new_param{
                            _config->_climb_pedestrian_config.device, _config->_configure_directory.models_directory});
                    } catch (const std::exception& ex) {
                        throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                    }
                }
            }
        }
        nessus_protocol protocol_ptr;
        climb climb_handle;
        climb_pedestrian climb_pedestrian_handle;
    };
    class algo_ptr {
    public:
        typedef void (algo_ptr::*set_protocols_handle)();
        algo_ptr() {
            protocol_ptr.init(_config->_configure_directory.directory);
            set_Function();
            for (int i = 0; i < _config->protocols_list["plugin_list"].size(); ++i) {
                std::string temp_str = _config->protocols_list["plugin_list"][i];
                try {
                    set_protocols_handle fun = this->Function[temp_str];
                    if (fun != nullptr) {
                        (this->*fun)();
                    }
                } catch (const std::exception& ex) {
                    throw source_code_aware_runtime_error(U8("Error: ") + temp_str + U8(": ") + ex.what());
                }
            }
        }
        std::unordered_map<std::string, set_protocols_handle> Function;
        void set_Function() {
            Function["face_attributes"]     = &algo_ptr::set_protocols_handl_face_attributes;
            Function["crossing"]            = &algo_ptr::set_protocols_handl_crossing;
            Function["flame"]               = &algo_ptr::set_protocols_handl_flame;
            Function["pump_mask"]           = &algo_ptr::set_protocols_handl_pump_mask;
            Function["pump_weld"]           = &algo_ptr::set_protocols_handl_pump_weld;
            Function["pump_hoisting"]       = &algo_ptr::set_protocols_handl_pump_hoisting;
            Function["pump_vesthelmet"]     = &algo_ptr::set_protocols_handl_pump_vesthelmet;
            Function["pumptop_helmet"]      = &algo_ptr::set_protocols_handl_pumptop_helmet;
            Function["pump_gate_status"]    = &algo_ptr::set_protocols_handl_pump_gate_status;
            Function["pump_light"]          = &algo_ptr::set_protocols_handl_pump_light;
            Function["pump_work_status"]    = &algo_ptr::set_protocols_handl_pump_work_status;
            Function["smog"]                = &algo_ptr::set_protocols_handl_smog;
            Function["refvest"]             = &algo_ptr::set_protocols_handl_refvest;
            Function["head"]                = &algo_ptr::set_protocols_handl_head;
            Function["helmet"]              = &algo_ptr::set_protocols_handl_helmet;
            Function["selene"]              = &algo_ptr::set_protocols_handl_selene;
            Function["cassius"]             = &algo_ptr::set_protocols_handl_cassius;
            Function["longinus"]            = &algo_ptr::set_protocols_handl_longinus;
            Function["romancia"]            = &algo_ptr::set_protocols_handl_romancia;
            Function["damocles"]            = &algo_ptr::set_protocols_handl_damocles;
            Function["sleep"]               = &algo_ptr::set_protocols_handl_sleep;
            Function["smoke"]               = &algo_ptr::set_protocols_handl_smoke;
            Function["vehicle"]             = &algo_ptr::set_protocols_handl_vehicle;
            Function["wander"]              = &algo_ptr::set_protocols_handl_wander;
            Function["pump_pumptop_person"] = &algo_ptr::set_protocols_handl_pump_pumptop_person;
            Function["leavepost"]           = &algo_ptr::set_protocols_handl_leavepost;
            Function["playphone"]           = &algo_ptr::set_protocols_handl_playphone;
            Function["onphone"]             = &algo_ptr::set_protocols_handl_onphone;
            Function["workcloth"]           = &algo_ptr::set_protocols_handl_workcloth;
            Function["pedestrian"]          = &algo_ptr::set_protocols_handl_pedestrian;
            Function["pedestrian_min"]      = &algo_ptr::set_protocols_handl_pedestrian_min;
            Function["posture"]             = &algo_ptr::set_protocols_handl_posture;
        }
        void set_protocols_handl_crossing() {
            _config->set_crossing(_config->_path);
            crossing_handle = protocol_ptr.make_instance<crossing>(
                crossing_new_param{_config->_crossing_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_flame() {
            _config->set_flame(_config->_path);
            flame_handle = protocol_ptr.make_instance<flame>(
                flame_new_param{_config->_flame_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_mask() {
            _config->set_pump_mask(_config->_path);
            pump_mask_handle = protocol_ptr.make_instance<pump_mask>(
                pump_mask_new_param{_config->_pump_mask_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_weld() {
            _config->set_pump_weld(_config->_path);
            pump_weld_handle = protocol_ptr.make_instance<pump_weld>(
                pump_weld_new_param{_config->_pump_weld_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_hoisting() {
            _config->set_pump_hoisting(_config->_path);
            pump_hoisting_handle = protocol_ptr.make_instance<pump_hoisting>(pump_hoisting_new_param{
                _config->_pump_hoisting_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_vesthelmet() {
            _config->set_pump_vesthelmet(_config->_path);
            pump_vesthelmet_handle = protocol_ptr.make_instance<pump_vesthelmet>(pump_vesthelmet_new_param{
                _config->_pump_vesthelmet_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pumptop_helmet() {
            _config->set_pumptop_helmet(_config->_path);
            pumptop_helmet_handle = protocol_ptr.make_instance<pumptop_helmet>(pumptop_helmet_new_param{
                _config->_pumptop_helmet_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_gate_status() {
            _config->set_pump_gate_status(_config->_path);
            pump_gate_status_handle = protocol_ptr.make_instance<pump_gate_status>(
                pump_gate_status_new_param{_config->_pump_gate_status_config.device});
        }
        void set_protocols_handl_pump_light() {
            _config->set_pump_light(_config->_path);
            pump_light_handle = protocol_ptr.make_instance<pump_light>(pump_light_new_param{
                _config->_pump_light_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_work_status() {
            _config->set_pump_work_status(_config->_path);
            pump_work_status_handle = protocol_ptr.make_instance<pump_work_status>(pump_work_status_new_param{});
        }
        void set_protocols_handl_smog() {
            _config->set_smog(_config->_path);
            smog_handle = protocol_ptr.make_instance<smog>(
                smog_new_param{_config->_smog_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_refvest() {
            _config->set_refvest(_config->_path);
            refvest_handle = protocol_ptr.make_instance<refvest>(
                refvest_new_param{_config->_refvest_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_head() {
            head_handle = protocol_ptr.make_instance<head>(
                head_new_param{.device = -1, .models_directory = _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_helmet() {
            _config->set_helmet(_config->_path);
            helmet_handle = protocol_ptr.make_instance<helmet>(
                helmet_new_param{_config->_helmet_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_selene() {
            _config->set_feature(_config->_path);
            if (_config->_feature_config.dimension != 256)
                return;
            selene_handle = protocol_ptr.make_instance<selene>(
                selene_new_param{_config->_feature_config.device, _config->_configure_directory.models_directory,
                    _config->_feature_config.model_type, _config->_feature_config.use_int8});
        }
        void set_protocols_handl_cassius() {
            _config->set_feature(_config->_path);
            if (_config->_feature_config.dimension != 512)
                return;
            cassius_handle = protocol_ptr.make_instance<cassius>(
                cassius_new_param{_config->_feature_config.device, _config->_configure_directory.models_directory,
                    _config->_feature_config.model_type, _config->_feature_config.use_int8});
        }
        void set_protocols_handl_longinus() {
            _config->set_detect(_config->_path);
            _config->set_track(_config->_path);
            longinus_handle =
                protocol_ptr.make_instance<longinus>(longinus_new_param{.device = _config->_detect_config.device,
                    .model_type                                                 = _config->_detect_config.model_type,
                    .algo_type                                                  = _config->_detect_config.algo_type,
                    .models_directory = _config->_configure_directory.models_directory});
            longinus_handle_library =
                protocol_ptr.make_instance<longinus>(longinus_new_param{.device = _config->_detect_config.device,
                    .model_type                                                 = _config->_detect_config.model_type,
                    .algo_type        = _config->_detect_config.library_algo_type,
                    .models_directory = _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_romancia() {
            _config->set_blur(_config->_path);
            romancia_handle = protocol_ptr.make_instance<romancia>(
                romancia_new_param{_config->_blur_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_face_attributes() {
            _config->set_attributes(_config->_path);
            face_attributes_handle = protocol_ptr.make_instance<face_attributes>(face_attributes_new_param{
                _config->_attributes_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_damocles() {
            _config->set_action_live(_config->_path);
            damocles_handle =
                protocol_ptr.make_instance<damocles>(damocles_new_param{_config->_action_live_config.device,
                    _config->_action_live_config.model_type, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_sleep() {
            _config->set_sleep(_config->_path);
            sleep_handle = protocol_ptr.make_instance<sleep>(
                sleep_new_param{_config->_sleep_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_smoke() {
            _config->set_smoke(_config->_path);
            smoke_handle = protocol_ptr.make_instance<smoke>(
                smoke_new_param{_config->_smoke_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_vehicle() {
            _config->set_vehicle(_config->_path);
            vehicle_handle = protocol_ptr.make_instance<vehicle>(
                vehicle_new_param{_config->_vehicle_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_wander() {
            _config->set_wander(_config->_path);
            _config->set_wander_limit(_config->_path);
            wander_handle = protocol_ptr.make_instance<wander>(
                wander_new_param{_config->_wander_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pump_pumptop_person() {
            _config->set_pump_pumptop_person(_config->_path);
            pump_pumptop_person_handle = protocol_ptr.make_instance<pump_pumptop_person>(pump_pumptop_person_new_param{
                _config->_pump_pumptop_person_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_leavepost() {
            _config->set_leavepost(_config->_path);
            leavepost_handle = protocol_ptr.make_instance<leavepost>(
                leavepost_new_param{_config->_leavepost_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_onphone() {
            _config->set_onphone(_config->_path);
            onphone_handle = protocol_ptr.make_instance<onphone>(
                onphone_new_param{_config->_onphone_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_playphone() {
            _config->set_playphone(_config->_path);
            playphone_handle = protocol_ptr.make_instance<playphone>(
                playphone_new_param{_config->_playphone_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_workcloth() {
            _config->set_workcloth(_config->_path);
            workcloth_handle = protocol_ptr.make_instance<workcloth>(
                workcloth_new_param{_config->_workcloth_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pedestrian() {
            _config->set_pedestrian(_config->_path);
            pedestrian_handle = protocol_ptr.make_instance<pedestrian>(pedestrian_new_param{
                _config->_pedestrian_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pedestrian_min() {
            _config->set_pedestrian_min(_config->_path);
            pedestrian_min_handle = protocol_ptr.make_instance<pedestrian_min>(pedestrian_min_new_param{
                _config->_pedestrian_min_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_posture() {
            posture_handle = protocol_ptr.make_instance<posture>(posture_new_param{
                .device = -1, .models_directory = _config->_configure_directory.models_directory, .model_type = 1});
        }

        nessus_protocol protocol_ptr;
        face_attributes face_attributes_handle;
        damocles damocles_handle;
        longinus longinus_handle_library;
        longinus longinus_handle;
        romancia romancia_handle;
        selene selene_handle;
        cassius cassius_handle;
        refvest refvest_handle;
        crossing crossing_handle;
        flame flame_handle;
        pump_mask pump_mask_handle;
        pump_weld pump_weld_handle;
        pump_hoisting pump_hoisting_handle;
        pump_vesthelmet pump_vesthelmet_handle;
        pumptop_helmet pumptop_helmet_handle;
        pump_gate_status pump_gate_status_handle;
        pump_light pump_light_handle;
        pump_work_status pump_work_status_handle;
        pump_pumptop_person pump_pumptop_person_handle;
        smog smog_handle;
        head head_handle;
        helmet helmet_handle;
        sleep sleep_handle;
        smoke smoke_handle;
        vehicle vehicle_handle;
        wander wander_handle;
        leavepost leavepost_handle;
        playphone playphone_handle;
        onphone onphone_handle;
        workcloth workcloth_handle;
        pedestrian pedestrian_handle;
        pedestrian_min pedestrian_min_handle;
        posture posture_handle;
    };
    extern algo_irisviel_ptr* thread_algo_irisviel_ptr;
    extern algo_crowd_ptr* thread_algo_crowd_ptr;
    extern std::unordered_map<std::thread::id, algo_ptr*> all_thread_algo_ptr;
    extern thread_pool* pool;
    extern void empower_Callback(
        void* context, std::string success, const char* message, std::int64_t remaining_seconds);
    extern std::string empower_time_decode(std::string timestampStr, std::string encode_str);
    extern std::string get_time_code();
    extern std::string getSubstring(const std::string& str64, int pos_t);
    bool write_dump_img(const gx_img_api& mat, std::string);
} // namespace glasssix
