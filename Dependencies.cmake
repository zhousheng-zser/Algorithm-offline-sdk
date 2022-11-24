include(${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/GXThirdPartyLibrary.cmake)

if(GX_STATIC_RUNTIME)
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=ON)
else()
    set(runtime_args CMAKE_ARGS -DGX_STATIC_RUNTIME=OFF)
endif()

if(CMAKE_CROSSCOMPILING)
    set(additional_args CMAKE_ARGS -DGX_TOOLCHAIN_PREFIX=${GX_TOOLCHAIN_PREFIX})
    set(toolchain_file ${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous/cmake/Armv7Toolchain.cmake)
else()
    set(additional_args "")
    set(toolchain_file "")
endif()

find_package(Threads REQUIRED)

gx_make_install_third_party_library(
    GXMiscellaneous
	REQUIRED
    PARALLEL_BUILD
    SYNC_BUILD_TYPE
    GENERATOR ${CMAKE_GENERATOR}
    ${runtime_args}
    ${additional_args}
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third-party/miscellaneous
    TOOLCHAIN_FILE ${toolchain_file}
)

gx_make_install_third_party_library(
    proxy
    PARALLEL_BUILD
    SYNC_BUILD_TYPE
    GENERATOR ${CMAKE_GENERATOR}
    ${runtime_args}
    ${additional_args}
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/third-party/proxy
    TOOLCHAIN_FILE ${toolchain_file}
)
