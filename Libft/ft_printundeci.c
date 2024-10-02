/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printundeci.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:32:39 by wichee            #+#    #+#             */
/*   Updated: 2024/06/11 11:38:19 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printundeci(va_list ap)
{
	unsigned int	u_deci;

	u_deci = va_arg(ap, unsigned int);
	return (ft_putunnbr(u_deci));
}
