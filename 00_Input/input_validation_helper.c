/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 22:42:12 by wichee            #+#    #+#             */
/*   Updated: 2024/10/31 22:42:30 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: check_quotes_balance
 * @brief: function checks if the quotes in the input string are balanced
 *
 * @param input: input string from readline
 * @return: 1 if balanced, 0 if not
 */
int	check_quotes_balance(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (*input == '"' && !single_quote)
			double_quote = !double_quote;
		input++;
	}
	return (!single_quote && !double_quote);
}

/**
 * @function: check_parentheses_balance
 * @brief: function checks if the parentheses in the input string are balanced
 *
 * @param input: input string from readline
 * @return: 1 if balanced, 0 if not
 */
int	check_parentheses_balance(const char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '(')
			count++;
		else if (*input == ')')
		{
			if (count == 0)
				return (0);
			count--;
		}
		input++;
	}
	return (count == 0);
}