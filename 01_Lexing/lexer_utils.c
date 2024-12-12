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
 * @function: has_variable
 * @brief: function checks if string contains expansion variables.
 * 
 * @param input: input string
 * @return: 1 if contains , 0 is not
 */
int	has_variable(char *input)
{
	int		in_single_quote;
	int		in_d_quote;
	int		i;

	in_single_quote = 0;
	in_d_quote = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (handle_quote_status(input, &in_single_quote, &in_d_quote, &i) == 1)
			;
		else if ((input[i] == '$' && input[i + 1] == '?'))
			return (1);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || in_d_quote))
			return (1);
		else
			i++;
	}
	return (0);
}

/**
 * @function: has_valid_variable
 * @brief: function checks if string contains valid expansion variable.
 * 
 * @param input: input string
 * @param env: current envp
 * @return: 1 if contains , 0 is not
 */
int	has_valid_variable(char *input, char **env)
{
	int		in_single_quote;
	int		in_d_quote;
	int		i;
	int		in_env_var;

	in_single_quote = 0;
	in_d_quote = 0;
	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		in_env_var = has_env_variable(input, env, i);
		if (handle_quote_status(input, &in_single_quote, &in_d_quote, &i) == 1)
			;
		else if ((input[i] == '$' && input[i + 1] == '?'))
			return (1);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || in_d_quote) && in_env_var)
			return (1);
		else
			i++;
	}
	return (0);
}

/**
 * @function: ft_lexer_init_state
 * @brief: function that inits the state of the lexer before assigning token
 * types
 * 
 * @param state: the struct
 * @return: no return value, void function.
 */
t_lex_init_state	*ft_lexer_init_state(t_lex_init_state *state)
{
	state = (t_lex_init_state *)malloc(sizeof(t_lex_init_state));
	if (!state)
		return (NULL);
	state->i = 0;
	state->is_first_token = 1;
	state->is_hd_delimiter = 0;
	state->is_fd = 0;
	return (state);
}

/**
 * @function: ft_free_lex_data
 * @brief: function that takes the struct t_lex_data
 * and frees all elements within it.
 * 
 * @param data: the struct t_lex_data
 * @return: no return value, void function.
 */
void	ft_free_lex_data(void *data)
{
	if (data)
	{
		free(((t_lex_data *)data)->raw_string);
		free(((t_lex_data *)data));
	}
}

/**
 * @function: ft_free_split()
 * @brief: function that takes a **char and frees each
	 string in the array followed by the array itself
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
