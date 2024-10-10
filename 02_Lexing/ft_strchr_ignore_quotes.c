/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_ignore_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:05:07 by wichee            #+#    #+#             */
/*   Updated: 2024/06/10 15:52:21 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

char	*ft_strchr_ignore_quotes(const char *s, int c)
{
	unsigned char	t;
	int				in_single_quote;
	int				in_double_quote;

	t = (unsigned char)c;
	in_single_quote = 0;
	in_double_quote = 0;
	if (*s == '\0' && *s == t)
		return ((char *)s);
	if (*s == t && *s != '\0')
		return ((char *)s);
	while (*s)
	{
		if (*s == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*s == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (*s == t && !in_single_quote && !in_double_quote)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
