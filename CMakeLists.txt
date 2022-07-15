cmake_minimum_required(VERSION 3.10)

project(GBEMU)

file(GLOB_RECURSE CC_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cc")
message(STATUS "C++ files: ${CC_SRCS}")

add_executable("${PROJECT_NAME}" ${CC_SRCS})
