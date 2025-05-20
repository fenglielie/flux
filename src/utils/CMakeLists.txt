add_library(utils INTERFACE)
target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
zero_check_target(utils)

add_library(flux::utils ALIAS utils)
