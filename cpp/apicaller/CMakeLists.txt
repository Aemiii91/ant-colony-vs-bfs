cmake_minimum_required(VERSION 3.10)

file(GLOB PYTHON_BINDINGS_SRC "src/*.hpp" "src/*.cpp")

find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})

add_library(apicaller ${PYTHON_BINDINGS_SRC})
target_link_libraries(apicaller ${PYTHON_LIBRARIES})

target_include_directories(apicaller PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")