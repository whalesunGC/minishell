/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 10:28:22 by wichee            #+#    #+#             */
/*   Updated: 2024/11/15 14:14:49 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include "libft.h"

int	ft_dputunnbr(int fd, long n);

int	ft_dprintf(int fd, const char *format, ...);
int	ft_dprintchar(int fd, va_list ap);
int	ft_dprintstr(int fd, va_list ap);
int	ft_dprintptr(int fd, va_list ap);
int	ft_dprintdeci(int fd, va_list ap);
int	ft_dprintundeci(int fd, va_list ap);
int	ft_dprinthexlow(int fd, va_list ap);
int	ft_dprinthexup(int fd, va_list ap);

#endif
