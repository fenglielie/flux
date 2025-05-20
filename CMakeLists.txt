cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(flux VERSION 1.0)
include(cmake/zero.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

zero_setup()
zero_check()


add_subdirectory(src)

add_subdirectory(demo)

add_subdirectory(examples)

include(CTest)
if(BUILD_TESTING)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE) # Disable GMock

    FetchContent_MakeAvailable(googletest)

    add_subdirectory(test)
endif()
