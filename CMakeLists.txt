# Project Setup
cmake_minimum_required(VERSION 3.13)
project(aul LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Global include dirs
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find all source files
file(GLOB aul_src CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/**/*.cpp
        ${PROJECT_SOURCE_DIR}/src/repl.cpp
        )

# Setup main repl exec
add_executable(aul ${aul_src})
target_link_libraries(aul readline)

# Fetch Catch2 from git
Include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)
FetchContent_MakeAvailable(Catch2)

# Find all test files (and include source files)
file(GLOB aul_test CONFIGURE_DEPENDS
        ${PROJECT_SOURCE_DIR}/src/**/*.cpp
        ${PROJECT_SOURCE_DIR}/test/*.cpp
        )

# Setup test exec
add_executable(aul_test ${aul_test})
target_link_libraries(aul_test PRIVATE Catch2::Catch2WithMain)
