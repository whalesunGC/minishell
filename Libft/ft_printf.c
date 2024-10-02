/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:29:22 by wichee            #+#    #+#             */
/*   Updated: 2024/06/19 12:23:26 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_print_format(char format, va_list ap)
{
	int	size;

	size = 0;
	if (format == 'c')
		size += ft_printchar(ap);
	else if (format == 's')
		size += ft_printstr(ap);
	else if (format == 'p')
		size += ft_printptr(ap);
	else if (format == 'd')
		size += ft_printdeci(ap);
	else if (format == 'i')
		size += ft_printdeci(ap);
	else if (format == 'u')
		size += ft_printundeci(ap);
	else if (format == 'x')
		size += ft_printhexlow(ap);
	else if (format == 'X')
		size += ft_printhexup(ap);
	else if (format == '%')
		size += write(1, "%", 1);
	return (size);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += ft_print_format(*(++format), ap);
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
