/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:31:47 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:40:29 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_tolower(int c)
{
	unsigned char	t;

	t = (unsigned char)c;
	if (c == EOF)
		return (c);
	else if (c >= 65 && c <= 90)
		return (c + 32);
	return (t);
}
