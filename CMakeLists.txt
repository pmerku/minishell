cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_CXX_STANDARD 14)

include_directories(libft/include)
include_directories(libft/include/ft_stdio)
include_directories(project_files/incl)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)
file(GLOB_RECURSE PROJECT_FILES project_files/**.c)

add_executable(minishell ${PROJECT_FILES})
target_link_libraries(minishell libft)
