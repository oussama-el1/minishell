/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-hadr <oel-hadr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 23:40:57 by yslami            #+#    #+#             */
/*   Updated: 2025/02/08 01:08:09 by oel-hadr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>

/* LIBC Functions */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *str);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_strnstr(const char *big, const char *little, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			ft_atoi(const char *str);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
int			ft_strcmp(const char *s1, const char *s2);

/* Additional functions */
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
int			ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
int			ft_putstrn_fd(char *s, int fd, int n);
int			ft_putnchar_fd(char c, int fd, int n);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
int			ft_lstsize(t_list *lst);

/* get_next_line */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_next_line(int fd);
size_t		ft_strlen_0(const char *str);
char		*ft_strchr_0(const char *s, int c);
char		*ft_strjoin_0(char const *s1, char const *s2);
char		*ft_strdup_0(const char *s);
char		*ft_strjoin_free(char *s1, char *s2);

# define HEXALOW "0123456789abcdef"
# define HEXAUP "0123456789ABCDEF"

typedef struct s_format
{
	int		len;
	int		neg;
	char	specifier;
	int		minus;
	int		plus;
	int		width;
	int		precision;
	int		neg_prec;
	int		zero;
	int		dot;
	int		space;
	int		sharp;
}	t_format;

t_format	ft_newformat(void);
void		ft_parse_bonus(const char *str, va_list list, t_format *p);
int			ft_isflag(int c);
int			ft_isspecific(int c);
int			ft_isflag_type(int c);
void		ft_flags_minus(t_format *p);
void		ft_reset_format(t_format *p);
int			ft_type(t_format p);
int			ft_print_c_prc(va_list list, t_format p);
int			ft_print_s(va_list list, t_format p);
int			ft_print_di(int nbr, t_format p);
int			ft_print_u(unsigned nbr, t_format p);
int			ft_print_hex(unsigned int n, t_format p);
int			ft_print_p(void *ptr, t_format p);
int			ft_nbrlen(int n, int base);
char		*ft_utoa(unsigned int nbr);

int			ft_printf(const char *format, ...);

#endif