/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_a.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:57:35 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 09:58:00 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: is_redirection
 * @brief: Checks if the current token is a redirection operator
 *
 * @param context: The parser context containing token information
 * @return: 1 if the current token is a redirection operator, 0 otherwise
 */
int	is_redirection(t_parser_context *context)
{
	return (is_token_type(context, TOKEN_REDIRECTION_OUT)
		|| is_token_type(context, TOKEN_REDIRECTION_IN)
		|| is_token_type(context, TOKEN_REDIRECTION_APPEND)
		|| is_token_type(context, TOKEN_HEREDOC));
}

/**
 * @function: ft_treeclear
 * @brief: thats the root of a tree and cleans its contents.
 *
 * @param ast: the root node of the AST
 * @param del: the void function that recursively frees the
 * memory stored in content.
 *
 * @return: no return value, void function.
 */
void	ft_treeclear(t_ast_node **ast, void (*del)(void *))
{
	if (ast == NULL || *ast == NULL)
		return ;
	ft_treeclear(&((*ast)->left), del);
	ft_treeclear(&((*ast)->right), del);
	if (del)
		del((*ast)->value);
	free(*ast);
	*ast = NULL;
}
