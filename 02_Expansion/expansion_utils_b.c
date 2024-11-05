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
 * @function: ft_expansion_tokens
 * @brief: this handles the expansion post tokenization
 * 
 * @param token_data: the address to a pointer of
 * a node on the token linked_list.
 * @return: a pointer to the next token.
 */
t_list	*ft_expansion_tokens(t_list **token_data)
{
	t_lex_data	*data;

	data = (t_lex_data *)(*token_data)->content;
	if (data->type == TOKEN_COMMAND || data->type == TOKEN_INQUOTE
		|| data->type == TOKEN_VARIABLE || data->type == TOKEN_RD_FD
		|| data->type == TOKEN_STRING)
	{
		data->raw_string = expansion_string(data->raw_string, 0);
		data->type = lexer_token_type_a(data->raw_string,
				data->is_first_token);
		if (data->type == 42)
			data->type = lexer_token_type_b(data->raw_string, data->in_quote,
					data->is_hd_delimiter, data->is_fd);
	}
	*token_data = (*token_data)->next;
	return (*token_data);
}
