/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:28:22 by wichee            #+#    #+#             */
/*   Updated: 2024/07/05 12:20:25 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int	ft_putunnbr(long n);

int	ft_printf(const char *format, ...);
int	ft_printchar(va_list ap);
int	ft_printstr(va_list ap);
int	ft_printptr(va_list ap);
int	ft_printdeci(va_list ap);
int	ft_printundeci(va_list ap);
int	ft_printhexlow(va_list ap);
int	ft_printhexup(va_list ap);

#endif
