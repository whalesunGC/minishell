/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ast_to_ll.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:14:17 by wichee            #+#    #+#             */
/*   Updated: 2024/10/31 23:14:37 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_ast_to_linkedlist
 * @brief: converts the input AST into a linked list.
 * used as middleware for mandatory submission
 *
 * @param node: pointer to the root of the AST
 * @return: pointer to the linked list or NULL
 */
t_list	*ft_ast_to_linkedlist(t_ast_node *node)
{
	t_list	*list;
	t_list	*left_list;
	t_list	*right_list;

	if (!node)
		return (NULL);
	list = ft_lstnew(node);
	if (!list)
		return (NULL);
	left_list = ft_ast_to_linkedlist(node->left);
	if (left_list)
		ft_lstadd_back(&list, left_list);
	right_list = ft_ast_to_linkedlist(node->right);
	if (right_list)
		ft_lstadd_back(&list, right_list);
	return (list);
}

/**
 * @function: ft_print_exec_list
 * @brief: prints out the entire exec list
 *
 * @param node: pointer to the head of the linked list
 * @return: void function
 */
void	ft_print_exec_list(t_list *node)
{
	t_ast_node	*ast_node;

	ast_node = NULL;
	while (node)
	{
		ast_node = (t_ast_node *)node->content;
		ft_print_exec_helper(ast_node);
		node = node->next;
	}
}
