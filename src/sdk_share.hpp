#pragma once
#include "../src/nessus/protocol.hpp"
#include "../src/nessus/protocols/damocles.hpp"
#include "../src/nessus/protocols/flame.hpp"
#include "../src/nessus/protocols/helmet.hpp"
#include "../src/nessus/protocols/irisviel.hpp"
#include "../src/nessus/protocols/leavepost.hpp"
#include "../src/nessus/protocols/longinus.hpp"
#include "../src/nessus/protocols/onphone.hpp"
#include "../src/nessus/protocols/pedestrian.hpp"
#include "../src/nessus/protocols/pedestrian_labor.hpp"
#include "../src/nessus/protocols/playphone.hpp"
#include "../src/nessus/protocols/refvest.hpp"
#include "../src/nessus/protocols/romancia.hpp"
#include "../src/nessus/protocols/selene.hpp"
#include "../src/nessus/protocols/sleep.hpp"
#include "../src/nessus/protocols/smog.hpp"
#include "../src/nessus/protocols/smoke.hpp"
#include "../src/nessus/protocols/tumble.hpp"
#include "../src/nessus/protocols/workcloth.hpp"
#include "config.hpp"
#include "glass6/secret_key_empower.hpp"
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
        std::string share_platform_name    = "RK3588";
#elif (GX_PLATFORM_NAME == 2)
        std::string share_platform_name = "RK3399";
#elif (GX_PLATFORM_NAME == 3)
        std::string share_platform_name = "RK3566";
#elif (GX_PLATFORM_NAME == 4)
        std::string share_platform_name = "RV1109";
#elif (GX_PLATFORM_NAME == 5)
        std::string share_platform_name = "CENTOS";
#endif

#if (EMPOWER_LANGUAGE == 0)
        std::string share_empower_language = "C++";
#elif (EMPOWER_LANGUAGE == 1)
        std::string share_empower_language = "JAVA";
#endif


        // GX_PLATFORM_NAME
    } // namespace
    extern config* _config;
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
            Function["flame"]            = &algo_ptr::set_protocols_handl_flame;
            Function["smog"]             = &algo_ptr::set_protocols_handl_smog;
            Function["refvest"]          = &algo_ptr::set_protocols_handl_refvest;
            Function["helmet"]           = &algo_ptr::set_protocols_handl_helmet;
            Function["selene"]           = &algo_ptr::set_protocols_handl_selene;
            Function["longinus"]         = &algo_ptr::set_protocols_handl_longinus;
            Function["romancia"]         = &algo_ptr::set_protocols_handl_romancia;
            Function["damocles"]         = &algo_ptr::set_protocols_handl_damocles;
            Function["sleep"]            = &algo_ptr::set_protocols_handl_sleep;
            Function["smoke"]            = &algo_ptr::set_protocols_handl_smoke;
            Function["tumble"]           = &algo_ptr::set_protocols_handl_tumble;
            Function["leavepost"]        = &algo_ptr::set_protocols_handl_leavepost;
            Function["playphone"]        = &algo_ptr::set_protocols_handl_playphone;
            Function["onphone"]          = &algo_ptr::set_protocols_handl_onphone;
            Function["workcloth"]        = &algo_ptr::set_protocols_handl_workcloth;
            Function["pedestrian_labor"] = &algo_ptr::set_protocols_handl_pedestrian_labor;
            Function["pedestrian"]       = &algo_ptr::set_protocols_handl_pedestrian;
        }
        void set_protocols_handl_flame() {
            _config->set_flame(_config->_path);
            flame_handle = protocol_ptr.make_instance<flame>(
                flame_new_param{_config->_flame_config.device, _config->_configure_directory.models_directory});
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
        void set_protocols_handl_helmet() {
            _config->set_helmet(_config->_path);
            helmet_handle = protocol_ptr.make_instance<helmet>(
                helmet_new_param{_config->_helmet_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_selene() {
            _config->set_feature(_config->_path);
            selene_handle = protocol_ptr.make_instance<selene>(
                selene_new_param{_config->_feature_config.device, _config->_configure_directory.models_directory,
                    _config->_feature_config.model_type, _config->_feature_config.use_int8});
        }
        void set_protocols_handl_longinus() {
            _config->set_detect(_config->_path);
            _config->set_track(_config->_path);
            longinus_handle =
                protocol_ptr.make_instance<longinus>(longinus_new_param{.device = _config->_detect_config.device,
                    .models_directory = _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_romancia() {
            _config->set_blur(_config->_path);
            romancia_handle = protocol_ptr.make_instance<romancia>(
                romancia_new_param{_config->_blur_config.device, _config->_configure_directory.models_directory});
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
        void set_protocols_handl_tumble() {
            _config->set_tumble(_config->_path);
            tumble_handle = protocol_ptr.make_instance<tumble>(
                tumble_new_param{_config->_tumble_config.device, _config->_configure_directory.models_directory});
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
        void set_protocols_handl_pedestrian_labor() {
            _config->set_pedestrian_labor(_config->_path);
            pedestrian_labor_handle = protocol_ptr.make_instance<pedestrian_labor>(pedestrian_labor_new_param{
                _config->_pedestrian_labor_config.device, _config->_configure_directory.models_directory});
        }
        void set_protocols_handl_pedestrian() {
            _config->set_pedestrian(_config->_path);
            pedestrian_handle = protocol_ptr.make_instance<pedestrian>(pedestrian_new_param{
                _config->_pedestrian_config.device, _config->_configure_directory.models_directory});
        }

        nessus_protocol protocol_ptr;
        damocles damocles_handle;
        longinus longinus_handle;
        romancia romancia_handle;
        selene selene_handle;
        refvest refvest_handle;
        flame flame_handle;
        smog smog_handle;
        helmet helmet_handle;
        sleep sleep_handle;
        smoke smoke_handle;
        tumble tumble_handle;
        leavepost leavepost_handle;
        playphone playphone_handle;
        onphone onphone_handle;
        workcloth workcloth_handle;
        pedestrian_labor pedestrian_labor_handle;
        pedestrian pedestrian_handle;
    };
    extern algo_irisviel_ptr* thread_algo_irisviel_ptr;
    extern std::unordered_map<std::thread::id, algo_ptr*> all_thread_algo_ptr;
    extern thread_pool* pool;
    extern void empower_Callback(
        void* context, std::string success, const char* message, std::int64_t remaining_seconds);
    extern std::string empower_time_decode(std::string timestampStr, std::string encode_str);
    extern std::string get_time_code();
    extern std::string getSubstring(const std::string& str64, int pos_t);
} // namespace glasssix
