include_guard()
include(${CMAKE_CURRENT_LIST_DIR}/GXUtil.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/GXEmscripten.cmake)

function(gx_write_boost_user_config_file)
    set(options "")
    set(one_value_args TOOLSET FILE RESULT_TOOLSET_ABBREVIATION)
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")
    gx_ensure_parameters(gx_write_boost_project_jam_file ARG TOOLSET FILE RESULT_TOOLSET_ABBREVIATION)

    get_filename_component(toolset_file_name ${ARG_TOOLSET} NAME_WE)
    message("[gx_write_boost_user_config_file][toolset_file_name] ${toolset_file_name}")

    # arm-none-linux-gnueabihf-gcc --> gcc
    # arm-none-linux-gnueabihf-g++ --> g++
    if(NOT "${toolset_file_name}" MATCHES [=[^(.+-)*(.+)$]=])
        message(FATAL_ERROR "Invalid format of the toolset file name: ${toolset_file_name}.")
    endif()

    set(map_g++ gcc)
    set(map_em++ emscripten)

    if(NOT "${map_${CMAKE_MATCH_2}}" STREQUAL "")
        set(toolset_name ${map_${CMAKE_MATCH_2}})
    else()
        set(toolset_name ${CMAKE_MATCH_2})
    endif()
    # ${toolset_name}
    file(WRITE ${ARG_FILE} "using ${toolset_name} : : \"${ARG_TOOLSET}\" : ;")
    set(${ARG_RESULT_TOOLSET_ABBREVIATION} ${toolset_name} PARENT_SCOPE)
endfunction()

function(gx_make_boost_impl)
    set(options SYNC_BUILD_TYPE REQUIRED PARALLEL_BUILD STATIC STATIC_RUNTIME)
    set(one_value_args SOURCE_DIR BINARY_DIR INSTALL_DIR TOOLSET TARGET_OS RESULT_FIND_PACKAGE_OPTIONS)
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")
    gx_ensure_parameters(gx_make_boost ARG SOURCE_DIR RESULT_FIND_PACKAGE_OPTIONS)    

    gx_make_default_binary_dir_and_install_dir(
        SOURCE_DIR ${ARG_SOURCE_DIR}
        PREFIX third-party
        RESULT_BINARY_DIR default_binary_dir
        RESULT_INSTALL_DIR default_install_dir
    )

    if(ARG_BINARY_DIR)
        set(binary_dir ${ARG_BINARY_DIR})
    else()
        set(binary_dir ${default_binary_dir})
    endif()

    if(ARG_INSTALL_DIR)
        set(install_dir ${ARG_INSTALL_DIR})
    else()
        set(install_dir ${default_install_dir})
    endif()

    gx_check_emscripten(use_emcc use_emxx emscripten_dir)

    # Replaces CMAKE_EXECUTABLE_SUFFIX with host_executable_suffix here to avoid .js when Emscripten designated.
    set(b2_program ${ARG_SOURCE_DIR}/b2${GX_HOST_EXECUTABLE_SUFFIX})

    # Bootstrap the boost archive if neccessary.
    if(NOT EXISTS ${b2_program})
        # Assumes cross-compiling using em++ on Windows.
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
            gx_execute_process(
                COMMAND bootstrap.bat
                WORKING_DIRECTORY ${ARG_SOURCE_DIR}
            )
        else()
            gx_execute_process(
                COMMAND sh bootstrap.sh
                WORKING_DIRECTORY ${ARG_SOURCE_DIR}
            )
        endif()
    endif()

    if(ARG_SYNC_BUILD_TYPE)
        string(TOLOWER "${CMAKE_BUILD_TYPE}" build_type)
        set(additional_args variant=${build_type})
    else()
        set(additional_args "")
    endif()
    
    if(ARG_PARALLEL_BUILD)
        include(ProcessorCount)
        ProcessorCount(processor_count)

        list(APPEND additional_args -j${processor_count})
    endif()

    if(ARG_STATIC)
        list(APPEND additional_args link=static)
        set(Boost_USE_STATIC_LIBS ON PARENT_SCOPE)
    endif()

    set(cflags "cflags=")
    set(cxxflags "cxxflags=")

    if(ARG_STATIC_RUNTIME)
        list(APPEND additional_args runtime-link=static)
        set(Boost_USE_STATIC_RUNTIME ON PARENT_SCOPE)

        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            string(APPEND cflags "-static-libgcc")
            string(APPEND cxxflags "-static-libgcc")
        endif()
    endif()

    list(APPEND additional_args ${cflags} ${cxxflags})

    if(ARG_TOOLSET)
        set(user_config_file ${binary_dir}/user-config.jam)
        gx_write_boost_user_config_file(
            TOOLSET ${ARG_TOOLSET}
            FILE ${user_config_file}
            RESULT_TOOLSET_ABBREVIATION toolset_abbreviation
        )

        list(
            APPEND additional_args
            toolset=${toolset_abbreviation}
            --user-config=${user_config_file}
        )
    endif()

    if(ARG_TARGET_OS)
        list(APPEND additional_args target-os=${ARG_TARGET_OS})
    endif()

    if(use_emxx)
        list(APPEND additional_args --disable-icu)
    endif()

    file(MAKE_DIRECTORY ${binary_dir})
    gx_execute_process(
        COMMAND ${b2_program} --prefix=${install_dir} --build-dir=${binary_dir} ${additional_args} install
        WORKING_DIRECTORY ${ARG_SOURCE_DIR}
    )

    if(ARG_REQUIRED)
        set(find_package_options REQUIRED)
    else()
        set(find_package_options "")
    endif()

    set(BOOST_ROOT ${install_dir} PARENT_SCOPE)
    set(${ARG_RESULT_FIND_PACKAGE_OPTIONS} ${find_package_options} PARENT_SCOPE)
endfunction()

macro(gx_make_boost)
    gx_make_boost_impl(
        ${ARGN}
        RESULT_FIND_PACKAGE_OPTIONS gx_make_boost_find_package_options
    )

    # https://cmake.org/cmake/help/latest/policy/CMP0074.html
    cmake_policy(PUSH)
    cmake_policy(SET CMP0074 NEW)
    find_package(Boost ${gx_make_boost_find_package_options})
    cmake_policy(POP)

    unset(gx_make_openssl_find_package_options)
endmacro()
