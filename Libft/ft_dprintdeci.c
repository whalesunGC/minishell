/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintdeci.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:48:09 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:14:23 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

int	ft_dprintdeci(int fd, va_list ap)
{
	char	*num;
	int		size;

	num = ft_itoa(va_arg(ap, int));
	ft_putstr_fd(num, fd);
	size = ft_strlen(num);
	free (num);
	return (size);
}
