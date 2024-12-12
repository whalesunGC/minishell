/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_e.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:08:22 by wichee            #+#    #+#             */
/*   Updated: 2024/12/12 19:08:24 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_reset_quotes
 * @brief: will take the
 */
char	*ft_reset_quotes(char *env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i])
	{
		if (env_var[i] == VAR_S_Q)
			env_var[i] = '\'';
		else if (env_var[i] == VAR_D_Q)
			env_var[i] = '\"';
		else
			i++;
	}
	return (env_var);
}

/**
 * @function: ft_replace_quotes
 * @brief: will take the
 */
static char	*ft_replace_quotes(char *env_var)
{
	int	i;

	i = 0;
	if (!env_var)
		return (NULL);
	while (env_var[i])
	{
		if (env_var[i] == '\'')
			env_var[i] = VAR_S_Q;
		else if (env_var[i] == '\"')
			env_var[i] = VAR_D_Q;
		else
			i++;
	}
	return (env_var);
}

/**
 * @function: ft_var_exp_val_var
 * @brief: takes an input that starts with a '$',
	finds the env variable and replaces inplace.
 *
 * @param input: the address to the pointer of the input string.
 * @param start_index: an int which represents the starting
	index that points to a '$'
 *
 * @return: returns a string with the '$VAR' replaced with
	its corresponding env variable if found, else it returns
	a string with '$VAR' replaced with a NULL
 */

static char	*ft_var_exp_val_var(char **input, int start_index, char **env)
{
	int		env_len;
	char	*var;
	char	*env_var;

	env_len = ft_env_len(*input + start_index);
	var = ft_substr(*input + start_index, 0, env_len);
	env_var = ft_env_search(var, env);
	env_var = ft_replace_quotes(env_var);
	return (free(var), env_var);
}

/**
 * @function: handle_env_variable_val_var
 * @brief: takes identified parameter
 * and does variable expansion.
 *
 * @param input: address to the pointer of the
 * string(string by reference)
 * @param i: index value of where '$' is found
 * @param env: env variables copied from main
 *
 */
static void	handle_env_variable_val_var(char **input, int *i, char **env)
{
	char	*env_var;

	env_var = ft_var_exp_val_var(input, *i, env);
	expansion_replace_string(env_var, *i, input);
	if (env_var)
	{
		*i += ft_strlen(env_var);
		free(env_var);
	}
}

/**
 * @function: expansion_val_var
 * @brief: takes input string that contains valid variables
 * and does variable expansion and quote removal
 *
 * @param input: any string, note that this
 * 	is malloced and needs to be freed after use.
 * @param env: env variables copied from main
 *
 * @return: returns expanded string.
 */
char	*expansion_val_var(char *input, char **env, int *exit_status)
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
		handle_quote_status_val_var(input, &in_single_quote, &in_d_quote, &i);
		if ((input[i] == '$' && input[i + 1] == '?') && !in_single_quote)
			input = ft_str_replace(input, i, status);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || in_d_quote))
			handle_env_variable_val_var(&input, &i, env);
		else
			i++;
	}
	return (free(status), input);
}
