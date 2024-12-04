/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils6.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:18:28 by apoh              #+#    #+#             */
/*   Updated: 2024/11/18 18:18:30 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_input_output_heredocs_multiple_commands
 * @brief: to dup2 input, output, heredoc redirections appropriately
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_input_output_heredocs_multiple_commands(
		t_piping_multiple_command_params *params, char ***env)
{
	params->b = 0;
	while (params->result->redirect[params->b] != NULL)
	{
		if (ft_strcmp(params->result->redirect[params->b], "<") == 0)
			setting_up_input_redirections_multiple_commands(params, env);
		else if (ft_strcmp(params->result->redirect[params->b], "a") == 0)
			setting_up_heredocs_multiple_commands(params, env);
		else if (ft_strcmp(params->result->redirect[params->b], ">") == 0)
			setting_up_output_redirections_multiple_commands(params, env);
		else if (ft_strcmp(params->result->redirect[params->b], ">>") == 0)
			setting_up_output_redirections_multiple_commands(params, env);
		params->b++;
	}
}

/**
 * @function: setup_pipe_redirection_and_closing
 * @brief: to handle the main general logic for the whole piping process
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	setup_pipe_redirection_and_closing(
			t_piping_multiple_command_params *params, char ***env)
{
	if (params->i < params->total - 1)
	{
		if (params->result->redirect != NULL)
		{
			handle_input_output_heredocs_multiple_commands(params, env);
			if (params->output_fd == 0)
				setting_up_pipes_to_redirect_output(params, env);
		}
		else
			setting_up_pipes_to_redirect_output(params, env);
	}
	if (params->i > 0)
	{
		if (params->result->redirect != NULL)
		{
			if (params->output_fd > 0)
				read_from_pipe(params, env);
			handle_input_output_heredocs_multiple_commands(params, env);
		}
		else
			read_from_pipe(params, env);
	}	
}

/**
 * @function: handle_built_in_multiple_piping_commands
 * @brief: to execute build in commands
 	if command array consists of built in commands
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_built_in_multiple_piping_commands(
			t_piping_multiple_command_params *params, char ***env, int *e_s)
{
	params->av = params->result->cmd;
	params->ac = 0;
	while (params->av[params->ac] != NULL)
		params->ac++;
	if (ft_strcmp(params->av[0], "echo") == 0)
		echo_command(params->ac, params->av);
	else if (ft_strcmp(params->av[0], "cd") == 0)
		cd_command(params->ac, params->av, env, e_s);
	else if (ft_strcmp(params->av[0], "pwd") == 0)
		pwd_command(params->ac, params->av, e_s);
	else if (ft_strcmp(params->av[0], "export") == 0)
		export_command(params->ac, params->av, env, e_s);
	else if (ft_strcmp(params->av[0], "unset") == 0)
		unset_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "env") == 0)
		env_command(params->ac, params->av, *env);
	else if (ft_strcmp(params->av[0], "exit") == 0)
		exit_command_multiple(params, *env);
}

/**
 * @function: handle_exit_conditions_if_built_in
 * @brief: to handle built in commands
 	if cmd array consists of built-in commands
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_exit_conditions_if_built_in(
			t_piping_multiple_command_params *params, char ***env)
{
	int	e_s;

	e_s = 0;
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0))
	{
		handle_built_in_multiple_piping_commands(params, env, &e_s);
		clean_up_function_multiple_commands(params, env);
		exit(e_s);
	}	
}

/**
 * @function: handle_child_process
 * @brief: handling the process a child process does after forking
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_child_process(
			t_piping_multiple_command_params *params, char ***env)
{
	setup_pipe_redirection_and_closing(params, env);
	if (params->input_fd > 0)
		close(params->input_fd);
	if (params->output_fd > 0)
		close(params->output_fd);
	if (params->heredocs_count > 0)
		closing_heredocs_pipes(params);
	closing_main_pipes(params);
	if (!params->result->cmd[0])
	{
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_SUCCESS);
	}
	handle_exit_conditions_if_built_in(params, env);
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (params->command_path == NULL || *params->result->cmd[0] == '\0')
		handle_invalid_command(params, env);
	else if (execve(params->command_path, params->result->cmd, *env) == -1)
		handle_execve_failure(params, env);
}
