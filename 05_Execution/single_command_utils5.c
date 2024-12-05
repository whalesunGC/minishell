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
 * @function: handle_single_commands_without_redirects
 * @brief: handles cases where there are no redirects
 	including built-in functions
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env : needed *** to amend env
 	if cd and export command is called
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking process fails, 0 if all commands are successfully run
 */

int	handle_single_commands_without_redirects(
			t_redirect_single_command_params *params, char ***env, int exit_s)
{
	if (ft_strcmp(params->av[0], "echo") == 0)
		echo_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "cd") == 0)
		cd_command(params->ac, params->av, env, params->exit_status);
	else if (ft_strcmp(params->av[0], "pwd") == 0)
		pwd_command(params->ac, params->av, params->exit_status);
	else if (ft_strcmp(params->av[0], "export") == 0)
		export_command(params->ac, params->av, env, params->exit_status);
	else if (ft_strcmp(params->av[0], "unset") == 0)
		unset_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "env") == 0)
		env_command(params->ac, params->av, *env, params->exit_status);
	else if (ft_strcmp(params->av[0], "exit") == 0)
	{
		*params->exit_status = exit_s;
		exit_command(params, *env, params->exit_status);
	}
	else if (handle_fork_plus_executing_child(params, env) == -1)
		return (-1);
	return (0);
}

/**
 * @function: handle_dup2_built_in_with_redirects
 * @brief: handles dup2 and file opening when there is an
 	output redirection with built-ins
 	this is being handled in the parent process
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 * 
 * @return: -1 if dup2 fails, 0 if everything is ok
 */

int	handle_dup2_built_in_with_redirects(
			t_redirect_single_command_params *params)
{
	if (params->output_fd > 0)
		close(params->output_fd);
	if (ft_strcmp(params->result->redirect[params->g], ">") == 0)
	{
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strcmp(params->result->redirect[params->g], ">>") == 0)
	{
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (params->output_fd < 0)
	{
		close(params->original_fd);
		return (-1);
	}
	if (dup2(params->output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		close(params->original_fd);
		return (-1);
	}
	params->rd_arg_counter++;
	return (0);
}

/**
 * @function: handle_single_commands_built_in_with_redirects
 * @brief: handling file opening when there is an output and input redirection
 	dup2 will be carried out if there's an output redirection
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 * 
 * @return: -1 if dup2 fails, 0 if everything is ok
 */

int	handle_single_commands_built_in_with_redirects(
			t_redirect_single_command_params *params)
{
	params->g = 0;
	params->rd_arg_counter = 0;
	if (params->result->redirect != NULL)
	{
		params->original_fd = dup(STDOUT_FILENO);
		while (params->result->redirect[params->g] != NULL)
		{
			if (handle_file_opening_input_for_built_in(params) == -1)
				return (-1);
			if (handle_file_opening_output_for_built_in(params) == -1)
				return (-1);
			params->g++;
		}
	}
	return (0);
}

/**
 * @function: execute_bulit_in_commands_with_redirects
 * @brief: after redirections are carried out, we execute the built-ins
 	closing of all fds and changing of output_fd
 	back to original fd if there was output redirection
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env : needed *** to amend env
 	if cd and export command is called
 * 
 * @return: void function
 */

void	execute_bulit_in_commands_with_redirects(
			t_redirect_single_command_params *params, char ***env, int exit_s)
{
	if (ft_strcmp(params->av[0], "echo") == 0)
		echo_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "cd") == 0)
		cd_command(params->ac, params->av, env, params->exit_status);
	else if (ft_strcmp(params->av[0], "pwd") == 0)
		pwd_command(params->ac, params->av, params->exit_status);
	else if (ft_strcmp(params->av[0], "export") == 0)
		export_command(params->ac, params->av, env, params->exit_status);
	else if (ft_strcmp(params->av[0], "unset") == 0)
		unset_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "env") == 0)
		env_command(params->ac, params->av, *env, params->exit_status);
	else if (ft_strcmp(params->av[0], "exit") == 0)
	{
		if (params->output_fd > 0)
		{
			close(params->output_fd);
			close(params->original_fd);
		}
		*params->exit_status = exit_s;
		exit_command(params, *env, params->exit_status);
	}
}

/**
 * @function: handle_single_commands
 * @brief: handles single commands with built-in features
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env : needed *** to amend env
 	if cd and export command is called
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking process fails, 0 if all commands are successfully run
 */

int	handle_single_commands(
			t_redirect_single_command_params *params, char ***env, int exit_s)
{
	if (params->result->cmd[0] == NULL)
	{
		if (handle_fork_plus_executing_child(params, env) == -1)
			return (-1);
	}
	else if (params->result->redirect == NULL)
	{
		if (handle_single_commands_without_redirects(params, env, exit_s) == -1)
			return (-1);
	}
	else if (params->result->redirect != NULL)
	{
		if (handle_single_commands_built_in(params, env, exit_s) == -1)
			return (-1);
	}
	return (0);
}
