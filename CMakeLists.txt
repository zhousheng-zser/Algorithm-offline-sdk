cmake_minimum_required (VERSION 3.20)

project(gx-offline-face-recognition CXX)

option(GX_USE_PURE_C "Whether to compile C-style APIs." OFF)
option(GX_STATIC_RUNTIME "Whether to link C/C++ runtime statically." ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(GX_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

include(CTest)
include(Dependencies.cmake)

list(APPEND CMAKE_MODULE_PATH ${GX_MISCELLANEOUS_ROOT}/cmake)
if(GX_STATIC_RUNTIME)
    include(GXCCXXRuntime)
    gx_replace_c_cxx_runtime_flags(STATIC_RUNTIME)
endif()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(display)
#add_subdirectory(demo)
