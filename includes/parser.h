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

typedef struct s_ast_node
{
	void					*content;
	struct s_ast_node		*root;
	struct s_ast_node		*left_leaf;
	struct s_ast_node		*right_leaf;
}	t_ast_node;

//parser.c
t_ast_node	*parser(t_list *token_data);
#endif

//paser_utils.c
void	ft_treeclear(t_ast_node **ast, void (*del)(void *));