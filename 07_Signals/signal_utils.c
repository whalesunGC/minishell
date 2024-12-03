/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:57:25 by wichee            #+#    #+#             */
/*   Updated: 2024/11/20 21:57:27 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_clean_up_pipes
 * @brief: clean up all pipes in child exit on signal
 * @param data: t_sig_data
 */
void	handle_cleanup_pipes(t_sig_data *data)
{
	int	y;

	y = 0;
	while (y < data->heredocs_count)
	{
		close(data->heredocs_pipes[y][0]);
		close(data->heredocs_pipes[y][1]);
		y++;
	}
	while (data->z < data->pipe_count)
	{
		close(data->pipes[data->z][0]);
		close(data->pipes[data->z][1]);
		data->z++;
	}
}

/**
 * @function: signal_parent
 * @brief: create static data for status update
 *
 * @param exit_status: exit_status of current program
 */
void	signal_parent(int *exit_status)
{
	static int	*temp_exit_status;

	if (exit_status)
		temp_exit_status = exit_status;
	if (!exit_status)
		*temp_exit_status = 130;
}

/**
 * @function: signal_cleanup
 * @brief: create static data for cleanup
 *
 * @param data: signal_data for cleanup
 */
void	signal_cleanup(t_sig_data *data)
{
	static t_sig_data	*temp_data;

	if (data)
		temp_data = data;
	if (!data)
		ft_free_signal(temp_data);
}
