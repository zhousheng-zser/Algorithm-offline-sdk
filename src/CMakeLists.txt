set(target_version 0.1)
set(target_name gx-offline-face-recognition)
set(package_name GxOfflineFaceRecognition)

add_library(${target_name} SHARED)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.h
	nessus/*.h
	nessus/*.hpp
	nessus/*.cpp
	nessus/protocols/*.hpp
	*.hpp
	*.cpp
	*.h
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
	PUBLIC
		$<BUILD_INTERFACE:${GX_PUBLIC_INCLUDE_DIR}>
		$<INSTALL_INTERFACE:include>
	PRIVATE
		${GX_PUBLIC_INCLUDE_DIR}/g6/face
		${CMAKE_CURRENT_SOURCE_DIR}
		${OpenCV_INCLUDE_DIRS}
		${GX_CV_SDK_INCLUDE}
)

target_compile_definitions(${target_name} PRIVATE GX_IS_FACE_IMPL=1)
target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})
target_link_directories(${target_name} PRIVATE ${OpenCV_LIB_DIR})

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	GXMiscellaneous::gx-miscellaneous
	${OpenCV_LIBS}
	${GX_CV_SDK_LIBS}
)

if(NOT WIN32)
target_link_libraries(
	${target_name}
	PRIVATE
	dl
	rknn_api
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

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../config  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)

include(GXPackaging)

gx_make_install_package(
	TARGET_NAME ${target_name}
	PACKAGE_NAME ${package_name}
	TARGET_VERSION ${target_version}
)
