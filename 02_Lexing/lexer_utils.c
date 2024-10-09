/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:43:07 by wichee            #+#    #+#             */
/*   Updated: 2024/10/09 19:43:35 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_free_split()
 * @brief: function that takes a **char and frees each string in the array followed by the array itself
 * 
 * @param input: a char* array or an array of strings each malloced.
 * 
 * @return: no return value, void function.
 */
void	ft_free_split(char **split)
{
	while (*split)
		free(*split++);
}
