cmake_minimum_required (VERSION 3.20)
project(gx-offline-recognition CXX)

option(GX_EMPOWER "Use LicenseClient" ON)
option(GX_STATIC_RUNTIME "Whether to link C/C++ runtime statically." ON)


set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(GX_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(THIRD_PARTY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
if(GX_STATIC_RUNTIME)
    include(GXCCXXRuntime)
    gx_replace_c_cxx_runtime_flags(STATIC_RUNTIME)
endif()


include(Dependencies.cmake)

#全局链接opencv
include_directories(
	${GX_PUBLIC_INCLUDE_DIR}/g6
	${OpenCV_INCLUDE_DIRS}
)
link_directories(${OpenCV_LIB_DIR})

if((GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON_UBUNTU"))
    include_directories(${GX_OPENCV_ROOT}/include)
    link_directories(${GX_OPENCV_ROOT}/lib)
    message("${GX_OPENCV_ROOT}/lib" )
    link_libraries(bmlib bmrt bmcv yuv bmjpuapi bmjpulite)
endif()


add_subdirectory(cmake/gx_api)
add_subdirectory(cmake/posture)
add_subdirectory(cmake/head)
add_subdirectory(cmake/pedestrian)
add_subdirectory(cmake/batterypilferers)
add_subdirectory(cmake/pedestrian_min)
add_subdirectory(cmake/playphone)
add_subdirectory(cmake/smog)
add_subdirectory(cmake/leavepost)
add_subdirectory(cmake/flame)
add_subdirectory(cmake/climb)
add_subdirectory(cmake/tumble)
add_subdirectory(cmake/crowd)
add_subdirectory(cmake/fighting)
add_subdirectory(cmake/helmet)
add_subdirectory(cmake/refvest)
add_subdirectory(cmake/sleep)
add_subdirectory(cmake/smoke)
add_subdirectory(cmake/vehicle)
add_subdirectory(cmake/wander)
add_subdirectory(cmake/workcloth)
add_subdirectory(cmake/pump_light)
add_subdirectory(cmake/pump_mask)
add_subdirectory(cmake/pump_vesthelmet)
add_subdirectory(cmake/pumptop_helmet)
add_subdirectory(cmake/pump_gate_status)
add_subdirectory(cmake/pump_hoisting)
add_subdirectory(cmake/pump_weld)
add_subdirectory(cmake/pump_pumptop_person)
add_subdirectory(cmake/pump_work_status)
add_subdirectory(cmake/crossing)
add_subdirectory(cmake/onphone)
add_subdirectory(cmake/climb_tumble_pedestrian)
add_subdirectory(test)