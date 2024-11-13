/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:59:09 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:15:37 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

int	ft_dprintstr(int fd, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str)
	{
		ft_putstr_fd(str, fd);
		return (ft_strlen(str));
	}
	else
	{
		return (write(fd, "(null)", 6));
	}
}
