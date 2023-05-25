if(GX_STATIC_RUNTIME)
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=ON)
else()
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=OFF)
endif()

if(CMAKE_CROSSCOMPILING)
    set(additional_args CMAKE_ARGS -DGX_TOOLCHAIN_PREFIX=${GX_TOOLCHAIN_PREFIX} -DGX_WITH_NET=OFF -DGX_WITH_TESTS=OFF -DGX_WITH_JNI=OFF)
else()
    set(additional_args "")
    set(toolchain_file "")
endif()

find_package(Threads REQUIRED)


if(WIN32)
    find_package(OpenCV REQUIRED HINTS ${GX_OPENCV_ROOT} NO_DEFAULT_PATH)
    find_package(
    GTest
    REQUIRED
    HINTS ${GX_GTEST_ROOT}/lib/cmake
    NO_DEFAULT_PATH
    )
    find_package(
    GXMiscellaneous
    REQUIRED
    HINTS ${GX_MISCELLANEOUS_ROOT}
    NO_DEFAULT_PATH
    )
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109" )
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
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "CENTOS" )
    find_package(
    GXMiscellaneous
    REQUIRED
    HINTS ${GX_MISCELLANEOUS_ROOT}
    NO_DEFAULT_PATH
    )
    find_package(
    GTest
    REQUIRED
    HINTS ${GX_GTEST_ROOT}/lib64/cmake
    NO_DEFAULT_PATH
    )
    set(OpenCV_LIB_DIR ${GX_OPENCV_ROOT}/lib64)
    set(OpenCV_INCLUDE_DIRS ${GX_OPENCV_ROOT}/include)
    set(OpenCV_LIBS opencv_calib3d opencv_core opencv_dnn opencv_features2d opencv_flann opencv_highgui opencv_imgproc opencv_imgcodecs opencv_ml opencv_objdetect opencv_photo opencv_shape opencv_stitching opencv_superres opencv_videoio opencv_video opencv_videostab)
elseif((GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3399" )OR(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3566"))
    include(${GX_MISCELLANEOUS_ROOT}/cmake/GXUtil.cmake)
    gx_find_package_no_root_path(
    GXMiscellaneous
    REQUIRED
    HINTS ${GX_MISCELLANEOUS_ROOT}
    NO_DEFAULT_PATH
    )
    gx_find_package_no_root_path(
    GTest
    REQUIRED
    HINTS ${GX_GTEST_ROOT}/lib/cmake
    NO_DEFAULT_PATH
    )
    set(OpenCV_LIB_DIR ${GX_OPENCV_ROOT}/sdk/native/libs/arm64-v8a)
    set(OpenCV_INCLUDE_DIRS ${GX_OPENCV_ROOT}/sdk/native/jni/include)
    set(OpenCV_LIBS opencv_java4)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3588" )
    include(${GX_MISCELLANEOUS_ROOT}/cmake/GXUtil.cmake)
    gx_find_package_no_root_path(
    GXMiscellaneous
    REQUIRED
    HINTS ${GX_MISCELLANEOUS_ROOT}/lib/cmake
    NO_DEFAULT_PATH
    )
    set(OpenCV_INCLUDE_DIRS ${GX_OPENCV_ROOT}/include/opencv4)
    set(OpenCV_LIB_DIR ${GX_OPENCV_ROOT}/lib)
    set(OpenCV_LIBS opencv_world)
endif()

if(WIN32)
    set(cvsdk_lib_relative_path "/lib/windows/x64/release")
    set(GX_CV_SDK_LIBS libparser)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109")
    set(cvsdk_lib_relative_path "/lib/rv1109/arm-linux-gnueabihf/release")
    set(GX_CV_SDK_LIBS damocles excalibur irisviel longinus parser plugin_register primitives romancia selene vision_service)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "CENTOS" )
    set(cvsdk_lib_relative_path "/lib/centos/x64/release")
    set(GX_CV_SDK_LIBS excalibur primitives selene irisviel parser damocles longinus plugin_register romancia vision_service)
elseif((GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3399" ))
    set(cvsdk_lib_relative_path "/lib/android/arm64-v8a/release")
    set(GX_CV_SDK_LIBS damocles excalibur irisviel longinus parser plugin_register primitives romancia selene vision_service)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3566")
    set(cvsdk_lib_relative_path "/lib/rk3566/android/arm64-v8a/release")
    set(GX_CV_SDK_LIBS damocles excalibur irisviel longinus parser plugin_register primitives romancia selene vision_service)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3588" )
    set(cvsdk_lib_relative_path "/lib/rk3588/aarch64-linux-gnu/release")
    set(GX_CV_SDK_LIBS damocles excalibur irisviel longinus parser plugin_register primitives romancia selene vision_service flame helmet refvest)
endif()

set(GX_CV_SDK_INCLUDE ${GX_CV_SDK_ROOT}/include)
set(GX_CV_SDK_LIB_DIR ${GX_CV_SDK_ROOT}${cvsdk_lib_relative_path})

message(STATUS "GX_CV_SDK_INCLUDE: ${GX_CV_SDK_INCLUDE}")
message(STATUS "GX_CV_SDK_LIB_DIR: ${GX_CV_SDK_LIB_DIR}")
