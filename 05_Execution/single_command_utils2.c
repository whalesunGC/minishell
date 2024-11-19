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
 * @function: handle_redirections_file_opening
 * @brief: handling opening of files when redirections are called
 	and handling errors if files are not valid
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_redirections_file_opening(
			t_redirect_single_command_params *params, char ***env)
{
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
		if (params->input_fd < 0 || params->output_fd < 0)
		{
			ft_printf("%s: ", params->result->rd_arg[params->rd_arg_counter]);
			perror("Error opening file");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		params->rd_arg_counter++;
		params->k++;
	}
}

/**
 * @function: handle_dup_and_closing_fd
 * @brief: handling dup function calls for both input and output fd
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_dup_and_closing_fd(t_redirect_single_command_params
*params, char ***env)
{
	if (params->input_fd > 0)
	{
		if (dup2(params->input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->input_fd);
	}
	if (params->output_fd > 0)
	{
		if (dup2(params->output_fd, STDOUT_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->output_fd);
	}
}

/**
 * @function: executing_execve_redirections
 * @brief: executing execve function if redirections are called
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	executing_execve_redirections(t_redirect_single_command_params
*params, char ***env)
{
	write(2, "Entering the redirect loop\n", 27);
	if (params->input_fd == 0)
	{
		write(2, "I should not come here\n", 23);
		if (dup2(params->pipes[params->pipe_count - 1][0], STDIN_FILENO) == -1)
		{
			perror("dup2 failed");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
	}
	write(2, "I should come here\n", 19);
	if (access(params->result->cmd[0], F_OK) == 0)
		params->command_path = params->result->cmd[0];
	else
		params->command_path = find_command
			(&params->result->cmd[0], 0, *env);
	if (execve(params->command_path, params->result->cmd, *env) == -1)
	{
		if (params->command_path != params->result->cmd[0])
			free(params->command_path);
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

/**
 * @function: handle_execve_for_redirections
 * @brief: handling execve conditions when there is redirections
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: void function
 */

void	handle_execve_for_redirections(t_redirect_single_command_params *params,
	char ***env)
{
	write(2, "Entering the redirect loop\n", 27);
	if (params->result->cmd[0] == NULL)
	{
		write(2, "No commands found, so we just exit\n", 35);
		params->z = 0;
		while (params->z < params->pipe_count)
		{
			close(params->pipes[params->z][0]);
			close(params->pipes[params->z][1]);
			params->z++;
		}
		clean_up_function(params, env);
		exit(EXIT_SUCCESS);
	}
	if (params->pipe_count > 0)
		exiting_conditions_nonzero_pipecount(params, env);
	else
		exiting_conditions_zero_pipecount(params, env);
	executing_execve_redirections(params, env);
}
