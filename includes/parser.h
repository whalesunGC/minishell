/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:13:13 by wichee            #+#    #+#             */
/*   Updated: 2024/10/13 17:13:22 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

typedef enum e_ast_node_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECTION,
	AST_HEREDOC,
	AST_ARGUMENT,
	AST_SUBSHELL,
	AST_AND,
	AST_OR
}						t_ast_node_type;

typedef struct s_parser_context
{
	t_list				*current_token;
	t_list				*token_list;
	int					error;
	char				*error_message;
}						t_parser_context;

typedef struct s_ast_node
{
	t_ast_node_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	struct s_ast_node	*parent;
}						t_ast_node;

// parser.c
t_ast_node	*parser(t_list *token_data);
t_ast_node	*parse_command_line(t_parser_context *context);
t_ast_node	*parse_pipeline(t_parser_context *context);
t_ast_node	*parse_subshell_or_pipeline(t_parser_context *context);
void		ft_print_tree_helper(t_ast_node *node, int depth);
void		ft_print_tree(t_ast_node *node);

// parser_recursive_descent.c
t_ast_node	*parse_command(t_parser_context *context);
t_ast_node	*parse_redirection(t_parser_context *context);
t_ast_node	*parse_heredoc(t_parser_context *context);

// parser_rd_helper.c
int			is_token_type(t_parser_context *context, t_token_type type);
void		advance_token(t_parser_context *context);
t_ast_node	*create_ast_node(t_ast_node_type type);
int			expect_token(t_parser_context *context, t_token_type expected_type);
void		add_child_node(t_ast_node *parent, t_ast_node *child);
void		swap_parent_node(t_ast_node *parent, t_ast_node *child);

// parser utils
void		ft_treeclear(t_ast_node **ast, void (*del)(void *));
int			is_redirection(t_parser_context *context);
int			is_heredoc(t_parser_context *context);

// parser_print.c
void		ft_print_tree_helper(t_ast_node *node, int depth);
void		ft_print_tree(t_ast_node *root);
#endif
