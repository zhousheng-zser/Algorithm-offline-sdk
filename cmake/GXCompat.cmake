include_guard()

function(gx_patch_compat_impl)
	set(options "")
    set(one_value_args TARGET TOOLCHAIN_TARGET_NAME BASE_DIR RESULT_CMAKE_FILE)
    set(multi_value_args "")
    cmake_parse_arguments(PARSE_ARGV 0 ARG "${options}" "${one_value_args}" "${multi_value_args}")
    gx_ensure_parameters(gx_patch_compat ARG TARGET TOOLCHAIN_TARGET_NAME RESULT_CMAKE_FILE)

	if(ARG_BASE_DIR)
		set(base_dir ${ARG_BASE_DIR})
	else()
		set(base_dir ${CMAKE_SOURCE_DIR})
	endif()

    string(TOLOWER "${ARG_TOOLCHAIN_TARGET_NAME}" toolchain_target_name)
	target_sources(${ARG_TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/compat/${toolchain_target_name}.cpp)

	set(cmake_file ${base_dir}/cmake/compat/${toolchain_target_name}.cmake)

	if(NOT EXISTS ${cmake_file})
		message(FATAL_ERROR "\"${cmake_file}\" does not exist.")
	endif()

	set(${ARG_RESULT_CMAKE_FILE} ${cmake_file} PARENT_SCOPE)
endfunction()

macro(gx_patch_compat)
	gx_patch_compat_impl(
		${ARGN}
		RESULT_CMAKE_FILE gx_patch_compat_cmake_file
	)

	include(${gx_patch_compat_cmake_file})
	unset(gx_patch_compat_cmake_file)
endmacro()
