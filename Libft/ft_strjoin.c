/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:10:22 by wichee            #+#    #+#             */
/*   Updated: 2024/06/04 13:57:07 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!s1 || !s2)
		return (NULL);
	new_str = (char *)malloc(len);
	if (!new_str)
		return (NULL);
	*new_str = '\0';
	ft_strlcat(new_str, s1, len);
	ft_strlcat(new_str, s2, len);
	return (new_str);
}
