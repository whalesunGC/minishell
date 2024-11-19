/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:29:42 by apoh              #+#    #+#             */
/*   Updated: 2024/11/06 22:07:37 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: execution_with_pipes
 * @brief: handling arguments with pipe commands
 * 
 * @param t_list *node : structure of linked list
 	where it points to void content
 	char **env : duplicated env from envp in the main function
 * 
 * @return: void function
 */

void	execution_with_pipes(t_list *node, char ***env, char *input)
{
	t_piping_multiple_command_params	params;

	if (check_for_pipes(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_piping_multiple_command_params));
	params.exec_data_head = node;
	params.total = check_total_commands(node);
	params.pipes = creating_new_pipes(params.total - 1);
	if (params.pipes == NULL || setting_up_pipes(&params) == -1)
		return ;
	searching_for_heredocs(&params, node);
	if (params.heredocs_count > 0)
	{
		params.heredocs_pipes = creating_heredocs_pipes(params.heredocs_count);
		if (params.heredocs_pipes == NULL || setting_up_heredocs_pipes
			(&params) == -1)
			return ;
		handle_heredocs_multiple_commands(&params, node, env, input);
	}
	params.i = 0;
	params.traverse = node;
	if (handle_arguments(&params, env, input) == -1)
		return ;
	handle_pipe_and_waiting_for_child(&params);
	free_pipes(params.pipes, params.total - 1);
	free_heredocs_pipes(params.heredocs_pipes, params.heredocs_count);
}
