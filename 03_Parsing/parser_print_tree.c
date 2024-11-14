/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print_tree.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:26:30 by wichee            #+#    #+#             */
/*   Updated: 2024/10/16 15:26:47 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_print_tree_helper
 * @brief: Recursively prints the AST in a tree-like format
 *
 * @param node: The current node in the AST
 * @param depth: The depth of the current node in the tree
 */
void	ft_print_tree_helper(t_ast_node *node, int depth)
{
	int	i;

	i = 0;
	if (node == NULL)
		return ;
	while (i < depth)
	{
		ft_printf("  ");
		i++;
	}
	if (node->type == AST_COMMAND)
		ft_printf("COMMAND: %s\n", node->value);
	else if (node->type == AST_PIPE)
		ft_printf("PIPE\n");
	else if (node->type == AST_AND)
		ft_printf("AND\n");
	else if (node->type == AST_OR)
		ft_printf("OR\n");
	else if (node->type == AST_SUBSHELL)
		ft_printf("SUBSHELL\n");
	else if (ast_is_redirection(node))
		ft_printf("REDIRECTION: %s\n", node->value);
	else if (node->type == AST_HEREDOC)
		ft_printf("HEREDOC: %s\n", node->value);
	else if (node->type == AST_ARGUMENT)
		ft_printf("ARGUMENT: %s\n", node->value);
	else if (node->type == AST_HD_DELIMITER_Q)
		ft_printf("HD_DELIMITER_Q: %s\n", node->value);
	else if (node->type == AST_HD_DELIMITER_NQ)
		ft_printf("HD_DELIMITER_NQ: %s\n", node->value);
	else if (node->type == AST_RD_FD)
		ft_printf("RD_FD: %s\n", node->value);
	else
		ft_printf("UNKNOWN\n");
	ft_print_tree_helper(node->left, depth + 1);
	ft_print_tree_helper(node->right, depth + 1);
}

/**
 * @function: ft_print_tree
 * @brief: Prints the entire AST in a tree-like format
 *
 * @param root: The root node of the AST
 */
void	ft_print_tree(t_ast_node *root)
{
	ft_printf("Abstract Syntax Tree:\n");
	ft_print_tree_helper(root, 0);
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

	ft_printf("\n=== EXECUTION LIST ===\n");
	while (exec_node)
	{
		node = (t_exec_node *)exec_node->content;
		ft_printf("Node Type: %s\n",
			node->type == AST_PIPE ? "PIPE" : "COMMAND");
		if (node->type == AST_COMMAND)
		{
			ft_printf("Command: %s\n", node->cmd[0]);
			ft_printf("Command Arguments:\n");
			if (node->cmd[0])
				ft_print_stringarray(node->cmd, 1);
			else
				ft_print_stringarray(node->cmd, 0);
			if (node->redirect)
			{
				ft_printf("Redirects:\n");
				ft_print_stringarray(node->redirect, 0);
				if (node->rd_arg)
				{
					ft_printf("Redirect Arguments:\n");
					ft_print_stringarray(node->rd_arg, 0);
				}
				if (node->delimiter)
				{
					ft_printf("Heredoc Delimiter:\n");
					ft_print_stringarray(node->delimiter,0);
				}	
			}
		}
		ft_printf("-------------------\n");
		exec_node = exec_node->next;
	}
	ft_printf("=== END OF LIST ===\n\n");
}

/**
 * @function: ft_print_stringarray
 * @brief: prints out a stringarray from an index
 *
 * @param stringarray: pointer the string array
 * @param i: index from which to start printing
 * @return: void function
 */
void	ft_print_stringarray(char **stringarray, int i)
{
	while (stringarray[i])
	{
		ft_printf("  [%d]: %s\n", i, stringarray[i]);
		i++;
	}
}