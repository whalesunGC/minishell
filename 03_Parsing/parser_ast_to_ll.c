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
 * @function: ft_ast_preorder
 * @brief: traverses AST and convert it into a
 * SLinked_list
 *
 * @param node: pointer to the root of the AST
 * @return: pointer to linked list or NULL
 */
t_list	*ft_ast_preorder(t_ast_node *node)
{
	t_list	*list;
	t_list	*left_list;
	t_list	*right_list;

	if (!node)
		return (NULL);
	list = ft_lstnew(node);
	if (!list)
		return (NULL);
	left_list = ft_ast_preorder(node->left);
	if (left_list)
		ft_lstadd_back(&list, left_list);
	right_list = ft_ast_preorder(node->right);
	if (right_list)
		ft_lstadd_back(&list, right_list);
	return (list);
}

/**
 * @function: ft_handle_invalid_nodes
 * @brief: checks for invalid node types and handles errors
 * 
 * @param ast_node: current AST node being processed
 * @param exec_list: list to clear in case of error
 * @return: 1 if invalid node found, 0 otherwise
 */
static int	ft_handle_invalid_nodes(t_ast_node *ast_node, t_list *exec_list)
{
	if (ast_node->type == AST_AND || ast_node->type == AST_OR)
	{
		ft_lstclear(&exec_list, ft_free_exec_data);
		ft_dprintf(2, "Syntax error: && or ||\n");
		return (1);
	}
	if (ast_node->type == AST_SUBSHELL)
	{
		ft_lstclear(&exec_list, ft_free_exec_data);
		ft_dprintf(2, "Syntax error: Subshell\n");
		return (1);
	}
	return (0);
}

/**
 * @function: ft_process_exec_node
 * @brief: processes and adds an exec node to the list
 * 
 * @param exec_node: node to process
 * @param exec_list: list to add node to
 * @param list: current position in AST list
 * @return: updated exec_list or NULL on error
 */
static t_list	*ft_process_exec_node(t_exec_node *exec_node,
									t_list *exec_list, t_list *list)
{
	if (exec_node->type == AST_COMMAND)
		exec_node = ft_fill_exec_node(exec_node, list);
	if (!exec_list)
		exec_list = ft_lstnew(exec_node);
	else
		ft_lstadd_back(&exec_list, ft_lstnew(exec_node));
	return (exec_list);
}

/**
 * @function: ft_exec_node
 * @brief: takes a linked-list that has been pre-order
 * traversed and outputs a linked-list containing
 * exec_nodes.
 *
 * @param list: pointer to the head of the po_linkedlist
 * @return: pointer to the head of the exec_linkedlist.
 */
t_list	*ft_exec_node(t_list *list)
{
	t_exec_node	*exec_node;
	t_ast_node	*ast_node;
	t_list		*exec_list;

	exec_node = NULL;
	exec_list = NULL;
	while (list)
	{
		ast_node = (t_ast_node *)list->content;
		if (ft_handle_invalid_nodes(ast_node, exec_list))
			return (NULL);
		if (ast_node->type == AST_PIPE)
			exec_node = ft_create_exec_node(AST_PIPE, ast_node);
		else if (ast_node->type == AST_COMMAND)
			exec_node = ft_create_exec_node(AST_COMMAND, ast_node);
		if (exec_node)
		{
			exec_list = ft_process_exec_node(exec_node, exec_list, list);
			exec_node = NULL;
		}
		list = list->next;
	}
	return (exec_list);
}

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
	t_list	*temp_list;
	t_list	*exec_node;

	list = ft_ast_preorder(node);
	exec_node = ft_exec_node(list);
	while (list)
	{
		temp_list = list;
		list = list->next;
		free(temp_list);
	}
	if (!exec_node)
		return (NULL);
	return (exec_node);
}
