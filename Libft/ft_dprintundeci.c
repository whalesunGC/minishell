/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintundeci.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:32:39 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:15:47 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

int	ft_dprintundeci(int fd, va_list ap)
{
	unsigned int	u_deci;

	u_deci = va_arg(ap, unsigned int);
	return (ft_dputunnbr(fd, u_deci));
}
