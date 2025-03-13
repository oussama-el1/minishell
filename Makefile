CC              	:=      gcc
CFLAGS          	:=      -Wall -Wextra -Werror -g
NAME            	:=      minishell
RM              	:=      rm -rf
MKDIR           	:=      mkdir -p
HEADER_FLAG			:=		.header

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

# all: $(NAME)
all: check_status
bonus: all


check_status:
	@if [ -f $(NAME) ]; then \
		if [ -z "`find $(SRCS) $(HEADERS) -newer $(NAME) 2>/dev/null`" ]; then \
			printf "$(GRAY)minishell is already up to date ✓$(DEF_COLOR)\n"; \
		else \
			$(MAKE) --no-print-directory $(NAME); \
		fi \
	else \
		$(MAKE) --no-print-directory $(NAME); \
	fi

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
# @printf "$(CYAN)_______________________$(DEF_COLOR)"
		@printf "\t\t\t\t🎩 Crafted by: $(BOLD)$(GREEN)oel-hadr$(DEF_COLOR) 🛠️ $(GREEN)yslami$(DEF_COLOR)\n"
		@printf "$(CYAN)\t\t\t    _____________________________________________$(DEF_COLOR)\n"
		@printf "\n$(GREEN) 🚀 SUCCESS: Minishell compiled successfully! 🚀\n$(DEF_COLOR)"
#@printf "\n$(GREEN)minishell compilation done!\n$(DEF_COLOR)"

create:
	@$(MKDIR) $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | create
		@$(MKDIR) $(dir $@)
		@printf "\033[1C$(YELLOW)Generating minishell objects... %-33.33s\r$(DEF_COLOR)" $@
		@$(CC) $(CFLAGS) -I $(READLINE_HEADER) -I inc -c $< -o $@

clean:
		@printf "$(GRAY)Deleting object files ...\n$(DEF_COLOR)"
		@$(RM) $(OBJ_DIR)
		@$(RM) $(HEADER_FLAG)

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