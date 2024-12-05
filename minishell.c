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
 * @function: handle_parsing
 * @brief:	function that handles the parsing portion of minishell
 * 
 * @param msd: minishell data
 * @return: void
 */
static void	handle_parsing(t_ms_data *msd)
{
	if (!ft_is_blank(msd->input))
		add_history(msd->input);
	msd->input = input_clean(msd->input, msd->exit_status);
	msd->token_data = lexer(msd->input);
	msd->token_data = expansion(msd->token_data, msd->env, msd->exit_status);
	msd->ast_root = parser(msd->token_data, msd->exit_status);
	msd->exec_data = ft_ast_to_linkedlist(msd->ast_root);
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
static void	ft_free_after_exec(t_ms_data **msd)
{
	if ((*msd)->exec_data)
		ft_lstclear(&(*msd)->exec_data, ft_free_exec_data);
	if ((*msd)->input)
		free((*msd)->input);
	if ((*msd)->token_data)
		ft_lstclear(&(*msd)->token_data, ft_free_lex_data);
	if ((*msd)->ast_root)
		ft_treeclear(&(*msd)->ast_root, free);
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
void	ft_free(t_ms_data **msd)
{
	if ((*msd)->env)
		free_dup_envp((*msd)->env);
	if ((*msd)->exec_data)
		ft_lstclear(&(*msd)->exec_data, ft_free_exec_data);
	if ((*msd)->input)
		free((*msd)->input);
	if ((*msd)->token_data)
		ft_lstclear(&(*msd)->token_data, ft_free_lex_data);
	if ((*msd)->ast_root)
		ft_treeclear(&(*msd)->ast_root, free);
	if ((*msd)->exit_status)
		free((*msd)->exit_status);
	if ((*msd))
		free((*msd));
}

/**
 * @function: handle_init_main
 * @brief:	inits the main functiion
 * 
 * @param ac: input variable count
 * @param av: input variables
 * @param envp: env
 * @param msd: minishell data struct
 * @return: void
 */
static t_ms_data	*handle_init_main(int ac, char **av, char **envp,
	t_ms_data *msd)
{
	msd = (t_ms_data *)malloc(sizeof(t_ms_data));
	if (!msd)
		return (ft_free(&msd), NULL);
	ft_memset(msd, 0, sizeof(t_ms_data));
	(void)ac;
	(void)av;
	if (envp[0] == NULL)
		ft_dprintf(1, "envp not initialised\n");
	msd->env = copy_envp(envp);
	if (msd->env == NULL)
	{
		ft_dprintf(2, "Duplicate of envp error!\n");
		return (ft_free(&msd), NULL);
	}
	msd->token_data = NULL;
	msd->ast_root = NULL;
	msd->exec_data = NULL;
	msd->exit_status = (int *)malloc(sizeof(int));
	if (!msd->exit_status)
		return (ft_free(&msd), NULL);
	*msd->exit_status = 0;
	ft_signal(NULL, NULL, NULL, PARENT);
	signal_parent(msd->exit_status);
	return (msd);
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
	t_ms_data	*msd;

	msd = NULL;
	msd = handle_init_main(ac, av, envp, msd);
	if (!msd)
		exit(EXIT_FAILURE);
	while (1)
	{
		msd->input = readline("minishell>> ");
		if (msd->input == NULL)
		{
			ft_dprintf(1, "Exiting minishell\n");
			break ;
		}
		handle_parsing(msd);
		if (!msd->input || !msd->exec_data)
		{
			ft_free_after_exec(&msd);
			continue ;
		}
		execution(msd->exec_data, &msd->env, msd);
		execution_with_pipes(msd->exec_data, &msd->env, msd);
		ft_free_after_exec(&msd);
	}
	return (rl_clear_history(), ft_free(&msd), 0);
}
