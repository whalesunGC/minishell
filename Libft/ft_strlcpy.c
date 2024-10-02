/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:22:28 by wichee            #+#    #+#             */
/*   Updated: 2024/05/16 20:44:58 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

static void	set_nul(char *dst, const char **src, size_t size)
{
	if (size != 0)
		*dst = '\0';
	while (**src)
		(*src)++;
	(*src)++;
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char	*s;
	size_t		n;

	s = src;
	n = size;
	if (size == 1)
		set_nul(dst, &src, size);
	if (n > 1)
	{
		while (--n)
		{
			if (*src)
				*dst++ = *src++;
			else
			{
				*dst = *src++;
				break ;
			}
		}
	}
	if (n == 0)
		set_nul(dst, &src, size);
	return (src - s - 1);
}
