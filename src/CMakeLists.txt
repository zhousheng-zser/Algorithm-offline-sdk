set(target_version 0.1)
set(target_name gx-offline-face-recognition)
set(package_name GxOfflineFaceRecognition)

add_library(${target_name} SHARED)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.h
	nessus/*.hpp
	nessus/*.cpp
	nessus/protocols/*.hpp
	distance/*hpp
	distance/*cpp

	*.hpp
	*.cpp
)

if(NOT GX_USE_PURE_C)
	list(REMOVE_ITEM private_sources gx_face_api_c.cpp)
	list(REMOVE_ITEM private_sources ${CMAKE_CURRENT_SOURCE_DIR}/gx_face_api_c.cpp)
endif()

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
	${OpenCV_LIBS}
	${GX_CV_SDK_LIBS}
)
if(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RK3399" )
	target_include_directories(${target_name} PRIVATE ${GX_MISCELLANEOUS_ROOT}/include)
	target_link_directories(${target_name} PRIVATE ${GX_MISCELLANEOUS_ROOT}/lib)
	target_link_libraries(${target_name} PRIVATE gx-miscellaneous fmt)
else()
	target_link_libraries(${target_name} PRIVATE GXMiscellaneous::gx-miscellaneous)
endif()

if(GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109" )
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
