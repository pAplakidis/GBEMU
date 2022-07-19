cmake_minimum_required(VERSION 3.10)

project(GBEMU)

set(SRCDIR "src/")

include_directories("${SRCDIR}")
file(GLOB_RECURSE CC_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "${SRCDIR}*.cc")

list(REMOVE_ITEM CC_SRCS "${SRCDIR}cpu.cc")
list(APPEND CC_SRCS "${SRCDIR}cpu.cc")

message(STATUS "C++ files: ${CC_SRCS}")

add_executable("${PROJECT_NAME}" ${CC_SRCS})
