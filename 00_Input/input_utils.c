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
 * @function: ft_not_env
 * @brief: checks if not a valid starting env name
 * 
 * @param input: input char
 * @return: 1 if not valid, 0 if valid
 */
int	ft_is_env(int i)
{
	return (ft_isalpha(i) || i == '_' || ft_isdigit(i));
}

/**
 * @function: ft_add_whitespace_helper
 * @brief: adds whitespace before and after the index.
 *
 * @param input: address of the pointer to the input string
 * @param i: interger value of index
 * @param delta: the difference in the length of the matched string - 1.
 * @return: value of index
 */
int	ft_add_whitespace_helper(char **input, int i, int delta)
{
	if (i != 0)
	{
		*input = ft_str_insert(*input, i - 1, " ");
		i += 1;
	}
	*input = ft_str_insert(*input, i + delta, " ");
	if (delta > 0)
	{
		i += delta;
	}
	return (i);
}

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

	pipe = (i == '|');
	parenthesis = (i == '(' || i == ')');
	return (pipe | parenthesis);
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
	return (i == ' ' || i == '\t');
}
