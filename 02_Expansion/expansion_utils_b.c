/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:34:50 by wichee            #+#    #+#             */
/*   Updated: 2024/11/20 21:54:48 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	ft_printf("variable found: %s\n", var);
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

/**
 * @function: ft_expansion_tokens
 * @brief: this handles the expansion post tokenization
 * 
 * @param token_data: the address to a pointer of
 * a node on the token linked_list.
 * @return: a pointer to the next token.
 */
t_list	*ft_expansion_tokens(t_list **token_data, char **env,
	int *exit_status)
{
	t_lex_data	*data;

	data = (t_lex_data *)(*token_data)->content;
	if (data->type == TOKEN_COMMAND || data->type == TOKEN_INQUOTE
		|| data->type == TOKEN_VARIABLE || data->type == TOKEN_RD_FD
		|| data->type == TOKEN_STRING)
	{
		data->raw_string = expansion_string(data->raw_string, 0,
				env, exit_status);
		token_data = handle_word_split(ft_strdup(data->raw_string), token_data);
		data = (t_lex_data *)(*token_data)->content;
		data->type = lexer_token_type_a(data->raw_string, data->is_first_token);
		if (data->type == 42)
			data->type = lexer_token_type_c(data->raw_string, data->in_quote,
					data->is_hd_delimiter, data->is_fd);
	}
	if ((data->type == TOKEN_STRING || data->type == TOKEN_COMMAND
			|| data->type == TOKEN_INQUOTE) && ft_has_quote(data->raw_string))
		data->raw_string = ft_remove_quote(data->raw_string);
	*token_data = (*token_data)->next;
	return (*token_data);
}
