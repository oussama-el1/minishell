/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:40:57 by yslami            #+#    #+#             */
/*   Updated: 2025/03/03 01:01:44 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "../../inc/minishell.h"
# include <stdlib.h>
# include <unistd.h>


int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_is_alnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char const *s1, char const *set, int type);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size, int type);
char		*ft_strdup(const char *s, int type);
char		*ft_strjoin(char const *s1, char const *s2, int type);
char		**ft_split(char const *s, char c, int type);
char		*ft_itoa(int n, int type);
int			ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_putstrn_fd(char *s, int fd, int n);
int			ft_putnchar_fd(char c, int fd, int n);
char		*ft_substr(char const *s, unsigned int start, size_t len, \
	int type);

#endif