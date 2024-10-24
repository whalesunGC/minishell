/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:45:41 by apoh              #+#    #+#             */
/*   Updated: 2024/09/25 14:46:15 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_strcmp
 * @brief: custom function to compare string without size variable
 * 
 * @param s1: string1
	  s2: string2
 * 
 * @return: differences between 2 strings if any. 0 if its the same.
 */


int	ft_strcmp(const char *s1, const char *s2)

{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
