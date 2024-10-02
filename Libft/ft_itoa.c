/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:52 by wichee            #+#    #+#             */
/*   Updated: 2024/06/06 06:50:22 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>
#include <stdlib.h>

static size_t	ft_num_char(long n)
{
	size_t	digits;

	digits = 0;
	while (n / 10 != 0)
	{
		n /= 10;
		digits++;
	}
	if (n < 0)
		return (digits + 2);
	else
		return (digits + 1);
}

char	*ft_itoa(int n)
{
	size_t	num_char;
	char	*alpha;
	long	size;

	size = (long)n;
	num_char = ft_num_char(size);
	alpha = (char *)malloc((num_char + 1) * sizeof(char));
	if (!alpha)
		return (NULL);
	alpha[num_char] = '\0';
	if (size < 0)
		size *= -1;
	while (num_char--)
	{
		alpha[num_char] = (size % 10) + 48;
		size /= 10;
	}
	if (n < 0)
		alpha[0] = '-';
	return (alpha);
}
