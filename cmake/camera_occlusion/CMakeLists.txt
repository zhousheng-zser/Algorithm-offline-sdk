set(target_name gx-camera_occlusion)
set(package_name GxCamera_occlusion)

add_library(${target_name} SHARED)


if(WIN32)
	set(target_version 1.0.0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3588" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=1)
	set(target_version 2.27.11)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3399" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=2)
	set(target_version 1.0.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3566" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=3)
	set(target_version 1.1.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=4)
	set(target_version 1.1.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "CENTOS" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=5)
	set(target_version 1.0.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "UBUNTU" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=6)
	set(target_version 1.0.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1106" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=7)
	set(target_version 1.0.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "SOPHON" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=8)
	set(target_version 1.8.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "SOPHON_UBUNTU" )
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=8)
	set(target_version 1.0.0)
endif()

message("EMPOWER_LANGUAGE  = ${GX_TOOLHAIN_TARGET_NAME}" )


file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/camera_occlusion/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/camera_occlusion/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/gx_camera_occlusion_api.hpp
)

target_sources(
	${target_name}
	PRIVATE ${private_sources})

target_include_directories(
	${target_name}
	PRIVATE
	${GX_PUBLIC_INCLUDE_DIR}/g6
	${THIRD_PARTY_INCLUDE_DIR}
	${GX_CV_SDK_INCLUDE}
)

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	${OpenCV_LIBS}
	gx-api  #公共图片处理  
)

if( (GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109" ) OR (GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1106" )  )
target_link_libraries(
	${target_name}
	PRIVATE
	dl
)
endif()

set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	target_link_options(
		${target_name}
		PRIVATE
		LINKER:-Bsymbolic
	)

	set_target_properties(${target_name}
		PROPERTIES
		CXX_VISIBILITY_PRESET hidden
	)
endif()

#include(GXPackaging)
#
#gx_make_install_package(
#	TARGET_NAME ${target_name}
#	PACKAGE_NAME ${package_name}
#	TARGET_VERSION ${target_version}
#)