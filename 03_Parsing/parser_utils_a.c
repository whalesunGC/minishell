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
 * @function: ft_treeclear
 * @brief: thats the root of a tree and cleans its contents.
 * 
 * @param ast: the root node of the AST
 * @param del: the void function that deleles or frees the
 * memory stored in content.
 * 
 * @return: no return value, void function.
 */
void	ft_treeclear(t_ast_node **ast, void (*del)(void *))
{
	t_ast_node	*temp_lst;

	if (*ast == NULL)
		;
	else
	{
		while (*ast != NULL)
		{
			del((*ast)->content);
			temp_lst = *ast;
			*ast = (*ast)->left_leaf;
			free(ast);
		}
	}
}