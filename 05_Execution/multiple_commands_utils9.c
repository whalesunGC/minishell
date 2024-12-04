/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils9.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:02:20 by apoh              #+#    #+#             */
/*   Updated: 2024/11/27 16:02:23 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: closing_heredocs_pipes
 * @brief: handle closing of heredoc pipes
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	closing_heredocs_pipes(t_piping_multiple_command_params *params)
{
	params->heredocs_pipe_number = 0;
	while (params->heredocs_pipe_number < params->heredocs_count)
	{
		close(params->heredocs_pipes[params->heredocs_pipe_number][0]);
		close(params->heredocs_pipes[params->heredocs_pipe_number][1]);
		params->heredocs_pipe_number++;
	}
}

/**
 * @function: handle_arguments
 * @brief: handling the commands after input
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if fork fails. 0 if everything is successful.
 */

void	closing_main_pipes(t_piping_multiple_command_params *params)
{
	params->j = 0;
	while (params->j < params->total - 1)
	{
		close(params->pipes[params->j][0]);
		close(params->pipes[params->j][1]);
		params->j++;
	}
}

/**
 * @function: handle_invalid_command
 * @brief: cleanup if command is invalid
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_invalid_command(
			t_piping_multiple_command_params *params, char ***env)
{
	ft_dprintf(2, "%s : command not found\n", params->result->cmd[0]);
	if (params->command_path != params->result->cmd[0])
		free(params->command_path);
	clean_up_function_multiple_commands(params, env);
	exit(127);
}

/**
 * @function: handle_execve_failure
 * @brief: cleanup if execve fails
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_execve_failure(
			t_piping_multiple_command_params *params, char ***env)
{
	perror("execve process failed");
	if (params->command_path != params->result->cmd[0])
		free(params->command_path);
	clean_up_function_multiple_commands(params, env);
	exit(126);
}

/**
 * @function: handle_pipe_and_waiting_for_child
 * @brief: cleanup after all processes are forked already
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_pipe_and_waiting_for_child(
			t_piping_multiple_command_params *params)
{
	int	status;

	ft_dprintf(2, "Debugging closing pipes and waiting"
		"for child process to finish\n");
	if (params->heredocs_count > 0)
		closing_heredocs_pipes(params);
	closing_main_pipes(params);
	params->j = 0;
	while (params->j < params->total)
	{
		ignore_parent_signals();
		if (waitpid(-1, &status, 0) == params->pid_array[params->total - 1])
		{
			if (WIFEXITED(status))
			{
				ft_dprintf(1, "Child %d exited normally, with exit code %d\n", params->pid_array[params->total - 1], WEXITSTATUS(status));
				*params->exit_status = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				ft_dprintf(1, "Child %d exited with signals, with exit code %d\n", params->pid_array[params->total - 1], WTERMSIG(status));
				*params->exit_status = WTERMSIG(status) + 128;
			}
		}
		else
			ft_dprintf(1, "Current exit status %d\n", *params->exit_status);
		params->j++;
	}
	ft_signal(NULL, NULL, NULL, PARENT);
}
