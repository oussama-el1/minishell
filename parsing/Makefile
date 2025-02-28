CC              :=      cc
CFLAGS          :=      -Wall -Wextra -Werror -g
NAME            :=      minishell
RM              :=      rm -rf
MKDIR           :=      mkdir -p

# libft
LIBFT_DIR       :=      lib/libft
LIBFT           :=      $(LIBFT_DIR)/libft.a
LIBFT_HEADER    :=      $(LIBFT_DIR)/libft.h

# readline linking
READLINE        :=      $(shell brew --prefix readline)/lib
READLINE_HEADER :=      $(shell brew --prefix readline)/include/readline

# srcs
HEADERS          :=      $(shell find inc -type f -name "*.h") $(LIBFT_HEADER)
SRC_DIR         :=      srcs
SRCS            :=      $(shell find $(SRC_DIR) -type f -name "*.c")

# objs
OBJ_DIR         :=      objs
OBJS            :=      $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
bonus: all

$(NAME): $(LIBFT) $(OBJS)
		@echo "$(YELLOW)Compiling minishell ...$(DEF_COLOR)"
		@$(CC) $(CFLAGS) $^ -o $@ -L $(READLINE) -lreadline
		@echo "$(GREEN)minishell compilation done!$(DEF_COLOR)"

$(LIBFT): $(LIBFT_HEADER)
		@echo "$(YELLOW)Compiling libft ...$(DEF_COLOR)"
		@$(MAKE) -C $(LIBFT_DIR)
		@echo "$(GREEN)libft compilation done!$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
		@mkdir -p $(dir $@)
		@$(CC) $(CFLAGS) -I $(READLINE_HEADER) -I inc -c $< -o $@

clean:
		@echo "$(GRAY)Deleting object files ...$(DEF_COLOR)"
		@$(RM) $(OBJ_DIR)
		@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
		@echo "$(GRAY)Deleting all ...$(DEF_COLOR)"
		@$(RM) $(NAME)
		@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

# Colors
DEF_COLOR       :=      \033[0;39m
GRAY            :=      \033[0;90m
GREEN           :=      \033[0;92m
YELLOW          :=      \033[0;93m