cmake_minimum_required(VERSION 3.15)

project(EmbeddedStateMachineLib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(esml src/statemachine.cpp)

if (BUILD_EXAMPLES)
    include_directories(examples/basic/include)
    add_executable(example_basic examples/basic/src/main.cpp)

    target_link_libraries(example_basic esml)
endif ()