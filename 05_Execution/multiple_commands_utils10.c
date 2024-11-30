/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils10.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:18:57 by wichee            #+#    #+#             */
/*   Updated: 2024/11/30 16:19:02 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_parent_for_handling_forking_process
 * @brief: handle parent process for the function handling forking process
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
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
	{
		ft_dprintf(1, "Child %d exited normally, with exit code %d\n", params->pid, WEXITSTATUS(status));
		*params->exit_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		ft_dprintf(1, "Child %d exited with signals, with exit code %d\n", params->pid, WTERMSIG(status));
		*params->exit_status = WTERMSIG(status) + 128;
	}
	ft_dprintf(1, "Current exit status %d\n", *params->exit_status);
	ft_signal(NULL, NULL, NULL, PARENT);
}
