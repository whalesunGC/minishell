/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:38:27 by wichee            #+#    #+#             */
/*   Updated: 2024/05/16 20:24:35 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_temp;

	s_temp = (unsigned char *)s;
	while (n--)
		*s_temp++ = '\0';
}
