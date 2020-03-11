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

DLLIST_DIR		= ft_dllist

DLLIST_SOURCES	=

DLLIST_SOURCES	:= $(addprefix $(DLLIST_DIR)/,$(DLLIST_SOURCES))

SRC		+= $(DLLIST_SOURCES)
HEADERS	+= ft_dllist.h
