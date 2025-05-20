add_executable(utils_test)
target_sources(utils_test PRIVATE
    error_test.cpp
    linespace_test.cpp
    period_index_test.cpp
    gaussquadrature_test.cpp
)
target_link_libraries(utils_test PRIVATE flux::base flux::utils gtest_main)


include(GoogleTest)
gtest_discover_tests(utils_test)
