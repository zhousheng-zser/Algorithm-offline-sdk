set(target_name gx-offline-face-recognition-test)

add_executable(${target_name} ${headers_and_sources})

file(
	GLOB private_sources
	CONFIGURE_DEPENDS
	*.hpp *.cpp *.h
)

target_sources(${target_name} PRIVATE ${private_sources})

target_link_libraries(
	${target_name}
	PRIVATE
	Threads::Threads
	gx-offline-face-recognition
	GXMiscellaneous::gx-miscellaneous
)

set_target_properties(${target_name}
	PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
)

add_test(NAME ${target_name} COMMAND ${target_name})
