/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:32:50 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:44:44 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*temp_s1;
	unsigned char	*temp_s2;

	temp_s1 = (unsigned char *)s1;
	temp_s2 = (unsigned char *)s2;
	while (n--)
	{
		if (*temp_s1 == '\0' || *temp_s2 == '\0')
			return (*temp_s1 - *temp_s2);
		else if (*temp_s1 > *temp_s2 || *temp_s1 < *temp_s2)
			return (*temp_s1 - *temp_s2);
		else if (*temp_s1++ == *temp_s2++)
			;
	}
	return (0);
}
