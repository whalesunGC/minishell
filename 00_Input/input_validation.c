/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:28:40 by wichee            #+#    #+#             */
/*   Updated: 2024/10/16 14:28:45 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_input_validation
 * @brief: function validates the input string for syntax errors
 *
 * @param input: input string from readline
 * @return: modified string that is delimited for the lexer module.
 */
char	*ft_input_validation(char *input)
{
	if (!check_quotes_balance(input) || !check_parentheses_balance(input))
	{
		ft_printf("Error: Unbalanced quotes or parentheses\n");
		free(input);
		return (NULL);
	}
	if (!check_or_placement(input) || !check_and_placement(input))
	{
		ft_printf("Error: Invalid || or && placement\n");
		free(input);
		return (NULL);
	}
	if (!check_pipe_placement(input))
	{
		ft_printf("Error: Invalid pipe placement\n");
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * @function: check_pipe_placement
 * @brief: function checks if the pipe placement in the input string is valid
 *
 * @param input: input string from readline
 * @return: 1 if valid, 0 if not
 */
int	check_pipe_placement(const char *input)
{
	int		in_quotes;
	char	quote_char;
	int		last_char_pipe;
	int		found_non_space;

	in_quotes = 0;
	quote_char = 0;
	last_char_pipe = 0;
	found_non_space = 0;
	while (*input)
	{
		if ((*input == '\'' || *input == '"') && (!in_quotes
				|| *input == quote_char))
			handle_quotes(&in_quotes, &quote_char, *input);
		if (!in_quotes)
			if (!handle_pipe_flags(input, &found_non_space, &last_char_pipe))
				return (0);
		input++;
	}
	return (!last_char_pipe);
}

/**
 * @function: check_or_placement
 * @brief: check if || is not at the end or the beginning of the
 * command string
 *
 * @param input: input string from readline
 * @return: 1 if valid, 0 if not
 */
int	check_or_placement(const char *input)
{
	int		in_quotes;
	char	quote_char;
	int		last_char_or;
	int		found_non_space;

	in_quotes = 0;
	quote_char = 0;
	last_char_or = 0;
	found_non_space = 0;
	while (*input)
	{
		if ((*input == '\'' || *input == '"') && (!in_quotes
				|| *input == quote_char))
			handle_quotes(&in_quotes, &quote_char, *input);
		if (!in_quotes)
			if (!handle_seq_flags(&input, &found_non_space, &last_char_or,
					"||"))
				return (0);
		input++;
	}
	return (!last_char_or);
}

/**
 * @function: check_and_placement
 * @brief: check if && is not at the end or the beginning of the
 * command string
 *
 * @param input: input string from readline
 * @return: 1 if valid, 0 if not
 */
int	check_and_placement(const char *input)
{
	int		in_quotes;
	char	quote_char;
	int		last_char_and;
	int		found_non_space;

	in_quotes = 0;
	quote_char = 0;
	last_char_and = 0;
	found_non_space = 0;
	while (*input)
	{
		if ((*input == '\'' || *input == '"') && (!in_quotes
				|| *input == quote_char))
			handle_quotes(&in_quotes, &quote_char, *input);
		if (!in_quotes)
			if (!handle_seq_flags(&input, &found_non_space, &last_char_and,
					"&&"))
				return (0);
		input++;
	}
	return (!last_char_and);
}
