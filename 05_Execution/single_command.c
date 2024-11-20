/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:17:49 by apoh              #+#    #+#             */
/*   Updated: 2024/11/19 16:03:26 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: execution
 * @brief: execution of a single command where it will
 	handle redirections and no redirections
 * 
 * @param t_list *node: structure of the linked list
 	where it points to void content
 	***env : *** is needed if env is needed to be updated
 * 
 * @return: -1 if error, 0 if success
 */

void	execution(t_list *node, char ***env, int *exit_status)
{
	t_redirect_single_command_params	params;

	if (checking_if_pipes_exist(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_redirect_single_command_params));
	ft_printf("Entering process of single command execution\n");
	finding_heredocs(&params, node);
	params.exec_data_head = node;
	params.exit_status = exit_status;
	if (params.pipe_count == 0)
	{
		write(2, "Entering no pipe count\n", 23);
		handling_no_heredocs(&params, env, node);
	}
	else
	{
		write(2, "Entering pipe count\n", 20);
		if (creating_pipes(&params) == -1)
			return ;
		if (handling_heredocs(&params, env, node) == -1)
			return ;
		params.z = 0;
		while (params.z < params.pipe_count)
		{
			close(params.pipes[params.z][0]);
			close(params.pipes[params.z][1]);
			params.z++;
		}
		free_pipes(params.pipes, params.pipe_count);
	}
}
