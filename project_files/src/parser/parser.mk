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

PARSER_DIR		= parser

PARSER_SOURCES = parser.c parser_utils.c count_commands.c \
	parser_redirections.c parser_command.c handle_token.c
PARSER_SOURCES := $(addprefix $(PARSER_DIR)/,$(PARSER_SOURCES))

SRC	+= $(PARSER_SOURCES)

HEADERS += ft_parser.h