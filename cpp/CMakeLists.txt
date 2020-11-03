cmake_minimum_required(VERSION 3.10)

project(P5 VERSION 0.1)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp" "src/graph/*" "src/aco/*")
message("${SOURCES}")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp" )
file(GLOB TEST_SOURCES "tests/*.cpp")

include_directories(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
include_directories("/src")
include_directories(graph)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-pthread -g")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(apicaller)

add_executable(routeplanner
        "src/main.cpp"
        ${SOURCES}
        )
target_link_libraries(routeplanner ${PYTHON_LIBRARIES} apicaller)

# testing
include(CTest)
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(tests
        ${TEST_SOURCES}
        ${SOURCES}
        )
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES})
target_link_libraries(tests ${PYTHON_LIBRARIES} apicaller)

gtest_discover_tests(tests)

