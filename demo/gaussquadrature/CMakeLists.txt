add_executable(demo_gaussquadrature demo_gaussquadrature.cpp)
target_link_libraries(demo_gaussquadrature PRIVATE flux::base flux::utils)

zero_check_target(demo_gaussquadrature)
