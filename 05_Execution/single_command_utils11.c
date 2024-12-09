/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils11.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 21:19:46 by apoh              #+#    #+#             */
/*   Updated: 2024/12/09 21:19:48 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_dot_slash_and_slash_single_commands
 * @brief: checking for slashes to handle executables
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_dot_slash_and_slash_single_commands(
			t_redirect_single_command_params *params, char ***env)
{
	params->dot_slash = ft_strnstr(params->result->cmd[0],
			"./", ft_strlen(params->result->cmd[0]));
	if (params->dot_slash == NULL)
	{
		params->slash = ft_strchr(params->result->cmd[0], '/');
		if (params->slash == NULL)
			params->command_path = find_command(&params->result->cmd[0],
					0, *env);
		else
			params->command_path = params->result->cmd[0];
	}
	else
		params->command_path = params->result->cmd[0];
}
