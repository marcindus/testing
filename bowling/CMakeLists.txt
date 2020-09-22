cmake_minimum_required(VERSION 3.11)
project(bowling)

set(CMAKE_CXX_STANDARD 17)

# Get Googletest

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
)

FetchContent_GetProperties(googletest)
if (NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif ()

add_definitions(-Wno-unused-variable)
add_definitions(-Wno-unused-parameter)
add_definitions(-Wall -Werror -pedantic -Wextra)

add_executable(gtests testBowling.cpp Bowls.cpp testFiles.cpp Files.cpp testInterpreter.cpp Interpreter.cpp testPrinter.cpp Printer.cpp)
target_link_libraries(gtests gtest_main gmock_main)

add_executable(bowling bowling.cpp Bowls.cpp Files.cpp Interpreter.cpp Printer.cpp)