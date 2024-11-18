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
void    ft_signal(t_list *exec_data, t_process_type process_flag)
{
    t_signal_data   *data;

    data = (t_signal_data *)malloc(sizeof(t_signal_data));
    data->exec_data_head = exec_data;
    data->exit_status = 0;
    if (process_flag == PARENT)
        parent_signal_handlers(data);
    else if (process_flag == CHILD)
        setup_signal_handlers_for_child(data);
}
