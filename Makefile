# **************************************************************************** #
#                                                                              #
#    Project: project_files                                   ::::::::             #
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
SRC				= main.c

OBJ				= $(patsubst %.c,%.o,$(SRC))
OBJ				:= $(patsubst %.s,%.o,$(OBJ))
HEADERS			=
HEADERS			:= $(addprefix project_files/incl/,$(HEADERS))

# Colours
DARK_GREEN		= \033[0;32m
GREEN			= \033[0;92m
END				= \033[0;0m

PREFIX			= $(DARK_GREEN)$(NAME) $(END)\xc2\xbb

all: $(NAME)

$(NAME): $(addprefix $(OUT_DIR)/,$(OBJ))
	@echo "$(PREFIX)$(GREEN)Bundling objects...$(END)"
	@$(CC) $(COMPILE_FLAGS) $(DEBUG_FLAG) -o $(NAME) libft/libft.a $(addprefix $(OUT_DIR)/,$(OBJ))

$(OUT_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(PREFIX)$(GREEN)Compiling file $(END)$< $(GREEN)to $(END)$@"
	@mkdir -p $(dir $@)
	@$(CC) $(COMPILE_FLAGS) $(DEBUG_FLAG) -I./project_files/incl/ -I./libft/incl/ -c -o $@ $<

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

exec: $(NAME)
	./minishell

.PHONY: all clean fclean re
