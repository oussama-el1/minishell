CC              	:=      cc
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
HEADER         		:=		inc/minishell.h
SRC_DIR         	:=      srcs
# SRCS            	:=      $(shell find $(SRC_DIR) -type f -name "*.c")
SRCS				:= srcs/main.c \
					srcs/execution/exec_command.c \
					srcs/execution/builtin.c \
					srcs/execution/exec_pipe.c \
					srcs/execution/exec_redirection.c \
					srcs/execution/exec_redirection_helpers.c \
					srcs/execution/exec_redirection_helpers2.c \
					srcs/execution/subshell.c \
					srcs/execution/exec_tree.c \
					srcs/execution/paths.c \
					srcs/execution/builtins/cd.c \
					srcs/execution/builtins/echo.c \
					srcs/execution/builtins/env.c \
					srcs/execution/builtins/exit.c \
					srcs/execution/builtins/export.c \
					srcs/execution/builtins/pwd.c \
					srcs/execution/builtins/unset.c \
					srcs/helper/ft_atoi.c \
					srcs/helper/ft_isdigit.c \
					srcs/helper/ft_putchar_fd.c \
					srcs/helper/ft_putstrn_fd.c \
					srcs/helper/ft_strlcat.c \
					srcs/helper/ft_strrchr.c \
					srcs/helper/ft_bzero.c \
					srcs/helper/ft_isnum.c \
					srcs/helper/ft_putendl_fd.c \
					srcs/helper/ft_split.c \
					srcs/helper/ft_strlcpy.c \
					srcs/helper/ft_strtrim.c \
					srcs/helper/ft_calloc.c \
					srcs/helper/ft_isprint.c \
					srcs/helper/ft_putnbr_fd.c \
					srcs/helper/ft_strchr.c \
					srcs/helper/ft_strlen.c \
					srcs/helper/ft_substr.c \
					srcs/helper/ft_isalnum.c \
					srcs/helper/ft_itoa.c \
					srcs/helper/ft_putnchar_fd.c \
					srcs/helper/ft_strdup.c \
					srcs/helper/ft_strncmp.c \
					srcs/helper/get_next_line_bonus.c \
					srcs/helper/ft_isalpha.c \
					srcs/helper/ft_memset.c \
					srcs/helper/ft_putstr_fd.c \
					srcs/helper/ft_strjoin.c \
					srcs/helper/ft_strnstr.c \
					srcs/parsing/parser.c \
					srcs/parsing/parsing_type.c \
					srcs/parsing/tree.c \
					srcs/parsing/tree_1.c \
					srcs/utils/arg_expander_helper.c \
					srcs/utils/env_utils2.c \
					srcs/utils/helper.c \
					srcs/utils/list_utils.c \
					srcs/utils/string_utils.c \
					srcs/utils/wildcard_expander.c \
					srcs/utils/arg_expender.c \
					srcs/utils/exec_utils.c \
					srcs/utils/helper_2.c \
					srcs/utils/list_utils2.c \
					srcs/utils/syntax.c \
					srcs/utils/wildcard_helpers.c \
					srcs/utils/arg_split.c \
					srcs/utils/fd_gc.c \
					srcs/utils/helper_3.c \
					srcs/utils/redir_parse.c \
					srcs/utils/syntax_helper.c \
					srcs/utils/env_utils.c \
					srcs/utils/garbage_collec.c \
					srcs/utils/helper_4.c \
					srcs/utils/signal.c \
					srcs/utils/tree_utils.c

# objs
OBJ_DIR         	:=      objs
OBJS            	:=      $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
bonus: all

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $^ -o $@ -L$(READLINE) -lreadline -lhistory
		@printf "\n"
		@for i in {1..8}; do \
			printf "\033[2C🔗$(GRAY) Linking object files $(DEF_COLOR)%-10s\r$(DEF_COLOR)" $$(seq -s "." $$i | tr -d '[:digit:]'); \
			sleep 0.3; \
		done
		@printf "\n\n$(CYAN)\t███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗     \n$(DEF_COLOR)"
		@printf "$(CYAN)\t████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║     \n$(DEF_COLOR)"
		@printf "$(CYAN)\t██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║     \n$(DEF_COLOR)"
		@printf "$(CYAN)\t██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║     \n$(DEF_COLOR)"
		@printf "$(CYAN)\t██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗\n$(DEF_COLOR)"
		@printf "$(CYAN)\t╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n\n$(DEF_COLOR)"
		@printf "\t\t\t\t🎩 Crafted by: $(BOLD)$(GREEN)oel-hadr$(DEF_COLOR) 🛠️ $(GREEN)yslami$(DEF_COLOR)\n"
		@printf "$(CYAN)\t\t\t    _____________________________________________$(DEF_COLOR)\n"
		@printf "\n$(GREEN) 🚀 SUCCESS: Minishell compiled successfully! 🚀\n$(DEF_COLOR)"

# create:
# 	@$(MKDIR) $(OBJ_DIR)
# | create

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
		@$(MKDIR) $(dir $@)
		@printf "\033[1C$(YELLOW)Generating minishell objects... %-33.33s\r$(DEF_COLOR)" $@
		@$(CC) $(CFLAGS) -I $(READLINE_HEADER) -I inc -c $< -o $@

clean:
		@printf "$(GRAY)Deleting object files ...\n$(DEF_COLOR)"
		@$(RM) $(OBJ_DIR)

fclean: clean
		@printf "$(GRAY)Deleting all ...\n$(DEF_COLOR)"
		@$(RM) $(NAME)


re: fclean all

.PHONY: all bonus create clean fclean re check_status

# Colors
DEF_COLOR       :=      \033[0;39m
GRAY            :=      \033[0;90m
GREEN           :=      \033[0;92m
CYAN			:=		\033[1;36m
YELLOW          :=      \033[0;93m
BOLD 			:= 		\033[1m