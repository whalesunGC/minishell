/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:27:23 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 17:09:27 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_isspecial
 * @brief: checks if input is a special character for the lexer in minishell
 * 
 * @param i: input integer
 * @return: 1 if special, 0 if not
 */
int	ft_isspecial(int i)
{
	int	pipe;
	int	parenthesis;
	int	quote;

	pipe = (i == '|');
	parenthesis = (i == '(' || i == ')');
	quote = (i == '\'' || i == '\"');
	return (pipe | parenthesis | quote);
}

/**
 * @function: ft_iswhitespace
 * @brief: checks if is whitespace
 * 
 * @param i: input integer
 * @return: 1 if whitespace, 0 if not
 */
int	ft_iswhitespace(int i)
{
	return (i == 32 || (i >= 9 && i <= 10)
		|| (i >= 11 && i <= 13));
}
