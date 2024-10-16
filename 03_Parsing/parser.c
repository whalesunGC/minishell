/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:12:07 by wichee            #+#    #+#             */
/*   Updated: 2024/10/13 17:12:48 by wichee           ###   ########.fr       */
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
void ft_print_tree_helper(t_ast_node *node, int depth)
{
    int	i;

	i = 0;
	if (node == NULL)
        return;
    while (i < depth)
    {
        ft_printf("  ");
        i++;
    }
    switch (node->type)
    {
        case AST_COMMAND:
            ft_printf("COMMAND: %s\n", node->value);
            break;
        case AST_PIPE:
            ft_printf("PIPE\n");
            break;
        case AST_AND:
            ft_printf("AND\n");
            break;
        case AST_OR:
            ft_printf("OR\n");
            break;
        case AST_SUBSHELL:
            ft_printf("SUBSHELL\n");
            break;
		case AST_REDIRECTION:
			ft_printf("REDIRECTION: %s\n", node->value);
			break;
		case AST_ARGUMENT:
			ft_printf("ARGUMENT: %s\n", node->value);
			break;		
        default:
            ft_printf("UNKNOWN\n");
    }
    ft_print_tree_helper(node->left, depth + 1);
    ft_print_tree_helper(node->right, depth + 1);
}

/**
 * @function: ft_print_tree
 * @brief: Prints the entire AST in a tree-like format
 * 
 * @param root: The root node of the AST
 */
void ft_print_tree(t_ast_node *root)
{
    ft_printf("Abstract Syntax Tree:\n");
    ft_print_tree_helper(root, 0);
}

/**
 * @function: parse_command_line
 * @brief: Parses the entire command line, handling AND (&&) and OR (||) operators
 * 
 * @param context: The parser context containing token information
 * @return: The root node of the parsed AST for the command line
 */
t_ast_node *parse_command_line(t_parser_context *context)
{
    t_ast_node	*node;
    t_ast_node	*new_node;
    
    node = parse_subshell_or_pipeline(context);
    while (is_token_type(context, TOKEN_AND) || is_token_type(context, TOKEN_OR))
    {
        if (is_token_type(context, TOKEN_AND))
            new_node = create_ast_node(AST_AND);
        else if (is_token_type(context, TOKEN_OR))
            new_node = create_ast_node(AST_OR);
        new_node->left = node;
        advance_token(context);
        new_node->right = parse_subshell_or_pipeline(context);
        node = new_node;
    }
    return (node);
}

/**
 * @function: parse_subshell_or_pipeline
 * @brief: Parses a subshell (enclosed in parentheses) or a pipeline
 * 
 * @param context: The parser context containing token information
 * @return: The AST node representing the subshell or pipeline
 */
t_ast_node *parse_subshell_or_pipeline(t_parser_context *context)
{
	t_ast_node *subshell_node;

	subshell_node = NULL;
    if (is_token_type(context, TOKEN_PARENTHESIS_L))
    {
        subshell_node = create_ast_node(AST_SUBSHELL);
        advance_token(context);
        subshell_node->left = parse_command_line(context);
        if (!expect_token(context, TOKEN_PARENTHESIS_R))
        {
            context->error = 1;
            context->error_message = ft_strdup("Expected closing parenthesis");
            return (subshell_node);
        }
        return (subshell_node);
    }
    return parse_pipeline(context);
}

/**
 * @function: parse_pipeline
 * @brief: Parses a pipeline of commands connected by pipe (|) operators
 * 
 * @param context: The parser context containing token information
 * @return: The AST node representing the pipeline
 */
t_ast_node *parse_pipeline(t_parser_context *context)
{
    t_ast_node	*node;
	t_ast_node	*pipe_node;
	
	node = parse_command(context); 
    while (is_token_type(context, TOKEN_PIPE))
    {
        pipe_node = create_ast_node(AST_PIPE);
        pipe_node->left = node;
        advance_token(context);
        pipe_node->right = parse_command(context);
        node = pipe_node;
    }
    return (node);
}
/**
 * @function: parser
 * @brief: Creates a syntax tree using an AST after taking in a stream of tokens
 * 
 * @param token_data: The head of a linked list which contains the stream of tokens
 * @return: A parsed AST following the bash syntax, or NULL if an error occurred
 */
t_ast_node *parser(t_list *token_data)
{
    t_parser_context context;
    t_ast_node *ast_root;

    context.current_token = token_data;
    context.token_list = token_data;
    context.error = 0;
    context.error_message = NULL;

    ast_root = parse_command_line(&context);

    if (context.error)
    {
        ft_printf("Error: %s\n", context.error_message);
        ft_treeclear(&ast_root, free);
        return NULL;
    }
	else
		ft_print_tree(ast_root);
    return (ast_root);
}
