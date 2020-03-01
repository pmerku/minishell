# **************************************************************************** #
#                                                                              #
#    Project: minishell                                   ::::::::             #
#    Members: dvoort, prmerku                           :+:    :+:             #
#    Copyright: 2020                                   +:+                     #
#                                                     +#+                      #
#                                                    +#+                       #
#                                                   #+#    #+#                 #
#    while (!(succeed = try()));                   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

LEX_DIR		= lex

LEX_SOURCES = lex.c
LEX_SOURCES := $(addprefix $(LEX_DIR)/,$(LEX_SOURCES))

SRC			+= $(LEX_SOURCES)

HEADERS		+= ft_lex.h