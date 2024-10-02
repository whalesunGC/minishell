/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:29:34 by wichee            #+#    #+#             */
/*   Updated: 2024/06/06 07:03:17 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
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
