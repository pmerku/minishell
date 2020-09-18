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

EXEC_SOURCES 	= exec.c utils.c
EXEC_SOURCES	+= builtins/cd.c builtins/echo.c builtins/env.c \
	builtins/env.c builtins/exit.c builtins/pwd.c builtins/empty.c
EXEC_SOURCES 	:= $(addprefix $(EXEC_DIR)/,$(EXEC_SOURCES))

SRC		+= $(EXEC_SOURCES)
HEADERS	+= ft_exec.h builtins.h