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

ENV_DIR		= env

ENV_SOURCES = env.c env_string.c env_path.c
ENV_SOURCES := $(addprefix $(ENV_DIR)/,$(ENV_SOURCES))

SRC			+= $(ENV_SOURCES)

HEADERS		+= ft_env.h