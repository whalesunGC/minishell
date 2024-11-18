/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:46:02 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:14:07 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

int	ft_dprintchar(int fd, va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	return (write(fd, &c, 1));
}
