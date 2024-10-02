/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:39:53 by wichee            #+#    #+#             */
/*   Updated: 2024/06/25 07:31:11 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*ft_strchr_gnl(const char *s, int c)
{
	unsigned char	t;

	t = (unsigned char)c;
	if (*s == '\0' && *s == t)
		return ((char *)s);
	if (*s == t && *s != '\0')
		return ((char *)s);
	while (*s++)
	{
		if (*s == t)
			return ((char *)s);
	}
	return (NULL);
}

void	*ft_memmove_gnl(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	dest_temp = dest;
	src_temp = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	if (dest_temp < src_temp)
		while (n--)
			*dest_temp++ = *src_temp++;
	else
	{
		dest_temp += n;
		src_temp += n;
		while (n--)
			*--dest_temp = *--src_temp;
	}
	return (dest);
}

char	*ft_substr_gnl(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	alloc_len;

	substr = NULL;
	if (*s == '\0' || len == 0 || start > ft_strlen_gnl(s))
		alloc_len = 0;
	else if (ft_strlen_gnl(s) - start < len)
		alloc_len = ft_strlen_gnl(s) - start;
	else
		alloc_len = len;
	substr = (char *)malloc(alloc_len + 1);
	if (!substr)
		return (free((void *)s), NULL);
	ft_memmove_gnl(substr, s + start, alloc_len);
	substr[alloc_len] = '\0';
	return (substr);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	ft_memmove_gnl(new_str, s1, ft_strlen_gnl(s1));
	ft_memmove_gnl(new_str + ft_strlen_gnl(s1), s2, ft_strlen_gnl(s2));
	new_str[len] = '\0';
	return (free((void *)s1), free((void *)s2), new_str);
}

char	*ft_strdup_gnl(const char *s)
{
	char		*dup;
	size_t		len;

	len = ft_strlen_gnl(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	ft_memmove_gnl(dup, s, len + 1);
	dup[len] = '\0';
	return (dup);
}
