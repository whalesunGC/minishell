/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhexup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:10:14 by wichee            #+#    #+#             */
/*   Updated: 2024/06/11 13:38:48 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_hexup(unsigned int i)
{
	char	hexlow[17];
	size_t	index;
	size_t	digit;

	if (i == 0)
		return (write(1, "0", 1));
	index = 16;
	hexlow[index] = '\0';
	index -= 1;
	while (i != 0)
	{
		digit = (i % 16);
		if (digit >= 0 && digit <= 9)
			hexlow[index] = digit + '0';
		else
			hexlow[index] = (digit - 10) + 65;
		i /= 16;
		index--;
	}
	return (write(1, &hexlow[index + 1], 15 - index));
}

int	ft_printhexup(va_list ap)
{
	unsigned int	hex;

	hex = va_arg(ap, unsigned int);
	return (ft_hexup(hex));
}
