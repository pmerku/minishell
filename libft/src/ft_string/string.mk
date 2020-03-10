# **************************************************************************** #
#                                                                              #
#    Project: custom_libc                                 ::::::::             #
#    Members: dvoort, prmerku                           :+:    :+:             #
#    Copyright: 2020                                   +:+                     #
#                                                     +#+                      #
#                                                    +#+                       #
#                                                   #+#    #+#                 #
#    while (!(succeed = try()));                   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

STRING_DIR		= ft_string

STRING_SOURCES 	= \
	ft_memccpy.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.asm \
	ft_memmove.c \
	ft_memset.c \
	ft_strchr.c \
	ft_strcmp.asm \
	ft_strcpy.asm \
	ft_strdup.asm \
	ft_strlen.asm \
	ft_strncmp.c \
	ft_strnlen.c \
	ft_strnstr.c \
	ft_strrchr.c

STRING_SOURCES := $(addprefix $(STRING_DIR)/,$(STRING_SOURCES))

SRC 	+= $(STRING_SOURCES)
HEADERS	+= ft_string.h
