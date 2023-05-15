set(target_version 0.1)
set(target_name demo)
set(package_name Demo)

add_library(${target_name} SHARED)

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	*.hpp
	*.cpp
)

target_sources(
	${target_name}
	PRIVATE ${private_sources}
 )

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
)

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

