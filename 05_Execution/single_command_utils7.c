/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_commands_utils7.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoh <apoh@student.42singapore.sg>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:27:11 by apoh              #+#    #+#             */
/*   Updated: 2024/11/21 12:27:12 by apoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * @function: handle_file_opening_input_for_built_in
 * @brief: handle file opening process for built in functions in utils5
 	this is for input redirection
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_file_opening_input_for_built_in(
			t_redirect_single_command_params *params)
{
	if (ft_strcmp(params->result->redirect[params->g], "<") == 0)
	{
		if (params->input_fd > 0)
			close(params->input_fd);
		params->input_fd = open(params->result->rd_arg
			[params->rd_arg_counter], O_RDONLY);
		if (params->input_fd < 0)
		{
			close(params->original_fd);
			return (-1);
		}
	}
	return (0);
}

/**
 * @function: handle_file_opening_output_for_built_in
 * @brief: handle file opening process for built in functions in utils5
 	this is for output redirection
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 * 
 * @return: -1 if failure, 0 if success
 */

int	handle_file_opening_output_for_built_in(
			t_redirect_single_command_params *params)
{
	if ((ft_strcmp(params->result->redirect[params->g], ">") == 0)
		|| (ft_strcmp(params->result->redirect[params->g], ">>") == 0))
	{
		if (handle_dup2_built_in_with_redirects(params) == -1)
			return (-1);
	}
	return (0);
}

void	handle_ambigious_redirect(
			t_redirect_single_command_params *params, char ***env)
{
	if (ft_strcmp(params->result->rd_arg[params->rd_arg_counter], "") == 0)
	{
		ft_dprintf(2, "ambigious redirect\n");
		clean_up_function(params, env);
		exit(EXIT_FAILURE);
	}
}

void	handle_closing_and_freeing(
			t_redirect_single_command_params *params)
{
	if (params->output_fd > 0)
	{
		close(params->output_fd);
		close(params->original_fd);
	}
	params->a = 0;
	while (params->a < params->pipe_count)
	{
		close(params->pipes[params->a][0]);
		close(params->pipes[params->a][1]);
		params->a++;
	}
	freeing_heredoc_pipes(params);
	free_pipes(params->pipes, params->pipe_count);
}

/**
 * @function: heredocs
 * @brief: handling the presence of heredocs
 * 
 * @param t_redirect_single_command_params *params: structure for
 	single_command parameters
 	***env: *** is called in the calling function
 	needed ** to free data if child process exits.
 * 
 * @return: -1 if failure, 0 if success
 */

int	heredocs(t_redirect_single_command_params *params, char ***env)
{
	params->a = 0;
	while (params->result->redirect[params->x] != NULL)
	{
		if ((ft_strcmp(params->result->redirect[params->x], "<<") == 0))
		{
			if (handling_forking_process(params, env) == -1)
				return (-1);
			if (params->result->redirect[params->x + 1] != NULL)
			{
				handling_next_redirect(params);
				continue ;
			}
			else if (params->result->redirect[params->x + 1] == NULL)
			{
				if (handling_last_redirect(params, env) == -1)
					return (-1);
			}
		}
		params->x++;
	}
	return (0);
}
