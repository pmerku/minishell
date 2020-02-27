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

# Constants
NAME			= libft.a

# Compiler
COMPILE_FLAGS	= -Wall -Werror -Wextra
DEBUG_FLAG		= -O3

# Files
SRC_DIR			= src
OUT_DIR			= out
SRC				= ft_strcpy.c ft_min.c ft_dabs.c \
	ft_max.c ft_abs.c ft_strchr.c ft_strip_chars.c \
	ft_nullcheck.c ft_checked_malloc.c ft_checked_calloc.c ft_strarr_append.c \
	ft_strdup.c ft_strempty.c ft_strtrim.c ft_calloc.c ft_isdigit.c ft_atoi.c \
	ft_bzero.c ft_free.c ft_malloc.c ft_memset.c ft_split.c ft_strcmp.c \
	ft_strdup.c ft_strends_with.c ft_isspace.c ft_stris_empty.c ft_strlen.s \
	ft_strarr_free.c ft_nsplit.c ft_exit.c ft_strarr_size.c ft_substr.c
SRC				+= printf/ft_eprintf.c printf/ft_fprintf.c \
	printf/ft_vfprintf.c printf/ft_vprintf.c printf/spec/spec_base.c \
	printf/spec/spec_charsprinted.c printf/spec/spec_ptr.c \
	printf/spec/spec_signed_int.c printf/spec/spec_string.c \
	printf/spec/spec_unsigned_int.c printf/spec/spec_char.c \
	printf/spec/spec_get.c printf/ft_printf.c printf/utils/ft_pf_atoi.c \
	printf/utils/fmt_read.c printf/utils/ft_inner_printf.c \
	printf/buf/buf_chars_printed.c printf/buf/buf_flush.c \
	printf/buf/buf_putchar.c printf/buf/buf_putchars.c \
	printf/buf/buf_putstr.c printf/buf/buf_putstri.c printf/buf/buf_reset.c \
	printf/buf/fd/buf_fd_create.c printf/buf/fd/buf_fd_flush.c \
	printf/buf/fd/buf_fd_putchar.c printf/buf/fd/buf_fd_putchars.c \
	printf/buf/fd/buf_fd_putstr.c printf/buf/fd/buf_fd_putstri.c \
	printf/buf/fd/buf_fd_reset.c printf/buf/fd/buf_fd_chars_printed.c \
	printf/buf/str/buf_str_create.c printf/buf/str/buf_str_flush.c \
	printf/buf/str/buf_str_putchar.c printf/buf/str/buf_str_putchars.c \
	printf/buf/str/buf_str_putstr.c printf/buf/str/buf_str_putstri.c \
	printf/buf/str/buf_str_reset.c printf/buf/str/buf_str_chars_printed.c \
	printf/utils/ft_ulltoa.c printf/utils/ft_ulltoa_base.c \
	printf/utils/ft_lltoa.c printf/ft_snprintf.c
SRC				+= collections/linked_list/linked_list_clear.c \
	collections/linked_list/linked_list_free.c \
	collections/linked_list/linked_list_iter.c \
	collections/linked_list/linked_list_new.c \
	collections/linked_list/linked_list_push_back.c \
	collections/linked_list/linked_list_push.c \
	collections/linked_list/linked_list_size.c
OBJ				= $(patsubst %.c,%.o,$(SRC))
OBJ				:= $(patsubst %.s,%.o,$(OBJ))
HEADERS			= libft.h memmgmt.h linked_list.h printf.h
HEADERS			:= $(addprefix incl/,$(HEADERS))

# Colours
DARK_GREEN		= \x1b[32m
GREEN			= \x1b[92m
END				= \x1b[0m

PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

all: $(NAME)

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ))
	@echo "$(PREFIX)$(GREEN)Bundling objects...$(END)"
	@ar rc $(NAME) $(addprefix $(OUT_DIR)/,$(OBJ))
	@ranlib $(NAME)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@$(CC) $(COMPILE_FLAGS) $(DEBUG_FLAG) -I./incl/ -c -o $@ $<

$(OUT_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@nasm -f macho64 -o $@ $<

clean:
	@echo "$(PREFIX)$(GREEN)Removing directory $(END)$(OUT_DIR)"
	@rm -rf $(OUT_DIR)

fclean: clean
	@echo "$(PREFIX)$(GREEN)Removing file $(END)$(NAME)"
	@rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
