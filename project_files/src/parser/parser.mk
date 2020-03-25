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

PARSER_SOURCES = parser.c
PARSER_SOURCES := $(addprefix $(PARSER_DIR)/,$(PARSER_SOURCES))

SRC	+= $(PARSER_SOURCES)

HEADERS += ft_parser.h