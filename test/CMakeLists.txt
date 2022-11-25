set(target_name gx-offline-face-recognition-test)


file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.hpp
	${GX_PUBLIC_INCLUDE_DIR}/g6/face/*.h
	../src/*.cpp
	../src/*.h
	*.hpp *.cpp *.h

)
add_executable(${target_name} )


target_sources(
	${target_name} 
	PRIVATE ${private_sources}
)

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
target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	GXMiscellaneous::gx-miscellaneous
	${OpenCV_LIBS}
	${GX_CV_SDK_LIBS}
)
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../config  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)


set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)
add_test(NAME ${target_name} COMMAND ${target_name})
