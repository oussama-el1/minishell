/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yslami <yslami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 18:10:29 by yslami            #+#    #+#             */
/*   Updated: 2025/02/03 14:01:31 by yslami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static void	skip_quotes(const char **s, int *in_quote, char *quote_char)
{
	if (is_quote(**s))
	{
		if (*in_quote && **s == *quote_char)
			*in_quote = 0;
		else if (!*in_quote)
		{
			*in_quote = 1;
			*quote_char = **s;
		}
	}
}

static int  ft_count_words(const char *s)
{
	int		count = 0;
	int		in_quote = 0;
	char	quote_char = 0;
	int		in_word = 0;

	while (*s)
	{
		if (*s == ' ' && !in_quote)
		{
			in_word = 0;
			s++;
			continue;
		}
		skip_quotes(&s, &in_quote, &quote_char);
		if (!in_word)
		{
			count++;
			in_word = 1;
		}
		s++;
	}
	return (count);
}

static char *extract_word(const char *start, const char *end)
{
	char	*word;
	char	*result;
	int		len;
	int		j;

	len = 0;
	j = 0;
	word = ft_substr(start, 0, end - start);
	if (!word)
		return (NULL);
	for (int i = 0; word[i]; i++)
		if (!is_quote(word[i]))
			len++;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		free(word);
		return (NULL);
	}
	for (int i = 0; word[i]; i++)
		if (!is_quote(word[i]))
			result[j++] = word[i];
	result[j] = '\0';
	free(word);
	return (result);
}

static int  ft_allocate(char **tokens, const char *s)
{
	int			in_quote = 0;
	char		quote_char = 0;
	const char	*start;
	int			i = 0;

	while (*s)
	{
		while (*s && *s == ' ' && !in_quote)
			s++;
		if (!*s)
			break;
		start = s;
		while (*s && (*s != ' ' || in_quote))
		{
			skip_quotes(&s, &in_quote, &quote_char);
			s++;
		}
		tokens[i] = extract_word(start, s);
		if (!tokens[i++])
			return (0);
	}
	tokens[i] = NULL;
	return (1);
}

char	**quote_split(const char *s)
{
	char	**tokens;
	int		count;
	int		j;

	if (!s || !*s)
		return (NULL);
	count = ft_count_words(s);
	tokens = (char **)malloc((count + 1) * sizeof(char *));
	if (!tokens)
		return (NULL);
	if (!ft_allocate(tokens, s))
	{
		j = 0;
		while (tokens[j])
			free(tokens[j++]);
		free(tokens);
		return (NULL);
	}
	return (tokens);
}

/*
echo "Hello "World" 'how are you' "
*/