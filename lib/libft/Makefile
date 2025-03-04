# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/23 15:42:47 by yslami            #+#    #+#              #
#    Updated: 2025/03/03 21:28:10 by oel-hadr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= 	cc
CFLAGS 		= 	-Wall -Wextra -Werror -g
HEADER 		= 	libft.h
NAME 		= 	libft.a
OBJ_DIR 	= 	obj/
MD 			= 	mkdir -p
RM			=	rm -rf
AR			=	ar rcs

SRCS 		= 	ft_isalpha.c \
				ft_isdigit.c \
				ft_isalnum.c \
				ft_isnum.c \
				ft_isprint.c \
				ft_strlen.c \
				ft_memset.c \
				ft_bzero.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstrn_fd.c \
				ft_putnchar_fd.c \

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
