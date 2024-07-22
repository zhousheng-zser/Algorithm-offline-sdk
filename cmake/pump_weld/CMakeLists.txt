set(target_name gx-pump_weld)
set(package_name GxPump_weld)

add_library(${target_name} SHARED)


if(WIN32)
	set(target_version 1.0.0)
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3588" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=1)
	set(GX_EMPOWER OFF)
	set(target_version 2.27.11)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3399" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=1)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=2)
	set(target_version 1.0.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3566" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=1)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=3)
	set(target_version 1.1.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=4)
	set(target_version 1.1.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "CENTOS" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=5)
	set(target_version 1.0.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "UBUNTU" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=6)
	set(GX_EMPOWER OFF)
	set(target_version 1.0.0)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1106" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=7)
	set(target_version 1.0.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "SOPHON" )
	set(GX_EMPOWER OFF)
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=8)
	set(GX_EMPOWER OFF)
	set(target_version 1.8.1)
elseif(GX_TOOLHAIN_TARGET_NAME STREQUAL  "SOPHON_UBUNTU" )
    target_compile_definitions(${target_name} PRIVATE EMPOWER_LANGUAGE=0)
    target_compile_definitions(${target_name} PRIVATE GX_PLATFORM_NAME=8)
	set(GX_EMPOWER OFF)
	set(target_version 1.0.0)
endif()

if(GX_EMPOWER)
    target_compile_definitions(${target_name} PRIVATE GX_EMPOWER_FLAG=true)
else()
    target_compile_definitions(${target_name} PRIVATE GX_EMPOWER_FLAG=false)
endif()
message("EMPOWER_LANGUAGE  = ${GX_TOOLHAIN_TARGET_NAME}" )
message("GX_EMPOWER_FLAG   = ${GX_EMPOWER}" )



file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/pump_weld/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/pump_weld/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/info_pump_weld.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/gx_pump_weld_api.hpp
)

target_sources(
	${target_name}
	PRIVATE ${private_sources})

target_include_directories(
	${target_name}
	PRIVATE
	${GX_PUBLIC_INCLUDE_DIR}/g6
	${THIRD_PARTY_INCLUDE_DIR}
	${OpenCV_INCLUDE_DIRS}
	${GX_CV_SDK_INCLUDE}
)

target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})
target_link_directories(${target_name} PRIVATE ${OpenCV_LIB_DIR})

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	${OpenCV_LIBS}
	${GX_CV_SDK_LIBS}
	gx-api  #公共图片处理  
)

#做鉴权的平台
if(GX_EMPOWER )
target_link_libraries(
	${target_name}
	PRIVATE
	LicenseClient::license_client
)
endif()

if((GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON") OR (GX_TOOLHAIN_TARGET_NAME STREQUAL "SOPHON_UBUNTU"))
    target_include_directories(${target_name} PRIVATE ${GX_OPENCV_ROOT}/include)
    target_link_directories(${target_name} PRIVATE ${GX_OPENCV_ROOT}/lib)
    target_link_libraries(${target_name} PRIVATE bmlib bmrt bmcv yuv bmjpuapi bmjpulite)
endif()

if(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3588")
target_link_libraries(
	${target_name}
	PRIVATE
	rknnrt
)
endif()


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