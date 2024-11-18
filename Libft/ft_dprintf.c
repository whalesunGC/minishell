/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:29:22 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:14:36 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_dprintf.h"

int	ft_dprint_format(int fd, char format, va_list ap)
{
	int	size;

	size = 0;
	if (format == 'c')
		size += ft_dprintchar(fd, ap);
	else if (format == 's')
		size += ft_dprintstr(fd, ap);
	else if (format == 'p')
		size += ft_dprintptr(fd, ap);
	else if (format == 'd')
		size += ft_dprintdeci(fd, ap);
	else if (format == 'i')
		size += ft_dprintdeci(fd, ap);
	else if (format == 'u')
		size += ft_dprintundeci(fd, ap);
	else if (format == 'x')
		size += ft_dprinthexlow(fd, ap);
	else if (format == 'X')
		size += ft_dprinthexup(fd, ap);
	else if (format == '%')
		size += write(fd, "%", 1);
	return (size);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		count;

	va_start(ap, format);
	count = 0;
	while (*format != '\0')
	{
		if (*format == '%')
			count += ft_dprint_format(fd, *(++format), ap);
		else
			count += write(fd, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
