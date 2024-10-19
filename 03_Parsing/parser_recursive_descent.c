/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_recursive_descent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 14:29:17 by wichee            #+#    #+#             */
/*   Updated: 2024/10/16 14:29:19 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: parse_command
 * @brief: Parses a single command with its arguments and redirections
 *
 * @param context: The parser context containing token information
 * @return: The AST node representing the command
 */
t_ast_node	*parse_command(t_parser_context *context)
{
	t_ast_node	*node;
	t_ast_node	*redir_node;
	t_ast_node	*arg_node;
	t_ast_node	*heredoc_node;

	node = create_ast_node(AST_COMMAND);
	redir_node = NULL;
	arg_node = NULL;
	heredoc_node = NULL;
	while (is_redirection(context))
	{
		redir_node = parse_redirection(context);
		add_child_node(node, redir_node);
	}
	while (is_heredoc(context))
	{
		heredoc_node = parse_heredoc(context);
		add_child_node(node, heredoc_node);
	}
	if (is_token_type(context, TOKEN_COMMAND))
	{
		node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		advance_token(context);
	}
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a command");
		return (node);
	}
	while (is_token_type(context, TOKEN_STRING))
	{
		arg_node = create_ast_node(AST_ARGUMENT);
		arg_node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		add_child_node(node, arg_node);
		advance_token(context);
	}
	while (is_redirection(context))
	{
		redir_node = parse_redirection(context);
		add_child_node(node, redir_node);
	}
	return (node);
}

/**
 * @function: parse_redirection
 * @brief: Parses a redirection operator and its target
 *
 * @param context: The parser context containing token information
 * @return: The AST node representing the redirection
 */
t_ast_node	*parse_redirection(t_parser_context *context)
{
	t_ast_node	*node;
	t_ast_node	*target_node;

	node = create_ast_node(AST_REDIRECTION);
	if (is_token_type(context, TOKEN_REDIRECTION_OUT)
		|| is_token_type(context, TOKEN_REDIRECTION_IN)
		|| is_token_type(context, TOKEN_REDIRECTION_APPEND))
	{
		node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		advance_token(context);
	}
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a redirection operator");
		return (node);
	}
	if (is_token_type(context, TOKEN_RD_FD))
	{
		target_node = create_ast_node(AST_ARGUMENT);
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
	return (node);
}

/**
 * @function: parse_heredoc
 * @brief: Parses a heredoc operator and its target
 *
 * @param context: The parser context containing token information
 * @return: The AST node representing the heredoc
 */
t_ast_node	*parse_heredoc(t_parser_context *context)
{
	t_ast_node	*node;
	t_ast_node	*target_node;

	node = create_ast_node(AST_REDIRECTION);
	if (is_token_type(context, TOKEN_HEREDOC))
	{
		node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		advance_token(context);
	}
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a heredoc operator");
		return (node);
	}
	if (is_token_type(context, TOKEN_HD_DELIMITER))
	{
		target_node = create_ast_node(AST_ARGUMENT);
		target_node->value = ft_strdup(((t_lex_data *)
					context->current_token->content)->raw_string);
		add_child_node(node, target_node);
		advance_token(context);
	}
	else
	{
		context->error = 1;
		context->error_message = ft_strdup("Expected a heredoc target");
	}
	return (node);
}
