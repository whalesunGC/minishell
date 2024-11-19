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
 * @function: ft_free_signal
 * @brief:	function to free signal data
 * 
 * @param data: struct that contains exec_data and exit_status
 * @return: void
 */
void    ft_free_signal(t_signal_data *data)
{
    if (data)
    {
        ft_lstclear(&data->exec_data_head, ft_free_exec_data);
        free(data->input);
        free_dup_envp(data->env);
        free_pipes(data->pipes, data->pipe_count);
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
void    ft_signal(t_redirect_single_command_params *params, char **env, char *input,
        t_process_type process_flag)
{
    t_signal_data   *data;

    data = NULL;    
    if (process_flag == PARENT)
        parent_signal_handlers();
    else if (process_flag == CHILD)
    {
        data = (t_signal_data *)malloc(sizeof(t_signal_data));
        data->exec_data_head = params->exec_data_head;
        data->exit_status = 0;
        data->env = env;
        data->input = input;
        data->pipes = params->pipes;
        data->pipe_count = params->pipe_count;
        setup_signal_handlers_for_child(data);
    }
}
