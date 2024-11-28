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
 * @function: handle_file_opening_process_for_redirection
 * @brief: handles the process of opening files for redirection and
 	reporting errors if file opening encounters errors
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

int	handle_file_opening_process_for_heredocs(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging handle redirections file opening\n");
	while (params->k < params->i)
	{
		if (ft_strcmp(params->result->redirect[params->k], "a") == 0)
		{
			params->k++;
			continue ;
		}
		handle_file_opening_redirection(params);
		handle_file_opening_errors_redirection(params, env);
		params->rd_arg_counter++;
		params->k++;
	}
	return (0);
}

/**
 * @function: handling_dup2_and_closing_heredoc_pipes_before_execve
 * @brief: handling dup2 of last heredoc pipes and dup2 to output if
 	there is an output file before running execve
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	handling_dup2_and_closing_heredoc_pipes_before_execve(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->input_fd > 0)
		close(params->input_fd);
	if (dup2(params->pipes[params->pipe_count - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (-1);
	}
	if (params->output_fd > 0)
	{
		if (dup2(params->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 failed for child for output_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->output_fd);
	}
	ft_dprintf(2, "Debugging closing current pipe\n");
	params->a = 0;
	while (params->a < params->pipe_count)
	{
		close(params->pipes[params->a][0]);
		close(params->pipes[params->a][1]);
		params->a++;
	}
	return (0);
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
	handle_file_opening_process_for_heredocs(params, env);
	if (handling_dup2_and_closing_heredoc_pipes_before_execve(params, env) == -1)
		return (-1);
	freeing_heredoc_pipes(params);
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command(&params->result->cmd[0], 0, *env);
	if (params->command_path == NULL)
	{
		ft_dprintf(2, "command not found\n");
		freeing_heredoc_pipes(params);
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
	else if (execve(params->command_path, params->result->cmd, *env) == -1)
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
