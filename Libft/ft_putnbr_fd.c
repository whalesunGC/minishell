/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:13:10 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 13:48:14 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	buffer[12];
	int		index;
	long	num;

	index = 11;
	num = (long)n;
	if (num == 0)
	{
		buffer[index] = '0';
		index--;
	}
	else if (num < 0)
	{
		write (fd, "-", 1);
		num *= -1;
	}
	while (num != 0)
	{
		buffer[index] = num % 10 + '0';
		num /= 10;
		index--;
	}
	write (fd, &buffer[index + 1], 10 - index);
}
