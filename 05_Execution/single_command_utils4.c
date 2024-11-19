/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 18:51:58 by apoh              #+#    #+#             */
/*   Updated: 2024/11/12 18:51:59 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: executing_execve_other_cases
 * @brief: checks to be conducted before execve
 	is executed to fulfill certain test scenarios
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	executing_execve_other_cases(t_redirect_single_command_params
*params, char ***env)
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
			ft_printf("exiting no redirects for no_pipes\n");
			clean_up_function(params, env);
			exit(EXIT_SUCCESS);
		}
	}
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (execve(params->command_path, params->result->cmd, *env) == -1)
	{
		perror("execve error");
		if (params->command_path != params->result->cmd[0])
			free(params->command_path);
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: handle_exit_conditions_other_cases
 * @brief: handling conditions to exit child process
 * 
 * @param t_redirect_single_command_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handling_exit_conditions_other_cases(t_redirect_single_command_params
*params, char ***env)
{
	if (params->result->cmd[0] == NULL)
	{
		ft_printf("No commands found, so we just exit\n");
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
	params->loop_counter = 0;
	while (params->result->redirect[params->loop_counter] != NULL)
		params->loop_counter++;
	if ((ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"a") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				"<") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				">") == 0)
		|| (ft_strcmp(params->result->redirect[params->loop_counter - 1],
				">>") == 0))
	{
		ft_printf("exiting no redirects\n");
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: child_process_other_cases
 * @brief: after a fork is created, having checks for
 	heredocs and deciding what to execute
 * 
 * @param t_redirect_single_command_params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	child_process_other_cases(
			t_redirect_single_command_params *params, char ***env)
{
	ft_printf("Entering the no redirect loop\n");
	if (params->pipe_count == 0)
	{
		write(2, "Entering here\n", 14);
		executing_execve_other_cases(params, env);
	}
	else
	{
		write(2, "Entering here1\n", 15);
		handling_exit_conditions_other_cases(params, env);
	}
}

/**
 * @function: handle_fork_plus_executing_child
 * @brief: forks the process and creates a child process to handle it
 * 
 * @param t_redirect_single_commands_params *params : structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if forking fails. 0 if the whole execution is successful
 */

int	handle_fork_plus_executing_child(t_redirect_single_command_params
*params, char ***env)
{
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
		child_process_other_cases(params, env);
	else
		wait(NULL);
	return (0);
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

int	handle_single_commands(t_redirect_single_command_params *params,
	char ***env)
{	
	if (ft_strcmp(params->av[0], "echo") == 0)
		echo_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "cd") == 0)
		cd_command(params->ac, params->av, env);
	else if (ft_strcmp(params->av[0], "pwd") == 0)
		pwd_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "export") == 0)
		export_command(params->ac, params->av, env);
	else if (ft_strcmp(params->av[0], "unset") == 0)
		unset_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "env") == 0)
		env_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "exit") == 0)
		exit_command(params, *env);
	else if (handle_fork_plus_executing_child(params, env) == -1)
		return (-1);
	return (0);
}
