/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:50:34 by apoh              #+#    #+#             */
/*   Updated: 2024/11/12 18:50:36 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_command_path_and_execve_failure
 * @brief: freeing up resources before exiting child process
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_command_path_and_execve_failure(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->command_path != params->result->cmd[0])
		free(params->command_path);
	clean_up_function(params, env);
	exit(127);
}

/**
 * @function: executing_execve
 * @brief: executing execve function after all conditions met
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	executing_execve(
			t_redirect_single_command_params *params, char ***env)
{
	if (!params->result->cmd[0])
	{
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
	handle_dot_slash_and_slash_single_commands(params, env);
	if (params->command_path == NULL || *params->result->cmd[0] == '\0')
	{
		ft_dprintf(2, "%s : command not found\n", params->result->cmd[0]);
		handle_command_path_and_execve_failure(params, env);
	}
	if (execve(params->command_path, params->result->cmd, *env) == -1)
		handle_error_for_execve_single_commands(params, env);
}

/**
 * @function: exiting_conditions_for_built_in
 * @brief: if cmd is a built in comand, will not perform execve
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	exiting_conditions_for_built_in(
			t_redirect_single_command_params *params, char ***env)
{
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0))
	{
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: handle_execve_for_redirections
 * @brief: handling execve conditions when there is redirections
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits
 * 
 * @return: void function
 */

void	handle_execve_for_redirections(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->result->cmd[0] == NULL)
	{
		ft_dprintf(2, "No commands found, so we just exit\n");
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
	exiting_conditions_for_built_in(params, env);
	params->a = 0;
	while (params->a < params->pipe_count)
	{
		close(params->pipes[params->a][0]);
		close(params->pipes[params->a][1]);
		params->a++;
	}
	executing_execve(params, env);
}

/**
 * @function: handling_executing_execve_other_cases
 * @brief: thie function will not handle redirections as
 	they are either done in heredocs function or handle redirect functions
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handling_executing_execve_other_cases(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->result->redirect != NULL)
	{
		if ((ft_strcmp(params->result->redirect[params->loop_counter],
					"a") == 0)
			|| (ft_strcmp(params->result->redirect[params->loop_counter],
					"<") == 0)
			|| (ft_strcmp(params->result->redirect[params->loop_counter],
					">") == 0)
			|| (ft_strcmp(params->result->redirect[params->loop_counter],
					">>") == 0))
		{
			clean_up_function(params, env);
			exit(EXIT_SUCCESS);
		}
	}
	executing_execve(params, env);
}
