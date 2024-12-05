/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_command_utils5.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:19:47 by apoh              #+#    #+#             */
/*   Updated: 2024/11/18 17:19:52 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: setting_up_input_redirections_multiple_commands
 * @brief: handles input redirections for dup2 to STDIN
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	setting_up_input_redirections_multiple_commands(
		t_piping_multiple_command_params *params, char ***env)
{
	if (dup2(params->input_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 to stdin failed input_fd");
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: setting_up_output_redirections_multiple_commands
 * @brief: handles output redirections for dup2 to STDOUT
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	setting_up_output_redirections_multiple_commands(
		t_piping_multiple_command_params *params, char ***env)
{
	if (dup2(params->output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 to stdin failed for output_fd");
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: setting_up_heredocs_multiple_commands
 * @brief: handles heredoc redirections to heredoc pipes for STDIN
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	setting_up_heredocs_multiple_commands(
			t_piping_multiple_command_params *params, char ***env)
{
	if (dup2(params->heredocs_pipes[params->heredocs_pipe_index][0],
		STDIN_FILENO) == -1)
	{
		perror("dup2 to stdin failed heredocs_pipe");
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: setting_up_pipes_to_redirect_output
 * @brief: to pass output of command to the main pipes
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	setting_up_pipes_to_redirect_output(
			t_piping_multiple_command_params *params, char ***env)
{
	if (dup2(params->pipes[params->i][1], STDOUT_FILENO) == -1)
	{
		perror("dup2 to stdout failed main_pipe");
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: read_from_pipe_without_redirections
 * @brief: to read input from the pipe if no redirections
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	read_from_pipe(
			t_piping_multiple_command_params *params, char ***env)
{
	if (dup2(params->pipes[params->i - 1][0], STDIN_FILENO) == -1)
	{	
		perror("dup2 to stdin failed for reading from pipe");
		clean_up_function_multiple_commands(params, env);
		exit(EXIT_FAILURE);
	}
}
