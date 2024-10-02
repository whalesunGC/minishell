/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:31:26 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:41:28 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

int	ft_toupper(int c)
{
	unsigned char	t;

	t = (unsigned char)c;
	if (c == EOF)
		return (c);
	else if (c >= 97 && c <= 122)
		return (c - 32);
	return (t);
}
