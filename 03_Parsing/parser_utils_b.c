/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 09:57:35 by wichee            #+#    #+#             */
/*   Updated: 2024/10/15 09:58:00 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: ft_free_node_components
 * @brief: Helper function that frees all components of an exec node
 *
 * @param node: Pointer to the exec node structure
 * @return: no return value, void function
 */
void	ft_free_node_components(t_exec_node *node)
{
	if (node->cmd)
	{
		ft_free_exec_helper(node->cmd);
		free(node->cmd);
	}
	if (node->rd_arg)
	{
		ft_free_exec_helper(node->rd_arg);
		free(node->rd_arg);
	}
	if (node->delimiter)
	{
		ft_free_exec_helper(node->delimiter);
		free(node->delimiter);
	}
	if (node->redirect)
	{
		ft_free_exec_helper(node->redirect);
		free(node->redirect);
	}
}
