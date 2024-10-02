/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:39:52 by wichee            #+#    #+#             */
/*   Updated: 2024/07/05 15:00:47 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isspace(int i)
{
	return ((i >= 9 && i <= 13) || i == 32);
}

static int	ft_issign(int i)
{
	return (i == 43 || i == 45);
}

long	ft_atoi(const char *nptr)
{
	int		sign;
	long	digit;

	sign = 1;
	digit = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (ft_issign(*nptr))
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		digit = digit * 10 + (*nptr - '0');
		nptr++;
	}
	return (digit * sign);
}
