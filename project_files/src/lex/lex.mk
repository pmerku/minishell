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

CURRENT_DIR		= lex

CURRENT_SOURCES = lex.c
CURRENT_SOURCES := $(addprefix $(CURRENT_DIR)/,$(CURRENT_SOURCES))

SRC				+= $(CURRENT_SOURCES)

HEADERS			+= lex.h