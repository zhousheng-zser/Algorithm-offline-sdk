include_guard()
include(${CMAKE_CURRENT_LIST_DIR}/GXUtil.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/GXEmscripten.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/GXCCXXRuntime.cmake)

# CMAKE_CURRENT_LIST_DIR will change within funcitons (with a dynamic scope).
set(_gx_openssl_absolute_current_dir ${CMAKE_CURRENT_LIST_DIR})

function(gx_openssl_patch_lib64 install_dir)
    if(EXISTS ${install_dir}/lib64 AND NOT EXISTS ${install_dir}/lib)
        file(CREATE_LINK ${install_dir}/lib64 ${install_dir}/lib COPY_ON_ERROR SYMBOLIC)
    endif()
endfunction()

function(gx_make_openssl_impl)
    set(options SYNC_BUILD_TYPE REQUIRED PARALLEL_BUILD STATIC STATIC_RUNTIME)
    set(one_value_args SOURCE_DIR BINARY_DIR CROSS_COMPILE CROSS_PLATFORM CC RESULT_FIND_PACKAGE_OPTIONS)
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")
    gx_ensure_parameters(gx_make_openssl ARG SOURCE_DIR RESULT_FIND_PACKAGE_OPTIONS)

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

    if(ARG_CROSS_COMPILE)
        gx_ensure_parameters(gx_make_openssl ARG CROSS_PLATFORM)
        set(configure_command ${ARG_SOURCE_DIR}/Configure)
        set(configure_args ${ARG_CROSS_PLATFORM} CROSS_COMPILE=${ARG_CROSS_COMPILE})
        set(make_command make)
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
        set(configure_args ${ARG_SOURCE_DIR}/Configure)
        
        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            list(APPEND configure_args VC-WIN64A)
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            list(APPEND configure_args VC-WIN32)
        else()
            message(FATAL_ERROR "This build system does not support non-32-bit or non-64-bit targets.")
        endif()

        list(APPEND configure_args /FS)

        set(configure_command ${_gx_openssl_absolute_current_dir}/../tools/perl-win/bin/perl.exe)
        set(make_command ${PROJECT_SOURCE_DIR}/tools/jom/jom.exe) # ${nmake_program}
    else()
        set(configure_command ${ARG_SOURCE_DIR}/config)
        set(make_command make)

        if(CMAKE_SIZEOF_VOID_P EQUAL 8)
            set(configure_args "linux-generic64")
        elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
            set(configure_args "linux-generic32")
        else()
            message(FATAL_ERROR "This build system does not support non-32-bit or non-64-bit targets.")
        endif()

        if(NOT use_emcc)
            # https://github.com/openssl/openssl/issues/1740
            list(APPEND configure_args "-Wl,--enable-new-dtags,-rpath,'$(LIBRPATH)'" "-Wl,-rpath,'$(LIBRPATH)'")
        endif()
    endif()

    if(use_emcc)
        list(INSERT configure_command 0 ${emscripten_dir}/emconfigure)
    endif()

    if(ARG_CC)
        list(APPEND configure_args CC=${ARG_CC})
    elseif(use_emcc)
        list(APPEND configure_args CC=cc AR=ar NM=nm RANLIB=ranlib STRIP=strip)
    elseif(NOT WIN32)
        list(APPEND configure_args CC=${CMAKE_C_COMPILER})
    endif()

    if(ARG_PARALLEL_BUILD)
        gx_thread_pool_worker_count(worker_count)
        set(make_extra_args -j${worker_count})
    else()
        set(make_extra_args "")
    endif()
    
    set(environment_variables "")
	
	if(ARG_STATIC)
        list(APPEND configure_args no-shared)
        set(OPENSSL_USE_STATIC_LIBS TRUE PARENT_SCOPE)
    endif()

    if(ARG_SYNC_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
        list(APPEND configure_args --debug)
    endif()

    if(ARG_STATIC_RUNTIME AND NOT use_emcc)
        gx_make_c_cxx_runtime_flags(
            STATIC_RUNTIME
            RESULT_DEBUG_FLAGS debug_flags
            RESULT_RELEASE_FLAGS release_flags
        )
        
        if(CMAKE_BUILD_TYPE STREQUAL "Debug")
            list(APPEND configure_args ${debug_flags})
        else()
            list(APPEND configure_args ${release_flags})
        endif()
    endif()

    if(CMAKE_C_FLAGS AND NOT CMAKE_C_FLAGS STREQUAL "\"\"")
        # Converts a space-separated string to a list.
        string(REPLACE " " ";" cmake_c_flags_list ${CMAKE_C_FLAGS})

        # Removes the unsupported flag for Clang.
        list(REMOVE_ITEM cmake_c_flags_list "-no-canonical-prefixes")

        list(
            APPEND configure_args
            ${cmake_c_flags_list}
        )
    endif()
	
    file(MAKE_DIRECTORY ${binary_dir})
    
    # (Re-)configure the project only when neccessary.
    if(NOT EXISTS ${binary_dir}/makefile)
        # OpenSSL 1.1.0 changed the behavior of install rules.
        # You should specify both --prefix and --openssldir to ensure make install works as expected.
        # https://wiki.openssl.org/index.php/Compilation_and_Installation#PREFIX_and_OPENSSLDIR
        # Prevents perl from generating unquoted absolute path for CC and CXX.
        if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            set(env_args ENVIRONMENT_VARIABLES CC=cl CXX=cl RC=rc)
        else()
            set(env_args "")
        endif()

        gx_execute_process(
            COMMAND ${configure_command} ${configure_args} --prefix=${install_dir} --openssldir=${install_dir} no-asm no-tests ${ARG_UNPARSED_ARGUMENTS}
            WORKING_DIRECTORY ${binary_dir}
            ${env_args}
        )
    endif()

    gx_execute_process(
        COMMAND ${make_command} ${make_extra_args}
        WORKING_DIRECTORY ${binary_dir}
        ENVIRONMENT_VARIABLES ${environment_variables}
    )

    gx_execute_process(
        COMMAND ${make_command} install_sw
        WORKING_DIRECTORY ${binary_dir}
    )

    if(ARG_REQUIRED)
        set(find_package_options REQUIRED)
    else()
        set(find_package_options "")
    endif()

    gx_openssl_patch_lib64(${install_dir})

    set(OPENSSL_ROOT_DIR ${install_dir} PARENT_SCOPE)
    set(${ARG_RESULT_FIND_PACKAGE_OPTIONS} ${find_package_options} PARENT_SCOPE)
endfunction()

macro(gx_make_openssl)
    gx_make_openssl_impl(
        ${ARGN}
        RESULT_FIND_PACKAGE_OPTIONS gx_make_openssl_find_package_options
    )

    message(STATUS "[gx_make_openssl][OPENSSL_USE_STATIC_LIBS] ${OPENSSL_USE_STATIC_LIBS}")
    message(STATUS "[gx_make_openssl][OPENSSL_ROOT_DIR] ${OPENSSL_ROOT_DIR}")

    # https://cmake.org/cmake/help/latest/policy/CMP0074.html
    cmake_policy(PUSH)
    cmake_policy(SET CMP0074 NEW)
    gx_push_root_path_policy()
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
    find_package(OpenSSL ${gx_make_openssl_find_package_options})
    gx_pop_root_path_policy()
    cmake_policy(POP)

    if(NOT WIN32)
        gx_pkg_config_add_path(${OPENSSL_ROOT_DIR}/lib/pkgconfig)
    endif()

    unset(gx_make_openssl_find_package_options)
endmacro()
