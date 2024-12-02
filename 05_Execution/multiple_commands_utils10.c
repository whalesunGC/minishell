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
 * @param params *params: structure for
 	Multi command parameters
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
