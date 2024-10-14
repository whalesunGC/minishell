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
 * @return: void
 */
void	ft_free(t_list **token_data)
{
	ft_lstclear(token_data, ft_free_lex_data);
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
	t_ast_node	*ast;

	(void)ac;
	(void)av;
	(void)envp;
	token_data = NULL;
	ast = NULL;
	setup_signal_handlers();
	input = readline("minishell>> ");
	input = expansion(input);
	token_data = lexer(input);
	return (free(input), ft_free(&token_data), 1);
}
