/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:41 by wichee            #+#    #+#             */
/*   Updated: 2024/10/07 18:04:48 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_quote_status
 * @brief: assigns flags to quotes
 *
 * @param input: address to the pointer of the
 * string(string by reference)
 * @param in_single_quote: point to the index value of where '$' is found
 * @param in_double_quote: env variables copied from main
 * @param i: current count
 * @return: 1 if flags change or 0
 */
int	handle_quote_status(char *input, int *in_single_quote,
	int *in_d_quote, int *i)
{
	if (input[*i] == '\"' && !(*in_single_quote))
	{
		*in_d_quote = !(*in_d_quote);
		(*i)++;
		return (1);
	}
	else if (input[*i] == '\'' && !(*in_d_quote))
	{
		*in_single_quote = !(*in_single_quote);
		(*i)++;
		return (1);
	}
	return (0);
}

/**
 * @function: handle_env_variable
 * @brief: takes identified parameter
 * and does variable expansion.
 *
 * @param input: address to the pointer of the
 * string(string by reference)
 * @param i: index value of where '$' is found
 * @param env: env variables copied from main
 *
 */
static void	handle_env_variable(char **input, int *i, char **env)
{
	char	*env_var;

	env_var = ft_var_exp(input, *i, env);
	expansion_replace_string(env_var, *i, input);
	if (env_var)
	{
		*i += ft_strlen(env_var);
		free(env_var);
	}
}

/**
 * @function: expansion
 * @brief: takes input string and does variable expansion.
 *
 * @param input: any string, note that this
 * 	is malloced and needs to be freed after use.
 * @param ignore_quote: flag to check if expansion should
 * ignore quotes.
 * @param env: env variables copied from main
 *
 * @return: returns expanded string or NULL if expansion fails.
 */
char	*expansion_string(char *input, int ignore_quote, char **env,
	int *exit_status)
{
	int		in_single_quote;
	int		in_d_quote;
	int		i;
	char	*status;

	in_single_quote = 0;
	in_d_quote = 0;
	i = 0;
	status = ft_itoa(*exit_status);
	while (input[i])
	{
		if (handle_quote_status(input, &in_single_quote, &in_d_quote, &i) == 1)
			;
		else if ((input[i] == '$' && input[i + 1] == '?'))
			input = ft_str_replace(input, i, status);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || ignore_quote || in_d_quote))
			handle_env_variable(&input, &i, env);
		else
			i++;
	}
	return (free(status), input);
}

/**
 * @function: expansion
 * @brief: iterates through linked-list and does expansion via
 * variable substitution on raw_string.
 *
 * @param token_data: linked-list of lexed token_data
 * @return: linked-list of token_data with expansion
 */
t_list	*expansion(t_list *token_data, char **env, int *exit_status)
{
	t_list	*head;

	head = token_data;
	if (!token_data)
		return (NULL);
	else
		while (token_data != NULL)
			token_data = ft_expansion_tokens(&token_data, env, exit_status);
	return (head);
}
