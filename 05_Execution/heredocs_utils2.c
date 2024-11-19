/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 22:38:06 by apoh              #+#    #+#             */
/*   Updated: 2024/11/12 22:38:17 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_exit_conditions_for_heredocs
 * @brief: handling certain exit conditions
 	so that execve will not be run
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_exit_conditions_for_heredocs(t_redirect_single_command_params
*params, char ***env)

{
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0))
	{
		write(0, "Exiting heredocs\n", 17);
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: handle_execve_for_heredocs
 * @brief: executing execve for heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success,
 	0 will never be reached if execve is successful.
 */

int	handle_execve_for_heredocs(t_redirect_single_command_params
*params, char ***env)

{
	if (dup2(params->pipes[params->pipe_count - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (-1);
	}
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (execve(params->command_path, params->result->cmd, *env) == -1)
	{
		perror("execve failed");
		params->z = 0;
		while (params->z < params->pipe_count)
		{
			close(params->pipes[params->z][0]);
			close(params->pipes[params->z][1]);
			params->z++;
		}
		free_dup_envp(*env);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * @function: handle_child_execution
 * @brief: forking child processes and to
 	execute them upon certain conditions
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_child_execution(t_redirect_single_command_params
*params, char ***env)

{
	write(0, "Entering the heredocs loop\n", 27);
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
	{
		handle_exit_conditions_for_heredocs(params, env);
		if (handle_execve_for_heredocs(params, env) == -1)
			return (-1);
	}
	return (0);
}
