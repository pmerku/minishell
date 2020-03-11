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

MATH_DIR		= ft_math

MATH_SOURCES	= ft_pow.c
MATH_SOURCES 	:= $(addprefix $(MATH_DIR)/,$(MATH_SOURCES))

SRC 	+= $(MATH_SOURCES)
HEADERS	+= ft_math.h
