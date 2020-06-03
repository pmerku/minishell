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

EXEC_DIR		= exec

EXEC_SOURCES 	= exec.c exec_builtins.c
EXEC_SOURCES 	:= $(addprefix $(EXEC_DIR)/,$(EXEC_SOURCES))

SRC		+= $(EXEC_SOURCES)
HEADERS	+= ft_exec.h builtins.h