/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils10.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:08:13 by wichee            #+#    #+#             */
/*   Updated: 2024/12/01 18:09:12 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_parent_for_handling_forking_process_multi
 * @brief: handle parent process for the function handling forking process below
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_parent_for_handling_forking_process_multi(
			t_piping_multiple_command_params *params)
{
	int	status;

	ignore_parent_signals();
	waitpid(params->pid, &status, 0);
	if (WIFEXITED(status))
		*params->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*params->exit_status = WTERMSIG(status) + 128;
	ft_signal(NULL, NULL, NULL, PARENT);
}

/**
 * @function: reset_and_closing_fds_when_error
 * @brief: closing and resetting fds when having error
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	reset_and_closing_fds_when_error(
			t_piping_multiple_command_params *params)
{
	if (params->input_fd < 0)
		params->input_fd = 0;
	if (params->input_fd > 0)
		close(params->input_fd);
	if (params->output_fd > 0)
		close(params->output_fd);
	if (params->output_fd < 0)
		params->output_fd = 0;
}

/**
 * @function: handle_dot_slash_and_slash
 * @brief: finding your command array if you have executables
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_dot_slash_and_slash(
			t_piping_multiple_command_params *params, char ***env)
{
	params->dot_slash = ft_strnstr(params->result->cmd[0],
			"./", ft_strlen(params->result->cmd[0]));
	if (params->dot_slash == NULL)
	{
		params->slash = ft_strchr(params->result->cmd[0], '/');
		if (params->slash == NULL)
			params->command_path = find_command(&params->result->cmd[0],
					0, *env);
		else
			params->command_path = params->result->cmd[0];
	}
	else
		params->command_path = params->result->cmd[0];
}
