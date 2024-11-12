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
 * @function: swap_parent_node
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

/**
 * @function: create_redir
 * @brief: creates ast_nodes that reflect the correct redirection token type
 *
 * @params: context
 * @return: pointer to ast_node;
 */
t_ast_node	*create_redir(t_parser_context *context)
{
	t_ast_node	*node;

	node = NULL;
	if (is_token_type(context, TOKEN_REDIRECTION_IN))
		node = create_ast_node(AST_REDIR_IN);
	else if (is_token_type(context, TOKEN_REDIRECTION_OUT))
		node = create_ast_node(AST_REDIR_OUT);
	else if (is_token_type(context, TOKEN_REDIRECTION_APPEND))
		node = create_ast_node(AST_REDIR_APPEND);
	return (node);
}

/**
 * @function: handle_redirection_target
 * @brief: Creates and processes the target node for redirection
 * 
 * @param context: The parser context containing token information
 * @param node: The parent redirection node
 * @return: void
 */
void	handle_redirection_target(t_parser_context *context, t_ast_node *node)
{
	t_ast_node	*target_node;

	if (is_token_type(context, TOKEN_RD_FD))
	{
		target_node = create_ast_node(AST_RD_FD);
		target_node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		add_child_node(node, target_node);
		advance_token(context);
	}
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a redirection target");
	}
}

/**
 * @function: handle_heredoc_delimiter
 * @brief: Creates and processes the delimiter node for heredoc
 * 
 * @param context: The parser context containing token information
 * @param node: The parent heredoc node
 * @return: void
 */
void	handle_heredoc_delimiter(t_parser_context *context, t_ast_node *node)
{
	t_ast_node	*target_node;

	if (is_token_type(context, TOKEN_HD_DELIMITER_Q))
		target_node = create_ast_node(AST_HD_DELIMITER_Q);
	else if (is_token_type(context, TOKEN_HD_DELIMITER_NQ))
		target_node = create_ast_node(AST_HD_DELIMITER_NQ);
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a heredoc delimiter");
		return ;
	}
	target_node->value = ft_strdup(((t_lex_data *)
				context->current_token->content)->raw_string);
	add_child_node(node, target_node);
	advance_token(context);
}
