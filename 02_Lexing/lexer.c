/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 11:58:49 by wichee            #+#    #+#             */
/*   Updated: 2024/10/05 12:00:58 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: lexer
 * @brief: this is the entry point to the lexer module.
 * 
 * @param input: string after expansion (variable expansion, 
 	command substition and globbing).
 *
 * @return: returns an int, 0 for failure to create "stream of tokens",
	 1 for success.
 */
int	lexer(char *input)
{
	char	**tokens;
	int		i;

	ft_printf("%s\n", input);
	tokens = tokenize(input);
	i = 0;
	if (!tokens)
		return (free(input), 0);
	else
	{
		while (tokens[i])
		{
			ft_printf("printing tokens: %s\n", tokens[i]);
			i++;
		}
	}
	return (ft_free_split(tokens), free(tokens), 1);
}
