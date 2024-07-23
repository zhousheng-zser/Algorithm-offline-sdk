set(target_name gx-api)
set(package_name GxApi)
#set(target_version 1.0.0)

add_library(${target_name} SHARED)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/gx_api/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/../../src/gx_api/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/gx_api.hpp
)

target_sources(
	${target_name}
	PRIVATE ${private_sources})

target_include_directories(
	${target_name}	
	PRIVATE 
	${GX_PUBLIC_INCLUDE_DIR}
)

target_link_directories(
	${target_name}
	PRIVATE 
	${OpenCV_LIB_DIR}
)

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	${OpenCV_LIBS}
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

include(GXPackaging)

#gx_make_install_package(
#	TARGET_NAME ${target_name}
#	PACKAGE_NAME ${package_name}
#	TARGET_VERSION ${target_version}
#)