CC              	:=      gcc
CFLAGS          	:=      -Wall -Wextra -Werror -g
NAME            	:=      minishell
RM              	:=      rm -rf
MKDIR           	:=      mkdir -p


OS             		:=      $(shell uname)

ifeq ($(OS), Darwin)
    READLINE        :=      $(shell brew --prefix readline)/lib
    READLINE_HEADER :=      $(shell brew --prefix readline)/include/readline
else
    READLINE        :=      /usr/lib
    READLINE_HEADER :=      /usr/include/readline
endif

# srcs
HEADERS         	:=      $(shell find inc -type f -name "*.h")
SRC_DIR         	:=      srcs
SRCS            	:=      $(shell find $(SRC_DIR) -type f -name "*.c")

# objs
OBJ_DIR         	:=      objs
OBJS            	:=      $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
bonus: all

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $^ -o $@ -L$(READLINE) -lreadline -lhistory
		@printf "\n$(GREEN)minishell compilation done!\n$(DEF_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
		@mkdir -p $(dir $@)
		@printf "$(YELLOW)Generating minishell objects... %-33.33s\r$(DEF_COLOR)" $@
		@$(CC) $(CFLAGS) -I $(READLINE_HEADER) -I inc -c $< -o $@

clean:
		@printf "$(GRAY)Deleting object files ...\n$(DEF_COLOR)"
		@$(RM) $(OBJ_DIR)

fclean: clean
		@printf "$(GRAY)Deleting all ...\n$(DEF_COLOR)"
		@$(RM) $(NAME)


re: fclean all

.PHONY: all bonus clean fclean re

# Colors
DEF_COLOR       :=      \033[0;39m
GRAY            :=      \033[0;90m
GREEN           :=      \033[0;92m
YELLOW          :=      \033[0;93m
