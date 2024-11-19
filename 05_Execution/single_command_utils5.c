/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:01:18 by apoh              #+#    #+#             */
/*   Updated: 2024/11/19 16:01:19 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_redirects
 * @brief: handling redirections if command consists of redirects
 	execute_child_process is in single_command_utils1.c
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails, 0 if all commands is executed
 */

int	handle_redirects(t_redirect_single_command_params *params,
	char ***env)
{
	while (params->result->redirect[params->i] != NULL)
		params->i++;
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		execute_child_process_for_redirections(params, env);
	else
		wait(NULL);
	return (0);
}

/**
 * @function: execute_child_process_for_redirections
 * @brief: further summarising into a cleaner structure to read
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	execute_child_process_for_redirections(t_redirect_single_command_params
*params, char ***env)
{
	handle_redirections_file_opening(params, env);
	handle_dup_and_closing_fd(params, env);
	handle_execve_for_redirections(params, env);
}

/**
 * @function: handle_single_commands_no_heredocs
 * @brief: handling forking process if no heredocs is found
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_single_commands_no_heredocs(t_redirect_single_command_params *params,
	char ***env)
{	
	if (handle_fork_plus_executing_child(params, env) == -1)
		return (-1);
	return (0);
}

/**
 * @function: handle_other_cases
 * @brief: handling other test case scenarios
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails 0 if all commands is executed
 */

int	handle_other_cases(t_redirect_single_command_params *params, char ***env)
{
	params->av = params->result->cmd;
	params->ac = 0;
	while (params->av[params->ac] != NULL)
		params->ac++;
	if (handle_single_commands(params, env) == -1)
		return (-1);
	return (0);
}
