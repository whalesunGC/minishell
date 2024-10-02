/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:11:06 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 14:19:20 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*out_str;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	out_str = (char *)malloc((len + 1) * sizeof(char));
	if (!out_str)
		return (NULL);
	while (i < len)
	{
		out_str[i] = f(i, s[i]);
		i++;
	}
	out_str[i] = '\0';
	return (out_str);
}
