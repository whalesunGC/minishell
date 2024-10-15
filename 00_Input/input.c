/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:59:20 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 15:00:00 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_input_remove_extra_whitespace
 * @brief: goes through the string and removes extra whitespaces
 * ie all whitespaces will not be preceeded by another whitespace.
 * 
 * @param input: input string
 * @result: new output string
 */
char	*ft_input_remove_extra_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_iswhitespace(input[i]) && ft_iswhitespace(input[i + 1]))
			input = ft_str_replace(input, i, "");
		else
			i++;
	}
	ft_printf("Output from remove_extra_whitespace: %s\n", input);
	return (input);
}

/**
 * @function: ft_input_add_whitespace
 * @brief: takes string and adds a white space after special characters.
 * 
 * @param input: input string
 * @result: new output string
 */
char	*ft_input_add_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_isspecial(input[i]))
		{
			if (i != 0)
			{
				input = ft_str_insert(input, i - 1, " ");
				i += 1;
			}
			input = ft_str_insert(input, i, " ");
		}
		i++;
	}
	ft_printf("Output from add_whitespace: %s\n", input);
	return (input);
}

/**
 * @function: ft_input_swap_whitespace
 * @brief: takes string swaps all whitespaces that are not ' ' 
 * with a single whitespace.
 * 
 * @param input: input string
 * @result: new output string
 */
char	*ft_input_swap_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (ft_iswhitespace(input[i]) && input[i] != ' ')
			input = ft_str_replace(input, i, " ");
		i++;
	}
	ft_printf("Output from swap_whitespace: %s\n", input);
	return (input);
}

/**
 * @function: input_clean
 * @brief: function takes raw input from readline and modifies the input.
 * it will format the input to make it easy to tokenize.
 * 
 * @param input: input string from readline
 * @return: modified string that is delimited for the lexer module.
 */
char	*input_clean(char *input)
{
	ft_printf("Readline input: %s\n", input);
	input = ft_input_swap_whitespace(input);
	input = ft_input_add_whitespace(input);
	input = ft_input_remove_extra_whitespace(input);
	ft_printf("Cleaned input: %s\n", input);
	return (input);
}
