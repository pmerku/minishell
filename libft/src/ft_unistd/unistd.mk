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

UNISTD_DIR		= ft_unistd

UNISTD_SOURCES	= \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_read.asm \
	ft_write.asm

UNISTD_SOURCES	:= $(addprefix $(UNISTD_DIR)/,$(UNISTD_SOURCES))

SRC		+= $(UNISTD_SOURCES)
HEADERS	+= ft_unistd.h
