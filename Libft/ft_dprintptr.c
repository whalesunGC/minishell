/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:03:42 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:15:27 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

static int	ft_daddress(int fd, unsigned long i)
{
	char	address[17];
	size_t	index;
	size_t	digit;

	index = 16;
	address[index] = '\0';
	index -= 1;
	while (i != 0)
	{
		digit = (i % 16);
		if (digit >= 0 && digit <= 9)
			address[index] = digit + '0';
		else
			address[index] = (digit - 10) + 97;
		i /= 16;
		index--;
	}
	return (write(fd, "0x", 2) + write(fd, &address[index + 1], 15 - index));
}

int	ft_dprintptr(int fd, va_list ap)
{
	unsigned long	address;

	address = (unsigned long)va_arg(ap, void *);
	if (!address)
	{
		return (write(fd, "(nil)", 5));
	}	
	return (ft_daddress(fd, address));
}
