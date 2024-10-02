/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:34 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:31:56 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_alloctrim(const char *s, size_t alloc_s)
{
	char	*trim_str;

	trim_str = (char *)malloc(alloc_s + 1);
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, s, alloc_s + 1);
	return (trim_str);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*start;
	const char	*end;
	size_t		alloc_s;

	start = s1;
	if (!s1 || !set)
		return (NULL);
	while (ft_strchr(set, *start) && *start)
		start++;
	if (*start == '\0')
		return (ft_alloctrim("\0", 0));
	end = s1 + ft_strlen(s1) - 1;
	while (ft_strchr(set, *end) && end > start)
		end--;
	alloc_s = end - start + 1;
	return (ft_alloctrim(start, alloc_s));
}
