/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdeci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 09:48:09 by wichee            #+#    #+#             */
/*   Updated: 2024/06/19 12:22:19 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printdeci(va_list ap)
{
	char	*num;
	int		size;

	num = ft_itoa(va_arg(ap, int));
	ft_putstr_fd(num, 1);
	size = ft_strlen(num);
	free (num);
	return (size);
}
