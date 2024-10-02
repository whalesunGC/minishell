/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:05:07 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 13:52:22 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

char	*ft_strchr(const char *s, int c)
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
