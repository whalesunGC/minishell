/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:34:50 by wichee            #+#    #+#             */
/*   Updated: 2024/10/19 18:20:08 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
 * @function: ft_string_trim_ends
 * @brief: takes a string, trims both ends and returns the
 * resulting new string. 
 * 
 * @param string: pointer to the address of the input string 
 * (passed by reference)
 * @return: new_string freeing the previous string
 */
char	*ft_string_trim_ends(char **string)
{
	int		len;
	char	*new_string;
	char	*og_string;

	if (!*string)
		return (NULL);
	og_string = *string;
	len = ft_strlen(*string);
	new_string = (char *)malloc((len - 1) * sizeof(char));
	if (!new_string)
		return (NULL);
	ft_strlcpy(new_string, *string + 1, len - 1);
	return (free(og_string), new_string);
}

/**
 * @function: ft_expansion_tokens
 * @brief: this handles the expansion post tokenization
 * 
 * @param token_data: the address to a pointer of
 * a node on the token linked_list.
 * @return: a pointer to the next token.
 */
t_list	*ft_expansion_tokens(t_list **token_data, char **env)
{
	t_lex_data	*data;
	t_list		*node;

	data = (t_lex_data *)(*token_data)->content;
	node = NULL;
	if (data->type == TOKEN_COMMAND || data->type == TOKEN_INQUOTE
		|| data->type == TOKEN_VARIABLE || data->type == TOKEN_RD_FD
		|| data->type == TOKEN_STRING)
	{
		data->raw_string = expansion_string(data->raw_string, 0, env);
		if (ft_has_whitespace(data->raw_string))
			node = lexer(data->raw_string);
		data->type = lexer_token_type_a(data->raw_string, data->is_first_token);
		if (data->type == 42)
			data->type = lexer_token_type_b(data->raw_string, data->in_quote,
					data->is_hd_delimiter, data->is_fd);
	}
	if ((data->type == TOKEN_COMMAND && data->in_quote)
		|| (data->type == TOKEN_INQUOTE && data->in_quote))
		data->raw_string = ft_string_trim_ends(&data->raw_string);
	if (data->type == TOKEN_STRING && ft_has_quote(data->raw_string))
		data->raw_string = ft_remove_quote(data->raw_string);
	*token_data = (*token_data)->next;
	return (*token_data);
}
