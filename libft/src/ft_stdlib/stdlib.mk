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

STDLIB_DIR		= ft_stdlib

STDLIB_SOURCES 	= \
	ft_abs.c \
	ft_atoi.c \
	ft_dabs.c \
	ft_max.c \
	ft_min.c

STDLIB_SOURCES 	:= $(addprefix $(STDLIB_DIR)/,$(STDLIB_SOURCES))

SRC 	+= $(STDLIB_SOURCES)
HEADERS	+= ft_stdlib.h
