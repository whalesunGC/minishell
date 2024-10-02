/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:07:40 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:29:25 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	t;
	size_t			n;
	const char		*tmp_s;

	t = (unsigned char)c;
	n = 0;
	tmp_s = s;
	while (*tmp_s++)
		n++;
	s = s + n;
	while (n--)
	{
		if (*s-- == t)
			return ((char *)s + 1);
	}
	if (*s == t)
		return ((char *)s);
	return (NULL);
}
