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
		|| is_token_type(context, TOKEN_REDIRECTION_APPEND));
}

int	is_heredoc(t_parser_context *context)
{
	return (is_token_type(context, TOKEN_HEREDOC));
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
	if ((*ast)->value)
		del((*ast)->value);
	free(*ast);
	*ast = NULL;
}

/**
 * @function: ft_free_exec_data
 * @brief: function that takes the struct t_exec_node
 * and frees all elements within it.
 * 
 * @param data: the struct t_exec_node
 * @return: no return value, void function.
 */
void	ft_free_exec_data(void *data)
{
	t_exec_node	*node;
	int	len;
	int	i;

	node = NULL;
	len = 0;
	i = 0;
	if (data)
	{
		node = (t_exec_node *)data;
		free(node->rd_arg);
		if (node->cmd)
		{
			while (node->cmd && node->cmd[len])
				len++;
			while (i > len)
				free(node->cmd[i]);
		}
		free(node->cmd);
		free(node);
	}
}
