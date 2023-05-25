set(target_name display-test)


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
    PRIVATE
	${OpenCV_INCLUDE_DIRS}
    mpp/*.hpp
)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FMT REQUIRED fmt)


message(STATUS "FMT_LIBRARY_DIRS: ${FMT_LIBRARY_DIRS}")
message(STATUS "FMT_LIBRARIES: ${FMT_LIBRARIES}")
message(STATUS "FMT_INCLUDE_DIRS: ${FMT_INCLUDE_DIRS}")

target_include_directories(${target_name}
PUBLIC
        $<BUILD_INTERFACE:${GX_PUBLIC_INCLUDE_DIR}>
        $<INSTALL_INTERFACE:include>
PRIVATE
        ${GX_PUBLIC_INCLUDE_DIR}/g6/face
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_directories(${target_name} PRIVATE 
${OpenCV_LIB_DIR} 
${FMT_LIBRARY_DIRS}
)

target_link_libraries(
    ${target_name}
    PRIVATE
    Threads::Threads
	${OpenCV_LIBS}
    /root/install/mmp/libgx-mpp.so
    ${FMT_LIBRARIES}
	gx-offline-face-recognition
    GXMiscellaneous::gx-miscellaneous
)



set_target_properties(${target_name}
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
add_test(NAME ${target_name} COMMAND ${target_name})
