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
NAME			= minishell

# Compiler
COMPILE_FLAGS	= -Wall -Werror -Wextra
DEBUG_FLAG		= -O3

# Files
SRC_DIR			= project_files/src
OUT_DIR			= project_files/out
INC_DIR			= project_files/incl
SRC				= main.c
HEADERS			=

LIBFT			= libft/libft.a
INC_LIBFT		= libft/incl

# Sub-modules
include	project_files/src/env/env.mk
include	project_files/src/lex/lex.mk

# Fix sources and headers
OBJ				= $(patsubst %.c,%.o,$(SRC))
OBJ				:= $(patsubst %.s,%.o,$(OBJ))
HEADERS			:= $(addprefix $(INC_DIR)/,$(HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

all: $(NAME)

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ)) $(LIBFT)
	@echo "$(PREFIX)$(GREEN)Bundling objects...$(END)"
	@echo "$(addprefix $(OUT_DIR)/,$(OBJ))"
	@$(CC) $(COMPILE_FLAGS) $(DEBUG_FLAG) -o $(NAME) $(addprefix $(OUT_DIR)/,$(OBJ)) $(LIBFT)

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@$(CC) $(COMPILE_FLAGS) $(DEBUG_FLAG) -I./$(INC_DIR) -I./$(INC_LIBFT) -c -o $@ $<

$(OUT_DIR)/%.o: $(SRC_DIR)/%.s $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@nasm -f macho64 -o $@ $<

$(LIBFT):
	@echo "$(PREFIX)$(GREEN)Bundling libft...$(END)"
	@$(MAKE) -C libft > /dev/null

clean:
	@echo "$(PREFIX)$(GREEN)Removing directory $(END)$(OUT_DIR), libft/out"
	@rm -rf $(OUT_DIR)
	@$(MAKE) -C libft clean > /dev/null

fclean: clean
	@echo "$(PREFIX)$(GREEN)Removing file $(END)$(NAME), $(LIBFT)"
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean > /dev/null

re: fclean $(NAME)

exec: $(NAME)
	./minishell

.PHONY: all clean fclean re
