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

STDIO_DIR		= ft_stdio/ft_printf

STDIO_SOURCES	= ft_eprintf.c ft_fprintf.c ft_printf.c ft_snprintf.c \
	ft_vfprintf.c ft_vprintf.c
STDIO_SOURCES	+= buf/buf_chars_printed.c buf/buf_flush.c buf/buf_putchar.c \
	buf/buf_putchars.c buf/buf_putstr.c buf/buf_putstri.c buf/buf_reset.c
STDIO_SOURCES	+= buf/fd/buf_fd_chars_printed.c buf/fd/buf_fd_create.c \
	buf/fd/buf_fd_flush.c buf/fd/buf_fd_putchar.c buf/fd/buf_fd_putchars.c \
	buf/fd/buf_fd_putstr.c buf/fd/buf_fd_putstri.c buf/fd/buf_fd_reset.c
STDIO_SOURCES	+= buf/str/buf_str_chars_printed.c buf/str/buf_str_create.c \
	buf/str/buf_str_flush.c buf/str/buf_str_putchar.c \
	buf/str/buf_str_putchars.c buf/str/buf_str_putstr.c \
	buf/str/buf_str_putstri.c buf/str/buf_str_reset.c
STDIO_SOURCES	+= spec/spec_base.c spec/spec_char.c spec/spec_charsprinted.c \
	spec/spec_get.c spec/spec_ptr.c spec/spec_signed_int.c spec/spec_string.c \
	spec/spec_unsigned_int.c
STDIO_SOURCES	+= utils/fmt_read.c utils/ft_inner_printf.c utils/ft_lltoa.c \
	utils/ft_pf_atoi.c utils/ft_ulltoa.c utils/ft_ulltoa_base.c
STDIO_SOURCES 	:= $(addprefix $(STDIO_DIR)/,$(STDIO_SOURCES))

SRC 	+= $(STDIO_SOURCES)
HEADERS	+= ft_stdio/ft_printf.h ft_stdio/ft_printf_utils.h
