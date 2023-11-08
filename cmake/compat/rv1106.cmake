include_guard()
string(APPEND CMAKE_C_FLAGS " ${c_cxx_linker_flags}")
string(APPEND CMAKE_CXX_FLAGS " ${c_cxx_linker_flags}")
unset(c_cxx_linker_flags)
