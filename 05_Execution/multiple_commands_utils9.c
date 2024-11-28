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

void	handle_invalid_command(t_piping_multiple_command_params *params, char ***env)
{
	ft_dprintf(2, "command not found\n");
	clean_up_function_multiple_commands(params, env);
	exit(EXIT_FAILURE);
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

void	handle_execve_failure(t_piping_multiple_command_params *params, char ***env)
{
	perror("execve process failed");
	if (params->command_path != params->result->cmd[0])
		free(params->command_path);
	clean_up_function_multiple_commands(params, env);
	exit(EXIT_FAILURE);
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
	ft_dprintf(2, "Debugging closing pipes and waiting for child process to finish\n");
	if (params->heredocs_count > 0)
		closing_heredocs_pipes(params);
	closing_main_pipes(params);
	params->j = 0;
	while (params->j < params->total)
	{
		wait(NULL);
		params->j++;
	}
}
