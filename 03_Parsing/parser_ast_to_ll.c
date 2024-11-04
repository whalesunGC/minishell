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
		if (ast_node->type == AST_PIPE)
			exec_node = ft_create_exec_node(AST_PIPE, ast_node);
		else if (ast_node->type == AST_COMMAND)
			exec_node = ft_create_exec_node(AST_COMMAND, ast_node);
		if (exec_node)
		{
			if (exec_node->type == AST_COMMAND)
				exec_node = ft_fill_exec_node(exec_node, list);
			if (!exec_list)
				exec_list = ft_lstnew(exec_node);
			else
				ft_lstadd_back(&exec_list, ft_lstnew(exec_node));
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
	ft_print_exec_list(exec_node);
	return (exec_node);
}

/**
 * @function: ft_print_exec_list
 * @brief: prints out the entire exec list
 *
 * @param node: pointer to the head of the linked list
 * @return: void function
 */
void	ft_print_exec_list(t_list *exec_node)
{
	t_exec_node	*node;
	int			i;

	ft_printf("\n=== EXECUTION LIST ===\n");
	while (exec_node)
	{
		node = (t_exec_node *)exec_node->content;
		ft_printf("Node Type: %s\n",
			node->type == AST_PIPE ? "PIPE" : "COMMAND");
		if (node->type == AST_COMMAND)
		{
			ft_printf("Command: %s\n", node->cmd[0]);
			ft_printf("Arguments:\n");
			i = 1;
			while (node->cmd[i])
			{
				ft_printf("  [%d]: %s\n", i, node->cmd[i]);
				i++;
			}
			if (node->redirection)
			{
				ft_printf("Redirections:\n");
				ft_printf("    type: %s, file: %s\n",
					node->redirection == AST_REDIR_IN ? "<" : node->redirection == AST_REDIR_OUT ? ">" : node->redirection == AST_REDIR_APPEND ? ">>" : "?",
					node->rd_arg);
			}
		}
		ft_printf("-------------------\n");
		exec_node = exec_node->next;
	}
	ft_printf("=== END OF LIST ===\n\n");
}
