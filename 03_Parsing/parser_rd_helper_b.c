/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rd_helper_b.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:16:33 by wichee            #+#    #+#             */
/*   Updated: 2024/10/23 18:11:27 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @brief swaps the parent and child nodes.
 *
 * @param parent The parent node to which the child node will be swapped
 * @param child The child node to be the parent.
 */
void	swap_parent_node(t_ast_node *parent, t_ast_node *child)
{
	if (!child->left)
		child->left = parent;
	else if (!child->right)
		child->right = parent;
	if (!parent->parent)
		parent->parent = child;
	else if (parent->parent->left == parent)
	{
		parent->parent->left = child;
		child->parent = parent->parent;
		parent->parent = child;
	}
	else if (parent->parent->right == parent)
	{
		parent->parent->right = child;
		child->parent = parent->parent;
		parent->parent = child;
	}
}
