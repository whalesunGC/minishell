/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 13:20:45 by wichee            #+#    #+#             */
/*   Updated: 2024/10/06 13:21:40 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_exit_status = 0;

/**
 * @function: ft_free
 * @brief:	function to free all created structs at exit.
 * 
 * @param token_data: linked-list that contains the stream of tokens
 * @param ast_root: root of the ast that is a binary tree of
 * the bash syntax.
 * @return: void
 */
void	ft_free(t_list **token_data, t_ast_node **ast_root)
{
	ft_lstclear(token_data, ft_free_lex_data);
	ft_treeclear(ast_root, free);
}

/**
 * @function: main
 * @brief: this is the entry point to the minishell program
 * 
 * @param: None
 * @return: returns int at exit. 0 for failure, 1 for success,
 */

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_list		*token_data;
	t_ast_node	*ast_root;

	(void)ac;
	(void)av;
	(void)envp;
	token_data = NULL;
	ast_root = NULL;
	setup_signal_handlers();
	input = readline("minishell>> ");
	add_history(input);
	input = input_clean(input);
	token_data = lexer(input);
	token_data = expansion(token_data);
	ast_root = parser(token_data);
	return (free(input), ft_free(&token_data, &ast_root), 1);
}
