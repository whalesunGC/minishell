/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputunnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:45:45 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:15:57 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_dputunnbr(int fd, long n)
{
	char	c[11];
	size_t	i;

	i = 10;
	c[i] = '\0';
	i -= 1;
	if (n == 0)
		return (write (fd, "0", 1));
	while (n != 0)
	{
		c[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
	return (write (fd, &c[i + 1], 9 - i));
}
