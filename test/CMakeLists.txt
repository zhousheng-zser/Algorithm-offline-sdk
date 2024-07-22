set(target_name gx-offline-recognition-test)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
    common.hpp
    #sophon.cpp
    test.cpp
    #nessus.cpp
    #face.cpp
)

add_executable(${target_name})

target_sources(
    ${target_name} 
    PRIVATE ${private_sources}
)

target_include_directories(
	${target_name}
	PRIVATE
	${GX_PUBLIC_INCLUDE_DIR}/g6
	${OpenCV_INCLUDE_DIRS}
)

target_link_directories(${target_name} PRIVATE ${OpenCV_LIB_DIR})

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	${OpenCV_LIBS}
	gx-api
	gx-helmet
	gx-flame
	gx-smog
	gx-posture
	gx-playphone
	gx-head
	gx-smoke
	gx-pedestrian
	gx-pedestrian_min
	gx-climb
	gx-tumble
	gx-crowd
	gx-sleep
	gx-fighting
	gx-refvest
	gx-batterypilferers
	gx-vehicle
	gx-wander
	gx-leavepost
	gx-workcloth
	gx-pump_light
	gx-pump_mask
	gx-pump_vesthelmet
)

if((GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON_UBUNTU"))
    target_include_directories(${target_name} PRIVATE ${GX_OPENCV_ROOT}/include)
    target_link_directories(${target_name} PRIVATE ${GX_OPENCV_ROOT}/lib)
    target_link_libraries(${target_name} PRIVATE bmlib bmrt bmcv yuv bmjpuapi bmjpulite)
endif()

if((GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL  "UBUNTU") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1106") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON_UBUNTU") )
    target_link_libraries( ${target_name} PRIVATE ${GX_CV_SDK_LIBS} )
    target_include_directories( ${target_name} PRIVATE ${GX_CV_SDK_INCLUDE} )
    target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})
endif()

set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

add_test(NAME ${target_name} COMMAND ${target_name})