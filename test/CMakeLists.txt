set(target_name gx-offline-recognition-test)


file(
	GLOB private_sources
    CONFIGURE_DEPENDS
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
        ${GX_PUBLIC_INCLUDE_DIR}/g6
        ${CMAKE_CURRENT_SOURCE_DIR}
		${GX_CV_SDK_INCLUDE}
		${OpenCV_INCLUDE_DIRS}
)

target_compile_definitions(${target_name} PRIVATE GX_IS_FACE_IMPL=1)
target_link_directories(${target_name} PRIVATE ${OpenCV_LIB_DIR})
target_link_libraries(
    ${target_name}
    PRIVATE
    Threads::Threads
	${OpenCV_LIBS}
    GXMiscellaneous::gx-miscellaneous
	gx-offline-recognition
)

if((GX_TOOLHAIN_TARGET_NAME STREQUAL  "RV1109")OR(GX_TOOLHAIN_TARGET_NAME STREQUAL  "UBUNTU")  )
    target_link_libraries( ${target_name} PRIVATE ${GX_CV_SDK_LIBS} )
    target_include_directories( ${target_name} PRIVATE ${GX_CV_SDK_INCLUDE} )
    target_link_directories(${target_name} PRIVATE ${GX_CV_SDK_LIB_DIR})
endif()

execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config
COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../config  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/config)


if(Win32)   ##### windows debug 
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi")   #设置调试信息格式
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF") #设置生成调制信息为:生成经过优化以共享和发布的调试信息(可执行文件)
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG:FULL /OPT:REF /OPT:ICF")  #设置生成调制信息__生成经过优化以共享和发布的调试信息(链接库)
endif()

set_target_properties(${target_name}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
add_test(NAME ${target_name} COMMAND ${target_name})
