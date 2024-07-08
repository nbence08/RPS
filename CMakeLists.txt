cmake_minimum_required(VERSION 3.10)
project(RockPaperScissors VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(BuildFunctions.cmake)

set(RPS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PRIMARY_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

option(verbose "verbose" OFF)

# add_subdirectory(core)
# add_subdirectory(components)
# add_subdirectory(io)
# add_subdirectory(rendering)
# add_subdirectory(GPU)
# add_subdirectory(resources)
add_subdirectory(main)
