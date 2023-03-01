include_guard()
include(${CMAKE_CURRENT_LIST_DIR}/GXUtil.cmake)

function(gx_make_c_cxx_runtime_flags)
    set(options STATIC_RUNTIME)
    set(one_value_args MSVC_OPTION_PREFIX RESULT_DEBUG_FLAGS RESULT_RELEASE_FLAGS)
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")
    gx_ensure_parameters(gx_make_c_cxx_runtime_flags ARG RESULT_DEBUG_FLAGS RESULT_RELEASE_FLAGS)

    if(ARG_MSVC_OPTION_PREFIX)
        set(msvc_option_prefix ${ARG_MSVC_OPTION_PREFIX})
    else()
        set(msvc_option_prefix /)
    endif()

    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        if(ARG_STATIC_RUNTIME)
            set(debug_flag ${msvc_option_prefix}MTd)
            set(release_flag ${msvc_option_prefix}MT)
        else()
            set(debug_flag ${msvc_option_prefix}MDd)
            set(release_flag ${msvc_option_prefix}MD)
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        if(ARG_STATIC_RUNTIME)
            set(debug_flag "-static-libstdc++ -static-libgcc")
            set(release_flag ${debug_flag})
        else()
            set(debug_flag "")
            set(release_flag "")
        endif()
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
        if(ARG_STATIC_RUNTIME)
            set(debug_flag -static-libc++)
            set(release_flag ${debug_flag})
        else()
            set(debug_flag "")
            set(release_flag "")
        endif()
    else()
        message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}.")
    endif()

    set(${ARG_RESULT_DEBUG_FLAGS} ${debug_flag}  PARENT_SCOPE)
    set(${ARG_RESULT_RELEASE_FLAGS} ${release_flag} PARENT_SCOPE)
endfunction()

function(gx_replace_c_cxx_runtime_flags)
    set(options STATIC_RUNTIME)
    set(one_value_args "")
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")

    if(ARG_STATIC_RUNTIME)
        set(runtime_flags STATIC_RUNTIME)
        set(reverse_runtime_flags "")
    else()
        set(runtime_flags "")
        set(reverse_runtime_flags STATIC_RUNTIME)
    endif()

    gx_make_c_cxx_runtime_flags(
        ${reverse_runtime_flags}
        RESULT_DEBUG_FLAGS reverse_debug_flags
        RESULT_RELEASE_FLAGS reverse_release_flags
    )

    string(REPLACE " " ";" reverse_debug_flag_list "${reverse_debug_flags}")
    string(REPLACE " " ";" reverse_release_flag_list "${reverse_release_flags}")

    gx_make_c_cxx_runtime_flags(
        ${runtime_flags}
        RESULT_DEBUG_FLAGS debug_flags
        RESULT_RELEASE_FLAGS release_flags
    )

    foreach(item IN LISTS reverse_debug_flag_list)
        string(REPLACE ${item} "" CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}")
        string(REPLACE ${item} "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    endforeach()

    foreach(item IN LISTS reverse_release_flag_list)
        string(REPLACE ${item} "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
        string(REPLACE ${item} "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
    endforeach()

    string(APPEND CMAKE_C_FLAGS_DEBUG " ${debug_flags}")
    string(APPEND CMAKE_CXX_FLAGS_DEBUG " ${debug_flags}")
    string(APPEND CMAKE_C_FLAGS_RELEASE " ${release_flags}")
    string(APPEND CMAKE_CXX_FLAGS_RELEASE " ${release_flags}")

    set(CMAKE_C_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG} PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} PARENT_SCOPE)
    set(CMAKE_C_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE} PARENT_SCOPE)
    set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} PARENT_SCOPE)
endfunction()
