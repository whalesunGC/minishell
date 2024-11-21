/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils9.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:27:27 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 15:27:29 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_exit_conditions_for_heredocs
 * @brief: handling certain exit conditions
 	so that execve will not be run
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_exit_conditions_for_heredocs(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging exit conditions for heredocs if built in command\n");
	if ((ft_strcmp(params->result->cmd[0], "echo") == 0)
		|| (ft_strcmp(params->result->cmd[0], "cd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "pwd") == 0)
		|| (ft_strcmp(params->result->cmd[0], "export") == 0)
		|| (ft_strcmp(params->result->cmd[0], "unset") == 0)
		|| (ft_strcmp(params->result->cmd[0], "env") == 0)
		|| (ft_strcmp(params->result->cmd[0], "exit") == 0))
	{
		ft_dprintf(2, "Debugging exiting heredocs\n");
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
}

/**
 * @function: handle_exit_file_opening_heredocs
 * @brief: in the presence of heredocs, we will open up all the files
 	to see if everything works, if everything works, we proceed with execve
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_exit_file_opening_heredocs(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->input_fd < 0 || params->output_fd < 0)
	{
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: checking_if_entire_command_has_errors
 * @brief: in the presence of heredocs, makes sure the
 	entire command is ok before we do execve
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	checking_if_entire_command_has_errors(
			t_redirect_single_command_params *params, char ***env)
{
	params->k = 0;
	while (params->k < params->i)
	{
		if (ft_strcmp(params->result->redirect[params->k], "a") == 0)
		{
			params->k++;
			continue ;
		}
		else if (ft_strcmp(params->result->redirect[params->k], "<") == 0)
			params->input_fd = open(params->result
					->rd_arg[params->rd_arg_counter], O_RDONLY);
		else if (ft_strcmp(params->result->redirect[params->k], ">") == 0)
			params->output_fd = open(params->result->rd_arg
				[params->rd_arg_counter], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(params->result->redirect[params->k], ">>") == 0)
			params->output_fd = open(params->result->rd_arg
				[params->rd_arg_counter], O_WRONLY | O_CREAT | O_APPEND, 0644);
		handle_exit_file_opening_heredocs(params, env);
		handle_file_closing_input_redirection(params);
		handle_file_closing_output_redirection(params);
		params->rd_arg_counter++;
		params->k++;
	}
}

/**
 * @function: handle_execve_for_heredocs
 * @brief: executing execve for heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success,
 	0 will never be reached if execve is successful.
 */

int	handle_execve_for_heredocs(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging handle execve for heredocs\n");
	if (dup2(params->pipes[params->pipe_count - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (-1);
	}
	checking_if_entire_command_has_errors(params, env);
	freeing_heredoc_pipes(params);
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (execve(params->command_path, params->result->cmd, *env) == -1)
	{
		perror("execve failed");
		freeing_heredoc_pipes(params);
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
	return (0);
}

/**
 * @function: handle_child_execution
 * @brief: forking child processes and to
 	execute them upon certain conditions
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_child_execution(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging Entering the heredocs loop\n");
	params->i = 0;
	while (params->result->redirect[params->i] != NULL)
		params->i++;
	params->pid = fork();
	if (params->pid < 0)
	{
		perror("forking failed");
		return (-1);
	}
	if (params->pid == 0)
	{
		handle_exit_conditions_for_heredocs(params, env);
		if (handle_execve_for_heredocs(params, env) == -1)
			return (-1);
	}
	return (0);
}
