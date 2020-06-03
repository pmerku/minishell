cmake_minimum_required(VERSION 3.10)
project(libft C)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB_RECURSE SOURCES src/**.c)
add_library(libft STATIC ${SOURCES})
