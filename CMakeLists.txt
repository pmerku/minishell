cmake_minimum_required(VERSION 3.15)
project(minishell C)

set(CMAKE_C_STANDARD 11)

include_directories(libft/include)
include_directories(project_files/incl)

add_library(libft
        libft/include/ft_stdio/ft_printf.h
        libft/include/ft_stdio/ft_printf_utils.h
        libft/include/ft_ctype.h
        libft/include/ft_libft.h
        libft/include/ft_memory.h
        libft/include/ft_stdlib.h
        libft/include/ft_string.h
        libft/include/ft_unistd.h
        libft/include/ft_math.h
        libft/include/ft_llist.h
        libft/src/ft_stdio
        libft/src/ft_ctype
        libft/src/ft_memory
        libft/src/ft_string
        libft/src/ft_unistd
        libft/src/ft_stdlib
        libft/src/ft_libft
        libft/src/ft_llist
        libft/src/ft_math
        )

add_executable(minishell
        project_files/src/main.c
        project_files/src/lex/lex.c
        project_files/incl/ft_lex.h
        project_files/incl/ft_env.h
        project_files/src/env/env.c
        project_files/incl/ft_parser.h)
