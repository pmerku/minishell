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

MEMORY_DIR		= ft_memory

MEMORY_SOURCES	= ft_bzero.c ft_calloc.c ft_checked_calloc.c \
	ft_checked_malloc.c ft_free.c ft_free_array.c ft_malloc.c ft_nullcheck.c
MEMORY_SOURCES	:= $(addprefix $(MEMORY_DIR)/,$(MEMORY_SOURCES))

SRC 	+= $(MEMORY_SOURCES)
HEADERS	+= ft_memory.h
