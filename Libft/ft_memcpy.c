/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:29:18 by wichee            #+#    #+#             */
/*   Updated: 2024/05/16 20:31:54 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_temp;
	unsigned char	*src_temp;

	dest_temp = dest;
	src_temp = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (n--)
		*dest_temp++ = *src_temp++;
	return (dest);
}
