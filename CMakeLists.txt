cmake_minimum_required(VERSION 4.2)
project(vector)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(googletest)

add_executable(vector
        main.cpp
        Vector.cpp
)

add_executable(vector_tests
        VectorTests.cpp
)

target_link_libraries(vector_tests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(vector_tests)