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
CFLAGS			= -Wall -Werror -Wextra
DFLAGS			= -g

# Files
SRC_DIR			= project_files/src
OUT_DIR			= project_files/out
INC_DIR			= project_files/incl
SRC				= main.c
HEADERS			=

LIBFT			= libft/libft.a
INC_LIBFT		= libft/include

# Sub-modules
include	project_files/src/env/env.mk
include	project_files/src/lex/lex.mk
include	project_files/src/parser/parser.mk

# Fix sources and headers
OBJ				= $(patsubst %.c,%.o,$(SRC))
OBJ				:= $(patsubst %.asm,%.o,$(OBJ))
HEADERS			:= $(addprefix $(INC_DIR)/,$(HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

all: $(NAME)

deps:
	@echo "$(SRC)"

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ)) $(LIBFT)
	@echo "$(PREFIX)$(GREEN)Bundling objects...$(END)"
	@$(CC) $(CFLAGS) $(DFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ $^

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(DFLAGS) -I$(INC_DIR) -I$(INC_LIBFT) -o $@ -c $<

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
