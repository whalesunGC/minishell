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
 * @function: initialise_params_single
 * @brief: sets up the initialising of parameters before we start the function
 * 
 * @param node: *params : structure of
 	multiple command parameters
 * @param msd: minishell data struct	
 * @return: void function
 */
static void	init_params_single(t_list *node,
	t_redirect_single_command_params *params, t_ms_data *msd)
{
	params->exec_data_head = node;
	params->exit_status = msd->exit_status;
	params->msd = msd;
}

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

void	execution(t_list *node, char ***env, t_ms_data *msd)
{
	t_redirect_single_command_params	params;

	if (checking_if_pipes_exist(node) == -1)
		return ;
	ft_memset(&params, 0, sizeof(t_redirect_single_command_params));
	finding_heredocs(&params, node);
	init_params_single(node, &params, msd);
	if (params.pipe_count > 16)
	{
		ft_dprintf(2, "Maximum here-document count exceeded\n");
		return ;
	}
	if (params.pipe_count == 0)
		handling_no_heredocs(&params, env, node);
	else
	{
		if (creating_pipes(&params) == -1)
			return ;
		if (handling_heredocs(&params, env, node) == -1)
			;
		freeing_heredoc_pipes(&params);
		free_pipes(params.pipes, params.pipe_count);
	}
}
