/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:13:31 by apoh              #+#    #+#             */
/*   Updated: 2024/11/11 19:13:33 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
 * @function: free_pipes
 * @brief: freeing pipes after the usage of the functions
 * 
 * @param **pipes: 2d array of pipes to keep track of
 	which pipe you are working with
 	num_pipes: number of pipes in total
 * 
 * @return: void function
 */

void	free_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	if (pipes == NULL)
		return ;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

/**
 * @function: free_heredocs_pipes
 * @brief: freeing heredoc pipes after the usage of the functions
 * 
 * @param **heredocs_pipes: 2d array of pipes to keep track of
 	which heredoc pipe you are working with
 	heredocs_count: number of heredoc pipes in total
 * 
 * @return: void function
 */

void	free_heredocs_pipes(int **heredocs_pipes, int heredocs_count)
{
	int	i;

	i = 0;
	if (heredocs_pipes == NULL)
		return ;
	while (i < heredocs_count)
	{
		free(heredocs_pipes[i]);
		i++;
	}
	free(heredocs_pipes);
}
