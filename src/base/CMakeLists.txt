add_library(base INTERFACE)
target_include_directories(base INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
zero_check_target(base)

add_library(flux::base ALIAS base)
