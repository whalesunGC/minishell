/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_commands_utils7.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:51:34 by apoh              #+#    #+#             */
/*   Updated: 2024/11/18 18:51:36 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_file_opening_errors
 * @brief: print error message if file opening fails
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handle_file_opening_errors(t_piping_multiple_command_params *params)
{
	if (params->input_fd < 0 || params->output_fd < 0)
	{
		ft_dprintf(2, "%s: ", params->result->rd_arg[params->rd_arg_counter]);
		perror("Error opening file");
		params->flag = 1;
	}
}

/**
 * @function: handle_file_opening_for_redirects
 * @brief: handling file opening operations and
 	closing files if last one is open
 * 
 * @param t_piping_multiple_command_params *params : structure of
 	multiple command parameters
 * 
 * @return: void function
 */

void	handling_file_opening_for_redirects(
			t_piping_multiple_command_params *params)
{
	if (ft_strcmp(params->result->redirect[params->a], "<") == 0)
	{
		if (params->input_fd > 0)
			close(params->input_fd);
		params->input_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_RDONLY);
	}
	else if (ft_strcmp(params->result->redirect[params->a], ">") == 0)
	{
		if (params->output_fd > 0)
			close(params->output_fd);
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (ft_strcmp(params->result->redirect[params->a], ">>") == 0)
	{
		if (params->output_fd > 0)
			close(params->output_fd);
		params->output_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
}

/**
 * @function: handle_file_opening_multiple_commands
 * @brief: to handle file opening for input redirections
 	to handle creation and appending for output redirections
 	to handle file opening errors as well
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_file_opening_multiple_commands(
			t_piping_multiple_command_params *params)
{
	ft_dprintf(2, "Debugging file opening\n");
	params->b = 0;
	while (params->result->redirect[params->b] != NULL)
		params->b++;
	params->a = 0;
	params->rd_arg_counter = 0;
	while (params->a < params->b)
	{
		if (ft_strcmp(params->result->redirect[params->a], "a") == 0)
		{
			params->a++;
			continue ;
		}
		handling_file_opening_for_redirects(params);
		handle_file_opening_errors(params);
		if (params->flag == 1)
		{
			if (params->input_fd > 0)
				close(params->input_fd);
			if (params->output_fd > 0)
				close(params->output_fd);
			break ;
		}
		params->rd_arg_counter++;
		params->a++;
	}
}

/**
 * @function: handle_heredocs_pipe_number_multiple_commands
 * @brief: to check which pipe number should i be using
 	to extract my data when running the command
 * 
 * @param t_piping_multiple_command_params *params : structure for
 	multiple commands parameters
 * 
 * @return: void function
 */

void	handle_heredocs_pipe_number_multiple_commands(
		t_piping_multiple_command_params *params)
{
	if (params->result->redirect != NULL)
	{
		ft_dprintf(2, "Debugging heredocs\n");
		handle_file_opening_multiple_commands(params);
		if (params->heredocs_count > 0)
		{
			params->b = 0;
			while (params->result->redirect[params->b] != NULL)
			{
				ft_dprintf(2, "Debugging counting heredocs count total\n");
				if (ft_strcmp(params->result->redirect[params->b], "a") == 0)
					params->heredocs_pipe_number++;
				params->b++;
			}
			if (params->heredocs_pipe_number > 0)
			{
				params->heredocs_pipe_index = params->heredocs_pipe_number - 1;
				ft_dprintf(2, "reading pipe number [%d]\n",
					params->heredocs_pipe_index);
			}
		}
	}
}
