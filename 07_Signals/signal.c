/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wichee <wichee@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:02:26 by wichee            #+#    #+#             */
/*   Updated: 2024/11/18 16:02:47 by wichee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_s_command_init
 * @brief: function to handle init of signal data for single command
 *
 * @param
 */
static void	handle_s_command_init(t_redirect_single_command_params *params_s,
		t_sig_data *data, char **env)
{
	data = (t_sig_data *)malloc(sizeof(t_sig_data));
	ft_memset(data, 0, sizeof(t_sig_data));
	params_s->signal_data = data;
	data->exec_data_head = params_s->exec_data_head;
	data->env = env;
	data->pipes = params_s->pipes;
	data->pipe_count = params_s->pipe_count;
	data->command_path = params_s->command_path;
	data->input1 = params_s->input1;
	data->exit_status = params_s->exit_status;
	data->z = 0;
	data->msd = params_s->msd;
	signal_cleanup(data);
	setup_signal_handlers_for_child();
}

/**
 * @function: handle_m_command_init
 * @brief: function to handle init of signal data for single command
 *
 * @param
 */
static void	handle_m_command_init(t_piping_multiple_command_params *params_m,
		t_sig_data *data, char **env)
{
	data = (t_sig_data *)malloc(sizeof(t_sig_data));
	ft_memset(data, 0, sizeof(t_sig_data));
	params_m->signal_data = data;
	data->exec_data_head = params_m->exec_data_head;
	data->env = env;
	data->pipes = params_m->pipes;
	data->pipe_count = params_m->total - 1;
	data->command_path = params_m->command_path;
	data->heredocs_pipes = params_m->heredocs_pipes;
	data->heredocs_count = params_m->heredocs_count;
	data->input1 = params_m->input1;
	data->exit_status = params_m->exit_status;
	data->z = 0;
	data->pid_array = params_m->pid_array;
	data->msd = params_m->msd;
	signal_cleanup(data);
	setup_signal_handlers_for_child();
}

/**
 * @function: ft_free_signal
 * @brief:	function to free signal data
 *
 * @param data: struct that contains exec_data and exit_status
 * @return: void
 */
void	ft_free_signal(t_sig_data *data)
{
	if (data)
	{
		handle_cleanup_pipes(data);
		if (data->pipes)
			free_pipes(data->pipes, data->pipe_count);
		if (data->command_path)
			free(data->command_path);
		if (data->heredocs_pipes)
			free_heredocs_pipes(data->heredocs_pipes, data->heredocs_count);
		if (data->input1)
			free(data->input1);
		if (data->pid_array)
			free(data->pid_array);
		if (data->msd)
			ft_free(&data->msd);
		free(data);
	}
}

/**
 * @function: ft_signal
 * @brief: initializes signal handling
 *
 * @param exec_data : exec_data to free for clean exit
 * @param process_flag : the process type, either PARENT or CHILD
 * @return: void function
 */
void	ft_signal(t_redirect_single_command_params *params_s,
		t_piping_multiple_command_params *params_m, char **env,
		t_process_type process_flag)
{
	t_sig_data	*data;

	data = NULL;
	if (process_flag == PARENT)
		parent_signal_handlers();
	else if (params_s && process_flag == CHILD)
		handle_s_command_init(params_s, data, env);
	else if (params_m && process_flag == CHILD)
		handle_m_command_init(params_m, data, env);
}
