set(target_name restruct-test)


file(
	GLOB private_sources
    CONFIGURE_DEPENDS
    nessus.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}
		${OpenCV_INCLUDE_DIRS}
        "/root/Glasssix_CV_SDK_beta-restruct/include"
)

target_link_directories(${target_name} PRIVATE ${OpenCV_LIB_DIR}
"/root/Glasssix_CV_SDK_beta-restruct/lib/rk3588/aarch64-linux-gnu/release"
)

target_link_libraries(
    ${target_name}
    PRIVATE
    Threads::Threads
	${OpenCV_LIBS}
        primitives
        parser
        excalibur
)


set_target_properties(${target_name}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
add_test(NAME ${target_name} COMMAND ${target_name})
