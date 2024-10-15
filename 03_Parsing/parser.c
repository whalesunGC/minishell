/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:12:07 by wichee            #+#    #+#             */
/*   Updated: 2024/10/13 17:12:48 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: parser
 * @brief: creates a syntax tree using a AST after taking in a stream of tokens
 * 
 * @param token_data: the head of a linked_list which contains 
 * the stream of tokens
 * @return: a parsed AST following the bash syntax
 */
t_ast_node	*parser(t_list *token_data)
{
	t_ast_node	*ast_node;

	ast_node = NULL;
	while (token_data)
		{
			ft_printf("Token is %s, Token Type is %d\n",
				((t_lex_data *)(token_data->content))->raw_string,
				((t_lex_data *)(token_data->content))->type);
			token_data = token_data->next;
		}
	return (ast_node);
}
