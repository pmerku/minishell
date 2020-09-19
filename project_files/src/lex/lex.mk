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

LEX_SOURCES = lex.c composite_str.c lex_chars.c lex_is_char.c lex_push.c \
	lex_read.c lex_str.c lex_token.c
LEX_SOURCES := $(addprefix $(LEX_DIR)/,$(LEX_SOURCES))

SRC			+= $(LEX_SOURCES)

HEADERS		+= ft_lex.h