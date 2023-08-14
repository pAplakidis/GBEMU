cmake_minimum_required(VERSION 3.10)

project(GBEMU)

# use sdl2
find_package(SDL2 REQUIRED)
set(CMAKE_CXX_FLAGS "-DGL_GLEXT_PROTOTYPES")

set(CMAKE_BUILD_TYPE Debug)
set(SRCDIR "src/")

# fetch c++ files
include_directories("${SRCDIR}")
file(GLOB_RECURSE CC_SRCS RELATIVE ${CMAKE_SOURCE_DIR} "${SRCDIR}*.cc")
list(REMOVE_ITEM CC_SRCS "${SRCDIR}cpu.cc")
list(APPEND CC_SRCS "${SRCDIR}cpu.cc")

message(STATUS "C++ files: ${CC_SRCS}")
add_executable("${PROJECT_NAME}" ${CC_SRCS})

# link libraries
target_include_directories("${PROJECT_NAME}" PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries("${PROJECT_NAME}" PRIVATE SDL2main SDL2 GL)


