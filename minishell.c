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

/**
 * @function: ft_is_blank
 * @brief:	check if string contains only '\n' ' ' '\t'
 * 
 * @param string: input string
 * @return: int 1 or 0
 */
static int	ft_is_blank(char *string)
{
	while (*string) 
	{
		if (*string != '\n' && !ft_iswhitespace(*string))
			return (0);
		string++;
	}
    return (1);
}

/**
 * @function: ft_free
 * @brief:	function to free all created structs at exit.
 * 
 * @param token_data: linked-list that contains the stream of tokens
 * @param ast_root: root of the ast that is a binary tree of
 * the bash syntax.
 * @param exec_data: head of exec_data
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
	char		**env;
	char		*input;
	t_list		*token_data;
	t_ast_node	*ast_root;
	t_list		*exec_data;
	int			*exit_status;

	(void)ac;
	(void)av;
	if (envp[0] == NULL)
		ft_printf("envp not initialised\n");
	env = copy_envp(envp);
	if (env == NULL)
	{
		ft_printf("Duplicate of envp error!\n");
		exit(EXIT_FAILURE);
	}
	token_data = NULL;
	ast_root = NULL;
	exec_data = NULL;
	exit_status = (int *)malloc(sizeof(int));
	if (!exit_status)
		return (0);
	*exit_status = 0;
	ft_signal(NULL, NULL, NULL, PARENT);
	signal_parent(exit_status);
	while (1)
	{
		input = readline("minishell>> ");
		if (input == NULL)
		{
			ft_printf("Exiting minishell\n");
			break ;
		}
		if (!ft_is_blank(input))
			add_history(input);
		input = input_clean(input);
		if (input == NULL)
			continue ;
		token_data = lexer(input);
		if (!token_data)
			continue;
		token_data = expansion(token_data, env, exit_status);
		ast_root = parser(token_data);
		exec_data = ft_ast_to_linkedlist(ast_root);
		if (!exec_data)
		{
			free(input);
			ft_free(&token_data, &ast_root);
			continue ;
		}
		free(input);
		ft_free(&token_data, &ast_root);
		execution(exec_data, &env, exit_status);
		execution_with_pipes(exec_data, &env, exit_status);
		ft_lstclear(&exec_data, ft_free_exec_data);
	}
	free_dup_envp(env);
	rl_clear_history();
	free(input);
	ft_free(&token_data, &ast_root);
	ft_lstclear(&exec_data, ft_free_exec_data);
	return (free(exit_status), 0);
}
