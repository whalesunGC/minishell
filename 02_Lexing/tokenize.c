/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:25:30 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 12:26:02 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: tokenize
 * @brief: takes input string and splits the words into tokens
	 without any classification.
 *
 * @param input: string after first expansion
 *
 * @return: returns a list of strings, char **tokens
 */
char	**tokenize(char *input)
{
	char	**tokens;

	tokens = ft_split_ignore_quotes(input, ' ');
	return (tokens);
}
