set(target_version 1.0.0)
set(target_name gx-nessus)
set(package_name GxNessus)

add_library(${target_name})

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.hpp
	*.hpp
	*.cpp
	protocols/*.hpp
	protocols/*.cpp
)

target_sources(
	${target_name}
	PRIVATE ${private_sources}
)

if(NOT "${GX_TOOLHAIN_TARGET_NAME}" STREQUAL "")
	include(GXCompat)
	gx_patch_compat(
		TARGET ${target_name}
		TOOLCHAIN_TARGET_NAME ${GX_TOOLHAIN_TARGET_NAME}
	)
endif()

target_include_directories(
	${target_name}
	PRIVATE
		../${GX_PUBLIC_INCLUDE_DIR}/g6/hotrail
		${CMAKE_CURRENT_SOURCE_DIR}
		${GX_CV_SDK_INCLUDE}
)

target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	GXMiscellaneous::gx-miscellaneous
	${GX_CV_SDK_LIBS}
)

set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)
