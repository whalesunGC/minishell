/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_utils7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:27:11 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 12:27:12 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: heredocs
 * @brief: handling the presence of heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	heredocs(t_redirect_single_command_params *params, char ***env)
{
	params->a = 0;
	while (params->result->redirect[params->x] != NULL)
	{
		if ((ft_strcmp(params->result->redirect[params->x], "<<") == 0))
		{
			if (handling_forking_process(params, env) == -1)
				return (-1);
			if (params->result->redirect[params->x + 1] != NULL)
			{
				ft_dprintf(2, "Debugging next redirect\n");
				handling_next_redirect(params);
				continue ;
			}
			else if (params->result->redirect[params->x + 1] == NULL)
			{
				ft_dprintf(2, "Debugging handling last redirect <<\n");
				if (handling_last_redirect(params, env) == -1)
					return (-1);
			}
		}
		params->x++;
	}
	return (0);
}
