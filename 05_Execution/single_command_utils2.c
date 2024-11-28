/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:26:26 by apoh              #+#    #+#             */
/*   Updated: 2024/11/07 20:26:32 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_pipe_reading_heredocs_and_dup2
 * @brief: to make sure you are doing the correct dup2
 	for the correct pipe if heredocs present
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits
 * 
 * @return: void function
 */

void	handle_pipe_reading_heredocs_and_dup2(
			t_redirect_single_command_params *params, char ***env)
{
	if (ft_strcmp(params->result->redirect[params->k], "a") == 0)
		params->pipe_number++;
	if (params->pipe_number > 0)
	{
		params->pipe_index = params->pipe_number - 1;
		ft_dprintf(2, "Reading pipe number of heredocs [%d]\n", params->pipe_index);
	}
	if (dup2(params->pipes[params->pipe_index][0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed for heredocs");
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: handle_file_opening_redirection
 * @brief: opens files and closes the previous ones if open
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_file_opening_redirection(
			t_redirect_single_command_params *params)
{
	if (ft_strcmp(params->result->redirect[params->k], "<") == 0)
	{
		if (params->input_fd > 0)
			close(params->input_fd);
		params->input_fd = open(params->result
				->rd_arg[params->rd_arg_counter], O_RDONLY);
	}
	else if (ft_strcmp(params->result->redirect[params->k], ">") == 0)
	{
		if (params->output_fd > 0)
			close(params->output_fd);
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strcmp(params->result->redirect[params->k], ">>") == 0)
	{
		if (params->output_fd > 0)
			close(params->output_fd);
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

/**
 * @function: handle_file_opening_errors_redirections
 * @brief: printing error message and perform cleanup before exiting
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits
 * 
 * @return: void function
 */

void	handle_file_opening_errors_redirection(
			t_redirect_single_command_params *params, char ***env)
{
	if (params->input_fd < 0 || params->output_fd < 0)
	{
		ft_dprintf(2, "%s: ", params->result->rd_arg[params->rd_arg_counter]);
		perror("Error opening file");
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: handle_redirection_process
 * @brief: handles dup2 properly for input redirection or heredoc redirection
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handling_redirection_process(
			t_redirect_single_command_params *params, char ***env)
{
	if (ft_strcmp(params->result->redirect[params->k], "<") == 0)
	{
		if (dup2(params->input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->input_fd);
	}
	else if ((ft_strcmp(params->result->redirect
				[params->k], ">") == 0)
		|| (ft_strcmp(params->result->redirect
				[params->k], ">") == 0))
	{
		if (dup2(params->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 failed for child for output_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->output_fd);
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

void	handle_file_opening_process_for_redirection(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging handle redirections file opening\n");
	params->loop_counter = 0;
	params->pipe_number = 0;
	while (params->k < params->i)
	{
		if (ft_strcmp(params->result->redirect[params->k], "a") == 0)
		{
			handle_pipe_reading_heredocs_and_dup2(params, env);
			params->k++;
			continue ;
		}
		handle_file_opening_redirection(params);
		handle_file_opening_errors_redirection(params, env);
		handling_redirection_process(params, env);
		params->rd_arg_counter++;
		params->k++;
	}
}
