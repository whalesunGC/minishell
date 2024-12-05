/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_utils6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:27:06 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 12:27:07 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: execute_child_process_for_redirections
 * @brief: if last command is a heredoc, will not execute 
 	handle_redirects function as this is already done in
 	heredocs function. if this check passes,
 	will proceed to do redirections
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	execute_child_process_for_redirections(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->pipe_count > 0)
	{
		params->loop_counter = 0;
		while (params->result->redirect[params->loop_counter] != NULL)
			params->loop_counter++;
		if (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"a") == 0)
		{
			freeing_heredoc_pipes(params);
			clean_up_function(params, env);
			exit(EXIT_SUCCESS);
		}
	}
	handle_file_opening_process_for_redirection(params, env);
	handle_execve_for_redirections(params, env);
}

/**
 * @function: handle_redirects
 * @brief: handling redirections if command consists of redirects
 	execute_child_process is in single_command_utils1.c
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails, 0 if all commands is executed
 */

int	handle_redirects(
			t_redirect_single_command_params *params, char ***env)
{
	while (params->result->redirect[params->i] != NULL)
		params->i++;
	if (*params->exit_status != 0)
		return (-1);
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		execute_child_process_for_redirections(params, env);
	else
		handle_parent_for_handling_forking_process(params);
	return (0);
}

/**
 * @function: freeing_heredoc_pipes
 * @brief: freeing pipes which are being set up during the heredoc process
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	freeing_heredoc_pipes(t_redirect_single_command_params *params)
{
	params->z = 0;
	while (params->z < params->pipe_count)
	{
		close(params->pipes[params->z][0]);
		close(params->pipes[params->z][1]);
		params->z++;
	}
}

/**
 * @function: clean_up_function
 * @brief: freeing up resources when child process exits
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	clean_up_function(
			t_redirect_single_command_params *params, char ***env)
{
	free(params->signal_data);
	freeing_heredoc_pipes(params);
	free_pipes(params->pipes, params->pipe_count);
	ft_free(&params->msd);
	(void)env;
	rl_clear_history();
}

/**
 * @function: handle_other_cases
 * @brief: handling other test case scenarios
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails 0 if all commands is executed
 */

int	handle_other_cases(t_redirect_single_command_params *params, char ***env)
{
	if (params->result->cmd[0] == NULL)
	{
		if (handle_single_commands(params, env) == -1)
			return (-1);
	}
	else
	{
		params->av = params->result->cmd;
		params->ac = 0;
		while (params->av[params->ac] != NULL)
			params->ac++;
		if (handle_single_commands(params, env) == -1)
			return (-1);
	}
	return (0);
}
