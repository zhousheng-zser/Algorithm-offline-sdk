include(${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/GXThirdPartyLibrary.cmake)

if(GX_STATIC_RUNTIME)
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=ON)
else()
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=OFF)
endif()

if(CMAKE_CROSSCOMPILING)
    set(additional_args CMAKE_ARGS -DGX_TOOLCHAIN_PREFIX=${GX_TOOLCHAIN_PREFIX} -DGX_WITH_NET=OFF -DGX_WITH_TESTS=OFF -DGX_WITH_JNI=OFF)
    set(toolchain_file ${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/RV1109Toolchain.cmake)
else()
    set(additional_args "")
    set(toolchain_file "")
endif()

find_package(Threads REQUIRED)




if(WIN32)
    find_package(OpenCV REQUIRED HINTS ${GX_OPENCV_ROOT} NO_DEFAULT_PATH)
    gx_make_install_third_party_library(
    GTest
	REQUIRED
    PARALLEL_BUILD
    SYNC_BUILD_TYPE
    GENERATOR ${CMAKE_GENERATOR}
    ${runtime_args}
    ${additional_args}
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third-party/googletest
    TOOLCHAIN_FILE ${toolchain_file}
    )
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
else()
    find_package(
    GXMiscellaneous
    REQUIRED
    HINTS ${GX_MISCELLANEOUS_ROOT}/lib/cmake
    NO_DEFAULT_PATH
    )
    find_package(
    GTest
    REQUIRED
    HINTS ${GX_GTEST_ROOT}/lib/cmake
    NO_DEFAULT_PATH
    )
    set(OpenCV_LIB_DIR ${GX_OPENCV_ROOT}/package/arm-linux-gnueabihf/lib)
    set(OpenCV_INCLUDE_DIRS ${GX_OPENCV_ROOT}/package/arm-linux-gnueabihf/include)
    set(OpenCV_LIBS opencv_core opencv_imgcodecs opencv_imgproc opencv_calib3d opencv_features2d opencv_flann opencv_highgui opencv_photo opencv_dnn.so.3.4.1 opencv_dnn.so opencv_ml opencv_video opencv_videoio opencv_videostab opencv_objdetect opencv_shape opencv_stitching opencv_superres)
endif()

if(WIN32)
    set(cvsdk_lib_relative_path "/lib/windows/x64/release")
    set(GX_CV_SDK_LIBS libparser)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    file(STRINGS /etc/os-release linux_distro_id REGEX "^ID=")
    string(REGEX REPLACE "ID=\"(.+)\"" "\\1" linux_distro_id "${linux_distro_id}")
    message("Found Linux Distro ID: ${linux_distro_id}")
    set(cvsdk_lib_relative_path "/lib/rv1109/arm-linux-gnueabihf/release")
    set(GX_CV_SDK_LIBS cassius damocles excalibur irisviel longinus parser plugin_register primitives romancia selene vision_service)
endif()

set(GX_CV_SDK_INCLUDE ${GX_CV_SDK_ROOT}/include)
set(GX_CV_SDK_LIB_DIR ${GX_CV_SDK_ROOT}${cvsdk_lib_relative_path})

message(STATUS "GX_CV_SDK_INCLUDE: ${GX_CV_SDK_INCLUDE}")
message(STATUS "GX_CV_SDK_LIB_DIR: ${GX_CV_SDK_LIB_DIR}")
