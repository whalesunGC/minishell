/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:46:02 by wichee            #+#    #+#             */
/*   Updated: 2024/06/19 12:23:00 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printchar(va_list ap)
{
	unsigned char	c;

	c = va_arg(ap, int);
	return (write(1, &c, 1));
}
