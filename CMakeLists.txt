cmake_minimum_required(VERSION 3.15)

project(EmbeddedStateMachineLib)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(esml src/statemachine.cpp)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

if (BUILD_TESTS)
    add_subdirectory(test)
endif ()