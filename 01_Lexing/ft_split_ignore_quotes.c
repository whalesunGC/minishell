/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ignore_quotes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:41 by wichee            #+#    #+#             */
/*   Updated: 2024/06/10 15:52:21 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

static const char	*ft_trimlead_del(const char *s, int c)
{
	int		in_single_quote;
	int		in_double_quote;

	if (!c || *s == '\0' || *s != c)
		return (s);
	in_single_quote = 0;
	in_double_quote = 0;
	while (*s)
	{
		if (*s == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*s == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*s == c && !in_single_quote && !in_double_quote)
		{
			while (*s == c)
				s++;
			break ;
		}
		s++;
	}
	return (s);
}

static size_t	ft_num_strings(const char *s, int c)
{
	size_t	num_strings;

	num_strings = 0;
	while (s)
	{
		s = ft_trimlead_del(s, c);
		if (*s == '\0')
			break ;
		if (*s)
			num_strings++;
		s = ft_strchr_ignore_quotes(s, c);
	}
	return (num_strings);
}

static void	ft_free(char **s_s)
{
	size_t	i;

	i = 0;
	while (s_s[i] != NULL)
	{
		free(s_s[i]);
		i++;
	}
	free(s_s);
}

static char	**ft_process_s(char **s_s, const char *t_s, const char *s, char c)
{
	size_t	i;
	size_t	num_strings;

	i = 0;
	num_strings = ft_num_strings(s, c);
	while (i < num_strings)
	{
		t_s = ft_trimlead_del(s, c);
		s = t_s;
		t_s = ft_strchr_ignore_quotes(t_s, c);
		if (!t_s)
			s_s[i] = ft_substr(s, 0, ft_strlen(s));
		else
			s_s[i] = ft_substr(s, 0, (t_s - s));
		if (!s_s[i])
		{
			ft_free(s_s);
			return (NULL);
		}
		s = t_s + 1;
		i++;
	}
	s_s[i] = NULL;
	return (s_s);
}

char	**ft_split_ignore_quotes(const char *s, char c)
{
	char		**split_str;
	const char	*temp_s;
	size_t		num_strings;

	temp_s = s;
	num_strings = ft_num_strings(s, c);
	if (!s)
		return (NULL);
	split_str = (char **)malloc((num_strings + 1) * sizeof(char *));
	if (!split_str)
		return (NULL);
	split_str = ft_process_s(split_str, temp_s, s, c);
	return (split_str);
}
