/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:10 by wichee            #+#    #+#             */
/*   Updated: 2024/06/06 07:04:31 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*ft_suballoc(const char *s, char *substr, size_t alloc_len)
{
	substr = (char *)malloc(alloc_len + 1);
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s, alloc_len + 1);
	return (substr);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	alloc_len;

	substr = NULL;
	if (*s == '\0' || len == 0 || start > ft_strlen(s))
		return (ft_suballoc("\0", substr, 0));
	else if (ft_strlen(s) - start < len)
		alloc_len = ft_strlen(s) - start;
	else
		alloc_len = len;
	substr = ft_suballoc(s + start, substr, alloc_len);
	return (substr);
}
