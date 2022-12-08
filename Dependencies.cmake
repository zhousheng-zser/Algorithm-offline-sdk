include(${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/GXThirdPartyLibrary.cmake)

if(GX_STATIC_RUNTIME)
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=ON)
else()
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=OFF)
endif()

if(CMAKE_CROSSCOMPILING)
    set(additional_args CMAKE_ARGS -DGX_TOOLCHAIN_PREFIX=${GX_TOOLCHAIN_PREFIX})
    set(toolchain_file ${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/Armv7Toolchain.cmake)
else()
    set(additional_args "")
    set(toolchain_file "")
endif()

find_package(Threads REQUIRED)

gx_make_install_third_party_library(
    GXMiscellaneous
	REQUIRED
    PARALLEL_BUILD
    SYNC_BUILD_TYPE
    GENERATOR ${CMAKE_GENERATOR}
    ${runtime_args}
    ${additional_args}
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous
    TOOLCHAIN_FILE ${toolchain_file}
)

message(STATUS "GX_OPENCV_ROOT: ${GX_OPENCV_ROOT}")
find_package(OpenCV REQUIRED HINTS ${GX_OPENCV_ROOT} NO_DEFAULT_PATH)

if(WIN32)
    set(cvsdk_lib_relative_path "/lib/windows/x64/release")
    set(GX_CV_SDK_LIBS libparser)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(STRINGS /etc/os-release linux_distro_id REGEX "^ID=")
    string(REGEX REPLACE "ID=\"(.+)\"" "\\1" linux_distro_id "${linux_distro_id}")
    message("Found Linux Distro ID: ${linux_distro_id}")
    set(cvsdk_lib_relative_path "/lib/windows/${linux_distro_id}/release")
    set(GX_CV_SDK_LIBS parser)
endif()

set(GX_CV_SDK_INCLUDE ${GX_CV_SDK_ROOT}/include)
set(GX_CV_SDK_LIB_DIR ${GX_CV_SDK_ROOT}${cvsdk_lib_relative_path})

message(STATUS "GX_CV_SDK_INCLUDE: ${GX_CV_SDK_INCLUDE}")
