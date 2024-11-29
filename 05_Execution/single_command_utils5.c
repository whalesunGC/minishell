/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:01:18 by apoh              #+#    #+#             */
/*   Updated: 2024/11/19 16:01:19 by apoh             ###   ########.fr       */
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
	ft_dprintf(2, "Debugging handle redirects\n");
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
	ft_dprintf(2, "Debugging freeing heredoc pipes single commands\n");
	params->z = 0;
	if (params->pipe_count != 0)
	{
		while (params->z < params->pipe_count)
		{
			close(params->pipes[params->z][0]);
			close(params->pipes[params->z][1]);
			params->z++;
		}
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
	ft_dprintf(2, "Debugging clean up function single commands\n");
	freeing_heredoc_pipes(params);
	free_pipes(params->pipes, params->pipe_count);
	ft_lstclear(&params->exec_data_head, ft_free_exec_data);
	free(params->signal_data);
	free(params->exit_status);
	free_dup_envp(*env);
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
	ft_dprintf(2, "Debugging handle other cases\n");
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
