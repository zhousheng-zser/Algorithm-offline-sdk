set(target_name gx-offline-recognition-test)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
    common.hpp
    sophon_test.cpp
    #rk3588_test.cpp
)

add_executable(${target_name})

target_sources(
    ${target_name} 
    PRIVATE ${private_sources}
)

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
	gx-pumptop_helmet
	gx-pump_gate_status
	gx-pump_hoisting
	gx-pump_weld
	gx-pump_pumptop_person
	gx-pump_work_status
	gx-crossing
	gx-onphone
	gx-climb_tumble_pedestrian
)

#Ìí¼Óparser primitives
target_link_libraries( ${target_name} PRIVATE ${GX_CV_SDK_LIBS} )
target_include_directories( ${target_name} PRIVATE ${GX_CV_SDK_INCLUDE} )
target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})

set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

add_test(NAME ${target_name} COMMAND ${target_name})