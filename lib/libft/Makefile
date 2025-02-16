# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 15:42:47 by yslami            #+#    #+#              #
#    Updated: 2025/02/03 14:35:40 by oel-hadr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror
HEADER 		= 	libft.h
NAME 		= 	libft.a
OBJ_DIR 	= 	obj/
MD 			= 	mkdir -p
RM			=	rm -rf
AR			=	ar rcs

SRCS 		= 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isascii.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				get_next_line.c \
				get_next_line_utils.c \
				ft_flag_utils.c \
				ft_flags.c \
				ft_parse.c \
				ft_print_char_s.c \
				ft_print_di.c \
				ft_print_hex.c \
				ft_print_u.c \
				ft_printf.c \
				ft_utoa.c \
				ft_putstrn_fd.c \
				ft_putnchar_fd.c \
				ft_strcmp.c \

# OBJS 		= 		$(SRCS:.c=.o)
OBJS		=	$(SRCS:%.c=$(OBJ_DIR)%.o)

all:	$(NAME)

$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

$(OBJ_DIR)%.o: %.c $(HEADER)
	@$(MD) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean
