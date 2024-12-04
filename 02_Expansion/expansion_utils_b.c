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
 * @function: handle_empty_expansion
 * @brief: frees and sets raw_string to NULL 
 *
 * @param data: token data
 */
static void	handle_empty_expansion(t_lex_data *data)
{
	free(data->raw_string);
	data->raw_string = NULL;
}

/**
 * @function: ft_is_only_whitespace
 * @brief: checks if string contains only whitespace
 *
 * @param string: input string
 * @return: 1 if true, 0 if false
 */
static int	ft_is_only_whitespace(char *string)
{
	if (!string)
		return (0);
	while (*string)
	{
		if (ft_iswhitespace(*string))
			;
		else
			return (0);
		string++;
	}
	return (1);
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
		token_data = handle_word_split(ft_strdup(data->raw_string), token_data,
				exit_status);
		data = (t_lex_data *)(*token_data)->content;
		data->type = lexer_token_type_a(data->raw_string, data->is_first_token);
		if (data->type == 42)
			data->type = lexer_token_type_c(data->raw_string, data->in_quote,
					data->is_hd_delimiter, data->is_fd);
	}
	if (*data->raw_string == '\0' || ft_is_only_whitespace(data->raw_string))
		handle_empty_expansion(data);
	if ((data->type == TOKEN_STRING || data->type == TOKEN_COMMAND
			|| data->type == TOKEN_INQUOTE) && ft_has_quote(data->raw_string))
		data->raw_string = ft_remove_quote(data->raw_string);
	*token_data = (*token_data)->next;
	return (*token_data);
}
