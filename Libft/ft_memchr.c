/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:39:16 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:33:34 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	unsigned char	temp_c;

	temp_s = (unsigned char *)s;
	temp_c = (unsigned char)c;
	while (n--)
	{
		if (*temp_s++ == temp_c)
			return (temp_s - 1);
	}
	return (NULL);
}
