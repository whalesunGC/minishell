/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_d.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:33:13 by wichee            #+#    #+#             */
/*   Updated: 2024/12/04 17:33:21 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
char	*expansion_val_var(char *input, char **env,
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
		handle_quote_status_val_var(input, &in_single_quote, &in_d_quote, &i);
		if ((input[i] == '\'') && !in_d_quote)
			input = ft_str_replace(input, i, "");
		else if ((input[i] == '\"') && !in_single_quote)
			input = ft_str_replace(input, i, "");
		else if ((input[i] == '$' && input[i + 1] == '?') && !in_single_quote)
			input = ft_str_replace(input, i, status);
		else if ((input[i] == '$' && ft_is_env(input[i + 1]))
			&& (!in_single_quote || in_d_quote))
			handle_env_variable(&input, &i, env);
		else
			i++;
	}
	return (free(status), input);
}

/**
 * @function: ft_remove_inquote
 * @brief: remove head and tail quotes if TOKEN_INQUOTE and quotes 
 * are unbalanced.
 *
 * @param string: The input string starting with the variable name
 */
char	*ft_remove_inquote(char *string)
{
	int	len;

	len = ft_strlen(string);
	if (!string)
		return (NULL);
	if (*string == '\'' || *string == '\"')
		string = ft_str_replace(string, 0, "");
	if (string[len - 2] == '\'' || string[len - 2] == '\"')
		string = ft_str_replace(string, (len - 2), "");
	return (string);
}

/**
 * @function: ft_env_len
 * @brief: Calculates the length of an environment variable name
 *
 * @param input: The input string starting with the variable name
 * @return: The length of the environment variable name
 */
int	ft_env_len(const char *input)
{
	int	len;

	len = 0;
	if (ft_strncmp(input, "$?", 2) == 0)
		len = 2;
	else if (input[len] == '$')
	{
		len++;
		while (input[len] && (ft_isalnum(input[len]) || input[len] == '_'))
			len++;
	}
	else
		len = 1;
	return (len);
}

/**
 * @function: ft_var_exp
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

char	*ft_var_exp(char **input, int start_index, char **env)
{
	int		env_len;
	char	*var;
	char	*env_var;

	env_len = ft_env_len(*input + start_index);
	var = ft_substr(*input + start_index, 0, env_len);
	env_var = ft_env_search(var, env);
	return (free(var), env_var);
}

/**
 * @function: ft_getenv
 * @brief: takes a string and searches the env array for a corresponding
 * string after the = sign
 * 
 * @param string: search string
 * @param env: array of strings to search
 * @return: the result env if found, NULL if not found.
 */
char	*ft_getenv(char *string, char **env)
{
	int		i;
	int		len;
	char	*value;

	if (!string || !env)
		return (NULL);
	len = ft_strlen(string);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], string, len) == 0 && env[i][len] == '=')
		{
			value = ft_strdup(env[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}
