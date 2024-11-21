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
 * @function: handle_file_opening_errors
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
 * @function: handle_file_closing_input_redirection
 * @brief: making sure the correct fd is closed
 	when looking through the redirect array
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_file_closing_input_redirection(
			t_redirect_single_command_params *params)
{
	if (params->input_fd > 0)
	{
		if (params->result->redirect[params->k + 1] != NULL)
		{
			params->b = params->k;
			while (params->result->redirect[params->b] != NULL)
			{
				if (params->result->redirect[params->b + 1] != NULL)
				{
					if (ft_strcmp(params->result->redirect
							[params->b + 1], "<") == 0)
						close(params->input_fd);
				}
				params->b++;
			}
		}
	}
}

/**
 * @function: handle_file_closing_output_redirection
 * @brief: making sure the correct fd is closed
 	when looking through the redirect array
 * 
 * @param t_redirect_single_command_params *params : structure to
 	store parameters for handling redirects / no redirects
 * 
 * @return: void function
 */

void	handle_file_closing_output_redirection(
			t_redirect_single_command_params *params)
{
	if (params->output_fd > 0)
	{
		if (params->result->redirect[params->k + 1] != NULL)
		{
			params->b = params->k;
			while (params->result->redirect[params->b] != NULL)
			{
				if (params->result->redirect[params->b + 1] != NULL)
				{
					if ((ft_strcmp(params->result->redirect
								[params->b + 1], ">") == 0)
						|| (ft_strcmp(params->result->redirect
								[params->b + 1], ">>") == 0))
						close(params->output_fd);
				}
				params->b++;
			}
		}
	}
}

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
	ft_dprintf(2, "Debugging handle redirections file opening\n");
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
		handle_file_opening_errors_redirection(params, env);
		handle_file_closing_input_redirection(params);
		handle_file_closing_output_redirection(params);
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

void	handle_dup_and_closing_fd(
			t_redirect_single_command_params *params, char ***env)
{
	ft_dprintf(2, "Debugging handle_dup_and_closing_fd\n");
	if (ft_strcmp(params->result->redirect[params->k - 1], "<") == 0
		&& params->input_fd > 0)
	{
		if (dup2(params->input_fd, STDIN_FILENO) == -1)
		{
			perror("Dup2 failed for child for input_fd");
			clean_up_function(params, env);
			exit(EXIT_FAILURE);
		}
		close(params->input_fd);
	}
	else if (((ft_strcmp(params->result->redirect[params->k - 1], ">") == 0)
			|| (ft_strcmp(params->result->redirect[params->k - 1], ">>") == 0))
		&& (params->output_fd > 0))
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
