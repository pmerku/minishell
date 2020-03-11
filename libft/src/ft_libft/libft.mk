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

LIBFT_DIR		= ft_libft

LIBFT_SOURCES	= ft_intlen.c ft_intlen_base.c ft_itoa.c ft_itoa_base.c \
	ft_nsplit.c ft_split.c ft_strarr_append.c ft_strarr_size.c ft_strempty.c \
	ft_strip_chars.c ft_strjoin.c ft_strtrim.c ft_substr.c get_next_line.c
LIBFT_SOURCES 	:= $(addprefix $(LIBFT_DIR)/,$(LIBFT_SOURCES))

SRC 	+= $(LIBFT_SOURCES)
HEADERS	+= ft_libft.h
