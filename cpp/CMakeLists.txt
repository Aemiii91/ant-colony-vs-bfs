cmake_minimum_required(VERSION 3.10)

project(P5 VERSION 0.1)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")
message("${SOURCES}")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories("/src")
include_directories("tests/*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pthread")


add_executable(p5
        "src/main.cpp"
        ${SOURCES}
        )

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
        ${TEST_SOURCES}
        ${SOURCES}
        )
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES})



