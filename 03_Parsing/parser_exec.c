/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:23:08 by wichee            #+#    #+#             */
/*   Updated: 2024/11/04 19:23:10 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_add_string
 * @brief: function that replaces existing string array with
 * an array carrying an additional string
 *
 * @param string_array: pointer to the array of strings
 * @param string: string to be added.
 * @return: the cmd string array char**
 */
char	**ft_add_string(char **string_array, char *string)
{
	char	**new_array;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (string_array && string_array[len])
		len++;
	new_array = (char **)malloc((len + 2) * sizeof(char *));
	if (!new_array)
		return (NULL);
	while (i < len)
	{
		new_array[i] = string_array[i];
		i++;
	}
	new_array[i] = string;
	new_array[i + 1] = NULL;
	free(string_array);
	return (new_array);
}

/**
 * @function: ft_fill_exec_node
 * @brief: takes an exec_node of type command and fills
 * it with required data.
 *
 * @param exec_node: pointer to the exec_node
 * @param list: pointer to te address of the current node
 * @return: a pointer to the exec_node
 */
t_exec_node	*ft_fill_exec_node(t_exec_node *exec_node, t_list *list)
{
	t_ast_node	*ast_node;

	ast_node = NULL;
	list = list->next;
	while (list)
	{
		ast_node = (t_ast_node *)list->content;
		if (ast_node->type == AST_COMMAND)
			break ;
		else if (ast_is_redirection(ast_node))
			exec_node->redirect = ft_add_string(exec_node->redirect,
					ast_node->value);
		else if (ast_node->type == AST_HD_DELIMITER_NQ
			|| ast_node->type == AST_HD_DELIMITER_Q)
			exec_node->delimiter = ft_add_string(exec_node->delimiter,
					ast_node->value);
		else if (ast_node->type == AST_RD_FD)
			exec_node->rd_arg = ft_add_string(exec_node->rd_arg,
					ast_node->value);
		else if (ast_node->type == AST_ARGUMENT)
			exec_node->cmd = ft_add_string(exec_node->cmd, ast_node->value);
		list = list->next;
	}
	return (exec_node);
}

/**
 * @function: ft_create_exec_node
 * @brief: creates the exec_node of the correct type
 *
 * @param type: AST enum type
 * @return: pointer to the head of the exec_linkedlist.
 */
t_exec_node	*ft_create_exec_node(t_ast_node_type type, t_ast_node *ast_node)
{
	t_exec_node	*exec_node;

	exec_node = (t_exec_node *)malloc(sizeof(t_exec_node));
	if (exec_node == NULL)
		return (NULL);
	exec_node->type = type;
	if (type == AST_PIPE)
		exec_node->cmd = NULL;
	else if (type == AST_COMMAND)
	{
		exec_node->cmd = (char **)malloc(2 * sizeof(char *));
		exec_node->cmd[0] = ast_node->value;
		exec_node->cmd[1] = NULL;
	}
	exec_node->redirect = NULL;
	exec_node->rd_arg = NULL;
	exec_node->delimiter = NULL;
	return (exec_node);
}

/**
 * @function: ast_is_redirection
 * @brief: helper function to check is node type is a redirect
 *
 * @param ast_node: ast_node to check
 * @return: int value
 */
int	ast_is_redirection(t_ast_node *ast_node)
{
	if (ast_node->type == AST_REDIR_IN)
		return (1);
	else if (ast_node->type == AST_REDIR_OUT)
		return (1);
	else if (ast_node->type == AST_REDIR_APPEND)
		return (1);
	else if (ast_node->type == AST_HEREDOC)
		return (1);
	else
		return (0);
}
