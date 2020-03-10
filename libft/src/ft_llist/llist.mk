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

LLIST_DIR		= ft_llist

LLIST_SOURCES 	= \
	ft_llist_clear.c \
	ft_llist_free.c \
	ft_llist_iter.c \
	ft_llist_new.c \
	ft_llist_push_back.c \
	ft_llist_push_front.c \
	ft_llist_size.c

LLIST_SOURCES 	:= $(addprefix $(LLIST_DIR)/,$(LLIST_SOURCES))

SRC 	+= $(LLIST_SOURCES)
HEADERS	+= ft_llist.h
